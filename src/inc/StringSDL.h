//==============================================================================
// File       : StringSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_SDL_ASSETS_STRINGSDL_H_
#define CONSOLEART_SDL_ASSETS_STRINGSDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "FontManagerSDL.h"

namespace sdl
{
class StringSDL
{
protected:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* textTexture;
	std::string text;
	int size;
	SDL_Rect rect;
	SDL_Color color;
	SDL_Texture* prepareText(std::string& text, SDL_Color& color);
public:
	StringSDL(std::string text, std::string fontname, int size, SDL_Color color, SDL_Renderer* renderer);
	StringSDL(std::string text, TTF_Font* fontname, int size, SDL_Color color, SDL_Renderer* renderer);
	virtual ~StringSDL();
	void setText(std::string text);
	void setText(std::string text, SDL_Color color);
	TTF_Font* getFont() const;
	SDL_Texture* getTexture() const;
	const std::string& getText() const;
	int getSize() const;
	SDL_Renderer* getRenderer() const {
		return renderer;
	}
	int getWidth() const;
	int getHeight() const;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_SDL_ASSETS_STRINGSDL_H_ */
