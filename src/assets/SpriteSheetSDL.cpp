//==============================================================================
// File       : SpriteSheetSDL.cpp
// Author     : riyufuchi
// Created on : Feb 22, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/SpriteSheetSDL.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../inc/external/stb_image.h"


namespace sdl
{
SpriteSheetSDL::SpriteSheetSDL(const char* path, SDL_Renderer* renderer) : renderer(renderer), ready(true), spriteSheet(nullptr), textureSheet(nullptr), sourceSurface(nullptr)
{
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Null renderer!");
		ready = false;
		return;
	}

	int w, h, channels;
	unsigned char* pixels = stbi_load(path, &w, &h, &channels, 4);
	if (!pixels)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed load stb: %s",
				stbi_failure_reason());
		ready = false;
		return;
	}

	// Create SDL surface (this COPIES pixels into SDL-owned memory)
	spriteSheet = SDL_CreateRGBSurfaceWithFormatFrom(pixels, // raw pixel data (temporary)
			w, h, 32,                 // depth
			w * 4,              // pitch
			SDL_PIXELFORMAT_RGBA32);

	// SDL_CreateRGBSurfaceWithFormatFrom DOES NOT copy pixel memory.
	// So we now need to allocate SDL-owned memory and copy into it.

	if (!spriteSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed create surface: %s",
				SDL_GetError());
		stbi_image_free(pixels);
		ready = false;
		return;
	}

	// Allocate SDL-owned surface memory that does copy
	SDL_Surface* finalSurface = SDL_ConvertSurfaceFormat(spriteSheet,
			SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(spriteSheet);      // free wrapper surface
	spriteSheet = finalSurface;        // use real surface

	stbi_image_free(pixels);           // raw stb buffer no longer needed

	if (!spriteSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Surface format convert failed: %s", SDL_GetError());
		ready = false;
		return;
	}

	// Optional: full texture version for drawing whole image
	textureSheet = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC, w, h);
	if (textureSheet)
	{
		SDL_UpdateTexture(textureSheet, nullptr, spriteSheet->pixels,
				spriteSheet->pitch);
	}
}

SpriteSheetSDL::SpriteSheetSDL(unsigned int len, unsigned char* imgdata, SDL_Renderer* renderer) : renderer(renderer), ready(true), spriteSheet(nullptr), textureSheet(nullptr), sourceSurface(nullptr)
{
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Null renderer!");
		ready = false;
		return;
	}

	int w, h, channels;
	unsigned char* pixels = stbi_load_from_memory(imgdata, len, &w, &h,
			&channels, 4);
	if (!pixels)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"stb failed load from memory: %s", stbi_failure_reason());
		ready = false;
		return;
	}

	// Wrap stb pixels into a temporary SDL surface (NO COPY!)
	SDL_Surface* tempSurface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, // raw pixel buffer
			w, h, 32,                 // depth
			w * 4,              // pitch
			SDL_PIXELFORMAT_RGBA32);

	if (!tempSurface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to wrap surface: %s",
				SDL_GetError());
		stbi_image_free(pixels);
		ready = false;
		return;
	}

	// Convert -> SDL now allocates and owns its own pixel memory (COPY happens here)
	spriteSheet = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_RGBA32,
			0);

	SDL_FreeSurface(tempSurface);  // free wrapper surface
	stbi_image_free(pixels);       // free stb pixel buffer

	if (!spriteSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Surface convert failed: %s",
				SDL_GetError());
		ready = false;
		return;
	}

	// Optional: full texture version, useful for drawing the whole sheet
	textureSheet = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STATIC, w, h);

	if (textureSheet)
	{
		SDL_UpdateTexture(textureSheet, nullptr, spriteSheet->pixels,
				spriteSheet->pitch);
	}
}


SpriteSheetSDL::~SpriteSheetSDL()
{
	if (textureSheet)
		SDL_DestroyTexture(textureSheet);
	if (spriteSheet)
		SDL_FreeSurface(spriteSheet);
}

SDL_Texture* SpriteSheetSDL::getCroppedTexture(int x, int y, int width, int height)
{
	if (!spriteSheet)
	{
		SDL_Log("ERROR: Sprite sheet not loaded!");
		return nullptr;
	}

	if (x < 0 || y < 0 || x + width > spriteSheet->w || y + height > spriteSheet->h)
	{
		SDL_Log("ERROR: Crop area out of bounds! SpriteSheet: %dx%d, Requested: x=%d, y=%d, w=%d, h=%d", spriteSheet->w, spriteSheet->h, x, y, width, height);
		return nullptr;
	}

	// Convert surface only if necessary
	sourceSurface = spriteSheet;
	if (spriteSheet->format->format != SDL_PIXELFORMAT_RGBA32)
	{
		sourceSurface = SDL_ConvertSurfaceFormat(spriteSheet,
				SDL_PIXELFORMAT_RGBA32, 0);
		if (!sourceSurface) {
			SDL_Log("ERROR: Failed to convert surface format: %s",
					SDL_GetError());
			return nullptr;
		}
	}

	// Create the cropped surface
	SDL_Surface* croppedSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
	if (!croppedSurface)
	{
		SDL_Log("ERROR: Failed to create cropped surface: %s", SDL_GetError());
		if (sourceSurface != spriteSheet)
			SDL_FreeSurface(sourceSurface);
		return nullptr;
	}

	SDL_Rect srcRect = { x, y, width, height };
	SDL_BlitSurface(sourceSurface, &srcRect, croppedSurface, nullptr);

	// Convert cropped surface to texture
	SDL_Texture* croppedTexture = SDL_CreateTextureFromSurface(renderer, croppedSurface);

	// Free only if we created a new surface for conversion
	if (sourceSurface != spriteSheet)
		SDL_FreeSurface(sourceSurface);

	SDL_FreeSurface(croppedSurface);

	if (!croppedTexture)
	{
		SDL_Log("ERROR: Failed to create texture: %s", SDL_GetError());
		return nullptr;
	}

	return croppedTexture;
}

SDL_Texture* SpriteSheetSDL::getTexture(const std::string& textureName)
{
	if (textureCache.find(textureName) != textureCache.end())
	{
		return textureCache[textureName]; // Return the cached texture if it exists
	}
	return nullptr;
}
std::pair<SDL_Texture*, SDL_Texture*> SpriteSheetSDL::getTexturePair(std::pair<std::string, std::string> IDs)
{
	return { getTexture(IDs.first), getTexture(IDs.second)};
}
void SpriteSheetSDL::prepareTexture(const std::string textureName, int x, int y, int width, int height)
{
	textureSheet = getCroppedTexture(x, y, width, height);
	if (!textureSheet)
		return;
	textureCache[textureName] = textureSheet;
}
void SpriteSheetSDL::prepareTexturePair(std::pair<std::string, std::string> IDs, int x, int y, std::pair<int, int> size)
{
	prepareTexture(IDs.first, x, y, size.first, size.second);
	prepareTexture(IDs.second, x + size.first, y, size.first, size.second);
}

bool SpriteSheetSDL::isReady() const
{
	return ready;
}

}
