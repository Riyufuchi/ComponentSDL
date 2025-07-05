//==============================================================================
// File       : ComponentSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Feb 21, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/ComponentSDL.h"

namespace sdl
{

ComponentSDL::ComponentSDL(int x, int y, int width, int height, std::function<void()> onClickEvent) : ComponentSDL(x, y, width, height, {128, 128, 128, 255}, onClickEvent)
{
}

ComponentSDL::ComponentSDL(int x, int y, int width, int height, SDL_Color baseColor, std::function<void()>  onClickEvent) : mouseOver(false),baseColor(baseColor), rect({x, y, width, height}), onClickEvent(onClickEvent)
{
}

ComponentSDL::~ComponentSDL()
{
}

void ComponentSDL::repose(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void ComponentSDL::center(int width, int height)
{
	rect.x = std::max(0, (width - rect.w) / 2);
	rect.y = std::max(0, (height - rect.h) / 2);
}

void ComponentSDL::centerHorizontal(int width)
{
	rect.x = std::max(0, (width - rect.w) / 2);
}

void ComponentSDL::onClick()
{
	if (onClickEvent && mouseOver)
		onClickEvent();
}

bool ComponentSDL::isMouseInside(int mouseX, int mouseY) const
{
	return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

void ComponentSDL::setX(int x)
{
	this->rect.x = x;
}

void ComponentSDL::setY(int y)
{
	this->rect.y = y;
}

void ComponentSDL::setWidth(int width)
{
	this->rect.w = width;
}

void ComponentSDL::setHeight(int height)
{
	this->rect.h = height;
}

void ComponentSDL::setMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

int ComponentSDL::getX() const
{
	return this->rect.x;
}

int ComponentSDL::getY() const
{
	return this->rect.y;
}

int ComponentSDL::getWidth() const
{
	return this->rect.w;
}

int ComponentSDL::getHeight() const
{
	return this->rect.h;
}

bool ComponentSDL::isMouseOver() const
{
	return mouseOver;
}

} /* namespace ConsoleArt */
