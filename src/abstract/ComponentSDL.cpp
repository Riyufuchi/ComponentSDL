//==============================================================================
// File       : ComponentSDL.cpp
// Author     : riyufuchi
// Created on : Feb 21, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/ComponentSDL.h"

namespace sdl
{

ComponentSDL::ComponentSDL(float x, float y, float width, float height, std::function<void()> onClickEvent) : ComponentSDL(x, y, width, height, {128, 128, 128, 255}, onClickEvent)
{
}

ComponentSDL::ComponentSDL(float x, float y, float width, float height, SDL_Color baseColor, std::function<void()>  onClickEvent) : mouseOver(false),baseColor(baseColor), rect({x, y, width, height}), onClickEvent(onClickEvent)
{
}

ComponentSDL::~ComponentSDL()
{
}

void ComponentSDL::repose(float x, float y)
{
	rect.x = x;
	rect.y = y;
}

void ComponentSDL::center(float width, float height)
{
	rect.x = std::max(0.0f, (width - rect.w) / 2);
	rect.y = std::max(0.0f, (height - rect.h) / 2);
}

void ComponentSDL::centerHorizontal(float width)
{
	rect.x = std::max(0.0f, (width - rect.w) / 2);
}

void ComponentSDL::onClick()
{
	if (onClickEvent && mouseOver)
		onClickEvent();
}

bool ComponentSDL::isMouseInside(float mouseX, float mouseY) const
{
	return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

void ComponentSDL::setX(float x)
{
	this->rect.x = x;
}

void ComponentSDL::setY(float y)
{
	this->rect.y = y;
}

void ComponentSDL::setWidth(float width)
{
	this->rect.w = width;
}

void ComponentSDL::setHeight(float height)
{
	this->rect.h = height;
}

void ComponentSDL::setMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

float ComponentSDL::getX() const
{
	return this->rect.x;
}

float ComponentSDL::getY() const
{
	return this->rect.y;
}

float ComponentSDL::getWidth() const
{
	return this->rect.w;
}

float ComponentSDL::getHeight() const
{
	return this->rect.h;
}

bool ComponentSDL::isMouseOver() const
{
	return mouseOver;
}

} /* namespace ConsoleArt */
