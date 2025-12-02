//==============================================================================
// File       : TextSDL.cpp
// Author     : riyufuchi
// Created on : Dec 2, 2025
// Last edit  : Dec 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ComponentSDL
//==============================================================================

#include "../inc/TextSDL.h"

namespace sdl
{

TextSDL::TextSDL(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, float pixelHeight, SDL_Color color) : renderer(renderer),
		texture(nullptr), color(color), textText(text), fontHeight(pixelHeight), textWidth(0), textHeight(0)
{
	// Load font file into memory
	std::ifstream file(fontPath, std::ios::binary | std::ios::ate);
	if (!file)
	{
		SDL_Log("Failed to open font file: %s", fontPath.c_str());
		return;
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	fontBuffer.resize(size);
	if (!file.read((char*) fontBuffer.data(), size))
	{
		SDL_Log("Failed to read font file: %s", fontPath.c_str());
		return;
	}

	if (!stbtt_InitFont(&fontInfo, fontBuffer.data(), 0))
	{
		SDL_Log("Failed to init font: %s", fontPath.c_str());
	}
	this->texture = renderText(text, color);
}

TextSDL::~TextSDL()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

SDL_Texture* TextSDL::renderText(const std::string& text, SDL_Color color)
{
	if (text.empty())
		return nullptr;

	textText = text;

	int width = 0, height = (int)fontHeight;
	std::vector<unsigned char> bitmap;

	// First pass: compute width
	int advance, lsb;
	for (char c : text)
	{
		stbtt_GetCodepointHMetrics(&fontInfo, c, &advance, &lsb);
		width += advance * fontHeight / stbtt_ScaleForPixelHeight(&fontInfo, fontHeight);
	}

	bitmap.resize(width * height);
	std::memset(bitmap.data(), 0, bitmap.size());

	int x = 0;
	float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontHeight);

	int ax;
	int c_x1, c_y1, c_x2, c_y2;
	int w, h;
	for (char c : text)
	{
		stbtt_GetCodepointHMetrics(&fontInfo, c, &ax, &lsb);
		stbtt_GetCodepointBitmapBox(&fontInfo, c, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

		w = c_x2 - c_x1;
		h = c_y2 - c_y1;
		std::vector<unsigned char> glyph(w * h);

		stbtt_MakeCodepointBitmap(&fontInfo, glyph.data(), w, h, w, scale, scale, c);

		// Blit glyph into main bitmap
		for (int gy = 0; gy < h; gy++)
		{
			for (int gx = 0; gx < w; gx++)
			{
				int dstX = x + gx + c_x1;
				int dstY = gy - c_y1;
				if (dstX >= 0 && dstX < width && dstY >= 0 && dstY < height)
				{
					bitmap[dstY * width + dstX] = glyph[gy * w + gx];
				}
			}
		}

		x += ax * scale;
	}

	// Convert bitmap to SDL surface (SDL3)
	SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);
	Uint32* pixels = static_cast<Uint32*>(surface->pixels);

	textWidth = width;
	textHeight = height;

	for (int i = 0; i < width * height; i++)
	{
		Uint8 alpha = bitmap[i];
		pixels[i] = (alpha << 24) | (color.b << 16) | (color.g << 8) | (color.r);
		// SDL3 uses ABGR for SDL_PIXELFORMAT_RGBA8888
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);

	return tex;
}

void TextSDL::setText(const std::string& text)
{
	setText(text, color);
}

void TextSDL::setText(const std::string& text, SDL_Color& color)
{
	this->texture = renderText(text, color);
}

SDL_Texture* TextSDL::getTexture() const
{
	return texture;
}

int TextSDL::getWidth() const
{
	return textWidth;
}

int TextSDL::getHeight() const
{
	return textHeight;
}

SDL_Renderer* TextSDL::getRenderer() const
{
	return renderer;
}

const std::string& TextSDL::getText() const
{
	return textText;
}

float TextSDL::getFontSize() const
{
	return fontHeight;
}

} /* namespace sdl */
