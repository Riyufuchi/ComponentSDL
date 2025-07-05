//==============================================================================
// File       : StringSDL.cpp
// Author     : riyufuchi
// Created on : Feb 25, 2025
// Last edit  : Feb 25, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/LabelSDL.h"

namespace sdl
{
LabelSDL::LabelSDL(std::string text, std::string fontname, int size, SDL_Color color, SDL_Renderer* renderer) : ComponentSDL(0, 0, 0, 0, color), renderer(renderer), font(nullptr), textTexture(nullptr)
{
	font = FontManagerSDL::getInstance().getFont(fontname, size);

	setText(text, color); // Initialize text texture
}

LabelSDL::~LabelSDL()
{
	if (textTexture)
		SDL_DestroyTexture(textTexture);
}

SDL_Texture* LabelSDL::prepareText(std::string& text, SDL_Color& color)
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
	SDL_Texture* t = prepareText(text, baseColor);
	if (!t)
		return;
	textTexture = t;
	SDL_QueryTexture(t, nullptr, nullptr, &rect.w, &rect.h);
}

void LabelSDL::setText(std::string text, SDL_Color color)
{
	SDL_Texture* t = prepareText(text, color);
	if (!t)
		return;
	textTexture = t;
	SDL_QueryTexture(t, nullptr, nullptr, &rect.w, &rect.h);
}
TTF_Font* LabelSDL::getFont()
{
	return font;
}
} /* namespace ConsoleArt */
