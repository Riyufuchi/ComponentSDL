//==============================================================================
// File       : TextSDL.cpp
// Author     : riyufuchi
// Created on : Dec 2, 2025
// Last edit  : Dec 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ComponentSDL
//==============================================================================

#include "../inc/TextSDL.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "../inc/external/stb_truetype.h"

namespace sdl
{

TextSDL::TextSDL(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, float pixelHeight, SDL_Color color) : renderer(renderer), texture(nullptr),
	color(color), textText(text), fontHeight(pixelHeight), textWidth(0), textHeight(0)
{
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
		return;
	}

	texture = renderText(text, color);
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

	float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontHeight);

	int width = 0;
	int height = (int) fontHeight;

	int advance, lsb;

	// Measure width first
	for (char c : text)
	{
		stbtt_GetCodepointHMetrics(&fontInfo, c, &advance, &lsb);
		width += int(advance * scale);
	}

	textWidth = width;
	textHeight = height;

	std::vector<unsigned char> bitmap(width * height);
	memset(bitmap.data(), 0, width * height);

	int x = 0;

	for (char c : text)
	{
		int ax, c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointHMetrics(&fontInfo, c, &ax, &lsb);
		stbtt_GetCodepointBitmapBox(&fontInfo, c, scale, scale, &c_x1, &c_y1,
				&c_x2, &c_y2);

		int w = c_x2 - c_x1;
		int h = c_y2 - c_y1;

		std::vector<unsigned char> glyph(w * h);

		stbtt_MakeCodepointBitmap(&fontInfo, glyph.data(), w, h, w, scale,
				scale, c);

		for (int gy = 0; gy < h; gy++)
		{
			for (int gx = 0; gx < w; gx++)
			{
				int dstX = x + gx + c_x1;
				int dstY = gy - c_y1 + (int) (fontHeight * 0.8f);

				if (dstX >= 0 && dstX < width && dstY >= 0 && dstY < height)
					bitmap[dstY * width + dstX] = glyph[gy * w + gx];
			}
		}

		x += int(ax * scale);
	}

	// SDL2 Surface RGBA8888
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
			SDL_PIXELFORMAT_RGBA8888);

	if (!surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return nullptr;
	}

	Uint32* pixels = (Uint32*) surface->pixels;

	for (int i = 0; i < width * height; i++)
	{
		Uint8 alpha = bitmap[i];

		// SDL_PIXELFORMAT_RGBA8888 = 0xRRGGBBAA
		pixels[i] = ((Uint32) color.r << 24) | ((Uint32) color.g << 16)
				| ((Uint32) color.b << 8) | (Uint32) alpha;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

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
