//==============================================================================
// File       : SpriteSheetSDL.cpp
// Author     : riyufuchi
// Created on : Feb 22, 2025
// Last edit  : Nov 10, 2025
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
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", IMG_GetError());
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
