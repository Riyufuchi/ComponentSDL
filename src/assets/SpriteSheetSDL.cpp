//==============================================================================
// File       : SpriteSheetSDL.cpp
// Author     : riyufuchi
// Created on : Feb 22, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/SpriteSheetSDL.h"

namespace sdl
{
SpriteSheetSDL::SpriteSheetSDL(const char* path, SDL_Renderer* renderer) : ready(true)
{
	this->renderer = renderer;

	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Null pointer to renderer!");
		ready = false;
		return;
	}

	spriteSheet = IMG_Load(path);
	if (!spriteSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", SDL_GetError());
		ready = false;
		return;
	}

	textureSheet = SDL_CreateTextureFromSurface(renderer, spriteSheet);
	if (!textureSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
		ready = false;
		return;
	}
	this->sourceSurface = nullptr;
}

SpriteSheetSDL::SpriteSheetSDL(unsigned int len, unsigned char* imgdata, SDL_Renderer* renderer)
{
	this->renderer = renderer;

	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Null pointer to renderer!");
		ready = false;
		return;
	}

	SDL_IOStream* io = SDL_IOFromConstMem(imgdata, len);

	spriteSheet = IMG_Load_IO(io, 1);
	if (!spriteSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", SDL_GetError());
		ready = false;
		return;
	}

	textureSheet = SDL_CreateTextureFromSurface(renderer, spriteSheet);
	if (!textureSheet)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
		ready = false;
		return;
	}
	this->sourceSurface = nullptr;
}

SpriteSheetSDL::~SpriteSheetSDL()
{
	if (textureSheet)
		SDL_DestroyTexture(textureSheet);
	if (spriteSheet)
		SDL_DestroySurface(spriteSheet);
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

	// Convert format if needed
	if (sourceSurface->format != SDL_PIXELFORMAT_RGBA32)
	{
		SDL_Surface* converted = SDL_ConvertSurface(spriteSheet, SDL_PIXELFORMAT_RGBA32);
		if (!converted)
		{
			SDL_Log("ERROR: Failed to convert surface: %s", SDL_GetError());
			return nullptr;
		}
		sourceSurface = converted;
	}

	// Allocate pixel buffer for cropped surface (SDL3 needs this!)
	int bytes_per_pixel = SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32);
	int pitch = width * bytes_per_pixel;

	void* pixels = SDL_malloc(height * pitch);
	if (!pixels)
	{
		SDL_Log("ERROR: Out of memory");
		if (sourceSurface != spriteSheet)
			SDL_DestroySurface(sourceSurface);
		return nullptr;
	}

	// Create surface wrapping this pixel buffer
	SDL_Surface* croppedSurface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, pitch);

	if (!croppedSurface)
	{
		SDL_free(pixels);
		if (sourceSurface != spriteSheet)
			SDL_DestroySurface(sourceSurface);
		return nullptr;
	}

	// Now blit the desired region
	SDL_Rect srcRect = { x, y, width, height };
	SDL_Rect dstRect = { 0, 0, width, height };

	if (SDL_BlitSurface(sourceSurface, &srcRect, croppedSurface, &dstRect))
	{
		SDL_Log("ERROR: Blit failed: %s", SDL_GetError());
		SDL_DestroySurface(croppedSurface);
		if (sourceSurface != spriteSheet)
			SDL_DestroySurface(sourceSurface);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, croppedSurface);
	if (!texture)
	{
		SDL_Log("ERROR: Failed to create texture: %s", SDL_GetError());
		SDL_DestroySurface(croppedSurface);
		return nullptr;
	}

	return texture;
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
