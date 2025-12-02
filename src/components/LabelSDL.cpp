//==============================================================================
// File       : StringSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/LabelSDL.h"

namespace sdl
{
LabelSDL::LabelSDL(std::string text, const std::string& fontname, int size, SDL_Color color, SDL_Renderer* renderer) : ComponentSDL(0, 0, 0, 0, color),
	renderer(renderer), textTexture(nullptr), size(size)
{
	this->fontname = fontname;
	setText(text, color); // Initialize text texture
}

LabelSDL::~LabelSDL()
{
	if (textStringSDL)
		delete textStringSDL;
}

void LabelSDL::draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
}

void LabelSDL::draw()
{
	SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
}

void LabelSDL::setText(std::string text)
{
	setText(text, baseColor);
}

void LabelSDL::setText(std::string text, SDL_Color color)
{
	if (textStringSDL)
		delete textStringSDL;
	textStringSDL = new TextSDL(renderer, fontname, text, size, color);
	SDL_Texture* t = textStringSDL->getTexture();
	if (!t)
		return;
	textTexture = t;
	SDL_QueryTexture(t, nullptr, nullptr, &rect.w, &rect.h);
}

} /* namespace ConsoleArt */
