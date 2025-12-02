//==============================================================================
// File       : Button.h
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_UTILS_BUTTON_H_
#define CONSOLEART_GUI_UTILS_BUTTON_H_

#include "SDL3/SDL.h"

#include "ComponentSDL.h"

namespace sdl
{
class ButtonSDL : public ComponentSDL
{
private:
	SDL_Color hoverColor;
public:
	ButtonSDL(int x, int y, int width, int height);
	~ButtonSDL();
	virtual void draw(SDL_Renderer* renderer) override;
};

} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_UTILS_BUTTON_H_ */
