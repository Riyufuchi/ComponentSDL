//==============================================================================
// File       : FontManagerSDL.h
// Author     : riyufuchi
// Created on : Mar 8, 2025
// Last edit  : Mar 8, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef SDL_ASSETS_FONTMANAGERSDL_H_
#define SDL_ASSETS_FONTMANAGERSDL_H_

#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

namespace sdl
{
class FontManagerSDL
{
private:
	struct FontDeleter
	{
		void operator()(TTF_Font* font) const
		{
			if (font)
				TTF_CloseFont(font);
		}
	};
	std::unordered_map<std::string, std::unique_ptr<TTF_Font, FontDeleter>> fonts;
	FontManagerSDL() = default;
	~FontManagerSDL() { clear(); }
	FontManagerSDL(const FontManagerSDL&) = delete;
	FontManagerSDL& operator=(const FontManagerSDL&) = delete;
public:
	static FontManagerSDL& getInstance();
	TTF_Font* getFont(const std::string& fontName, int size);
	void clear();
};
} /* namespace ConsoleArt */
#endif /* SDL_ASSETS_FONTMANAGERSDL_H_ */
