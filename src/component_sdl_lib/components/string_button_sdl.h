//==============================================================================
// File       : StringButtonSDL.h
// Author     : riyufuchi
// Created on : Mar 04, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#ifndef SDL_COMPONENTS_STRINGBUTTONSDL_H_
#define SDL_COMPONENTS_STRINGBUTTONSDL_H_

#include "../base/component_sdl.h"
#include "../asset_tools/text_sdl.h"

namespace sdl
{
class StringButtonSDL : public ComponentSDL
{
private:
	TextSDL* text;
	SDL_Texture* textHover;
public:
	StringButtonSDL(TextSDL* text, SDL_Color hoverColor, std::function<void()> callback = nullptr);
	StringButtonSDL(int x, int y, TextSDL* text, SDL_Color hoverColor, std::function<void()> callback = nullptr);
	virtual ~StringButtonSDL();
	virtual void draw(SDL_Renderer *renderer) override;
};
} /* namespace sdl */
#endif /* SDL_COMPONENTS_STRINGBUTTONSDL_H_ */
