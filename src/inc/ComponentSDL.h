//==============================================================================
// File       : ComponentSDL.h
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_COMPONENTSDL_H_
#define CONSOLEART_GUI_COMPONENTSDL_H_

#include "SDL3/SDL.h"
#include <functional>

namespace sdl
{
class ComponentSDL
{
protected:
	bool mouseOver;
	SDL_Color baseColor;
	SDL_FRect rect;
	std::function<void()> onClickEvent;
public:
	ComponentSDL(float x, float y, float width, float height, std::function<void()> onClickEvent = nullptr);
	ComponentSDL(float x, float y, float width, float height, SDL_Color baseColor, std::function<void()> onClickEvent = nullptr);
	virtual ~ComponentSDL();
	// Functions
	bool isMouseInside(float x, float y) const;
	//Methods
	void onClick();
	void repose(float x, float y);
	void center(float width, float height);
	void centerHorizontal(float width);
	virtual void draw(SDL_Renderer* renderer) = 0;
	// Setters
	virtual void setX(float x);
	virtual void setY(float y);
	void setWidth(float width);
	void setHeight(float height);
	void setMouseOver(bool mouseOver);
	// Getters
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	bool isMouseOver() const;
};
} /* namespace ConsoleArt */

#endif /* CONSOLEART_GUI_COMPONENTSDL_H_ */
