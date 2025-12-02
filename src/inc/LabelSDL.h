//==============================================================================
// File       : StringSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_SDL_ASSETS_LABELSDL_H_
#define CONSOLEART_SDL_ASSETS_LABELSDL_H_

#include <string>

#include "SDL3/SDL.h"
#include "SDL3/SDL_ttf.h"

#include "ComponentSDL.h"
#include "FontManagerSDL.h"
#include "StringSDL.h"

namespace sdl
{
class LabelSDL : public ComponentSDL
{
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* textTexture;
	StringSDL* textStringSDL;
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
