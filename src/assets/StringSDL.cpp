//==============================================================================
// File       : StringSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/StringSDL.h"

namespace sdl
{
StringSDL::StringSDL(std::string text, std::string fontname, int size, SDL_Color color, SDL_Renderer* renderer) : renderer(renderer), textTexture(nullptr), text(text), size(size), color(color)
{
	font = FontManagerSDL::getInstance().getFont(fontname, size);
	if (!font)
	{
		SDL_Log("ERROR: Failed to load font: %s", TTF_GetError());
		return; // Prevent further execution
	}

	setText(text, color); // Initialize text texture
}

StringSDL::StringSDL(std::string text, TTF_Font* font, int size, SDL_Color color, SDL_Renderer* renderer) : renderer(renderer), textTexture(nullptr), text(text), size(size), color(color)
{
	this->font = font;
	if (!font)
	{
		SDL_Log("ERROR: Failed to load font: %s", TTF_GetError());
		return; // Prevent further execution
	}
	setText(text, color); // Initialize text texture
}

StringSDL::~StringSDL()
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
}

SDL_Texture* StringSDL::prepareText(std::string& text, SDL_Color& color)
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
	if (!textSurface)
	{
		SDL_Log("ERROR: Failed to create text surface: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (!textTexture)
	{
		SDL_Log("ERROR: Failed to create texture from text: %s", SDL_GetError());
	}

	return textTexture;
}

void StringSDL::setText(std::string text)
{
	SDL_Texture* t = prepareText(text, color);
	if (!t)
		return;
	textTexture = t;
	SDL_QueryTexture(t, nullptr, nullptr, &rect.w, &rect.h);
}

void StringSDL::setText(std::string text, SDL_Color color)
{
	SDL_Texture* t = prepareText(text, color);
	if (!t)
		return;
	textTexture = t;
	SDL_QueryTexture(t, nullptr, nullptr, &rect.w, &rect.h);
}
TTF_Font* StringSDL::getFont() const
{
	return font;
}

int StringSDL::getSize() const {
	return size;
}

const std::string& StringSDL::getText() const
{
	return text;
}

SDL_Texture* StringSDL::getTexture() const
{
	return textTexture;
}

int StringSDL::getWidth() const
{
	return rect.w;
}
int StringSDL::getHeight() const
{
	return rect.h;
}

} /* namespace ConsoleArt */
