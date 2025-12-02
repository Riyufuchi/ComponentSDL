//==============================================================================
// File       : StringButtonSDL.cpp
// Author     : riyufuchi
// Created on : Mar 04, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/StringButtonSDL.h"

namespace sdl
{
StringButtonSDL::StringButtonSDL(StringSDL* text, SDL_Color hoverColor, std::function<void()> callback) : StringButtonSDL(0, 0, text, hoverColor, callback)
{
}

StringButtonSDL::StringButtonSDL(int x, int y, StringSDL* text, SDL_Color hoverColor, std::function<void()> callback) : ComponentSDL(x, y, 10, 10, callback), text(text)
{
	this->rect.w = text->getWidth();
	this->rect.h = text->getHeight();
	this->textHover = new sdl::StringSDL(text->getText(), text->getFont(), hoverColor, text->getRenderer());
}

StringButtonSDL::~StringButtonSDL()
{
	delete text;
	delete textHover;
}

void StringButtonSDL::draw(SDL_Renderer *renderer)
{
	SDL_RenderTexture(renderer, isMouseOver() ? textHover->getTexture() : text->getTexture(), nullptr, &rect);
}

} /* namespace sdl */
