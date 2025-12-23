//==============================================================================
// File       : Button.cpp
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../component_sdl_lib/components/button_sdl.h"

namespace sdl
{

ButtonSDL::ButtonSDL(int x, int y, int width, int height) : ComponentSDL(x, y, width, height, {0, 128, 255, 255})
{
	this->hoverColor = {0, 200, 255, 255};
}
ButtonSDL::~ButtonSDL()
{
}

void ButtonSDL::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer,
		mouseOver ? hoverColor.r : baseColor.r,
		mouseOver ? hoverColor.g : baseColor.g,
		mouseOver ? hoverColor.b : baseColor.b, 255);
	SDL_RenderFillRect(renderer, &rect);
}
} /* namespace consoleart */
