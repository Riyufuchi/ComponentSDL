//==============================================================================
// File       : StringSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_SDL_ASSETS_LABELSDL_H_
#define CONSOLEART_SDL_ASSETS_LABELSDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "ComponentSDL.h"
#include "FontManagerSDL.h"

namespace sdl
{
class LabelSDL : public ComponentSDL
{
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Texture* prepareText(std::string& text, SDL_Color& color);
public:
	LabelSDL(std::string text, std::string fontname, int size, SDL_Color color, SDL_Renderer* renderer);
	virtual ~LabelSDL();
	virtual void draw(SDL_Renderer *renderer) override;
	void draw();
	void setText(std::string text);
	void setText(std::string text, SDL_Color color);
	TTF_Font* getFont();

};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_SDL_ASSETS_STRINGSDL_H_ */
