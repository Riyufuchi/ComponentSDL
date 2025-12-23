//==============================================================================
// File       : StringSDL.h
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef CONSOLEART_SDL_ASSETS_LABELSDL_H_
#define CONSOLEART_SDL_ASSETS_LABELSDL_H_

#include <string>

#include "SDL2/SDL.h"

#include "../base/component_sdl.h"
#include "../asset_tools/text_sdl.h"

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

} /* namespace consoleart */

#endif /* CONSOLEART_SDL_ASSETS_STRINGSDL_H_ */
