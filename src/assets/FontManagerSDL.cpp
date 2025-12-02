//==============================================================================
// File       : FontManagerSDL.cpp
// Author     : riyufuchi
// Created on : Mar 08, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/FontManagerSDL.h"

namespace sdl
{

FontManagerSDL& FontManagerSDL::getInstance()
{
	static FontManagerSDL instance;
	return instance;
}

TTF_Font* FontManagerSDL::getFont(const std::string& fontName, int size)
{
	std::string key = fontName + std::to_string(size);

	auto it = fonts.find(key);
	if (it != fonts.end())
	{
		return it->second.get();
	}

	TTF_Font *font = TTF_OpenFont(fontName.c_str(), size);
	if (!font)
	{
		SDL_Log("Failed to load font %s: %s", fontName.c_str(), SDL_GetError());
		return nullptr;
	}

	fonts[key] = std::unique_ptr<TTF_Font, FontDeleter>(font);
	return font;
}

void FontManagerSDL::clear()
{
	fonts.clear();
}

} /* namespace sdl */
