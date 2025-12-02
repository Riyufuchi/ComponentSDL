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

#include "SDL2/SDL.h"

#include "ComponentSDL.h"
#include "TextSDL.h"

namespace sdl
{
class LabelSDL : public ComponentSDL
{
private:
	SDL_Renderer* renderer;
	SDL_Texture* textTexture;
	TextSDL* textStringSDL;
	int size;
	std::string fontname;
public:
	LabelSDL(std::string text, const std::string& fontname, int size, SDL_Color color, SDL_Renderer* renderer);
	virtual ~LabelSDL();
	virtual void draw(SDL_Renderer *renderer) override;
	void draw();
	void setText(std::string text);
	void setText(std::string text, SDL_Color color);

};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_SDL_ASSETS_STRINGSDL_H_ */
