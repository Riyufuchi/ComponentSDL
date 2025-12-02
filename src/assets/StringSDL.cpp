//==============================================================================
// File       : StringSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Dec 02, 2025
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
		SDL_Log("ERROR: Failed to load font: %s", SDL_GetError());
		return; // Prevent further execution
	}

	setText(text, color); // Initialize text texture
}

StringSDL::StringSDL(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) : renderer(renderer), textTexture(nullptr), text(text), size(size), color(color)
{
	this->font = font;
	if (!font)
	{
		SDL_Log("ERROR: Failed to load font: %s", SDL_GetError());
		return; // Prevent further execution
	}
	setText(text, color); // Initialize text texture
}

StringSDL::~StringSDL()
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
}

SDL_Texture* StringSDL::prepareText(const std::string& text, SDL_Color& color)
{
	// Destroy old texture
	if (textTexture)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = nullptr;
	}

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), 0, color);
	if (!textSurface)
	{
		SDL_Log("ERROR: Failed to create text surface: %s", SDL_GetError());
		return nullptr;
	}

	// Convert to texture
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_DestroySurface(textSurface);

	if (!textTexture)
	{
		SDL_Log("ERROR: Failed to create texture from text: %s",
				SDL_GetError());
		return nullptr;
	}

	return textTexture;
}

void StringSDL::setText(std::string text)
{
	setText(text, color);
}

void StringSDL::setText(std::string text, SDL_Color& color)
{
	SDL_Texture* t = prepareText(text, color);
	if (!t)
		return;
	textTexture = t;
	static float w, h;
	SDL_GetTextureSize(t, &w, &h);
	rect.w = w;
	rect.w = h;
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
