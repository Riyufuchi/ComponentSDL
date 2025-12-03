//==============================================================================
// File       : TextSDL.cpp
// Author     : riyufuchi
// Created on : Dec 02, 2025
// Last edit  : Dec 03, 2025
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
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

SDL_Texture* TextSDL::renderText(const std::string& text, SDL_Color color)
{
	if (text.empty())
		return nullptr;

	textText = text;

	float scale = stbtt_ScaleForPixelHeight(&fontInfo, fontHeight);

	int width = 0;
	// Ascender and descender calculations help determine actual vertical space needed, not just fontHeight
	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
	// Calculate vertical offset to align the text baseline correctly within the bitmap
	int baseline = (int) (ascent * scale);
	int height = (int) (ascent - descent + lineGap) * scale;

	// Recalculate width for consistency if metrics change
	int advance, lsb;
	for (char c : text)
	{
		stbtt_GetCodepointHMetrics(&fontInfo, c, &advance, &lsb);
		width += int(advance * scale);
	}

	// Handle edge case if width/height is zero
	if (width <= 0 || height <= 0)
	{
		return nullptr;
	}

	textWidth = width; // Store in member variables if needed
	textHeight = height;

	std::vector<unsigned char> bitmap(width * height);
	memset(bitmap.data(), 0, width * height);

	// --- CRITICAL MISSING STEP: Draw glyphs into the bitmap ---
	int x = 0;
	for (char c : text)
	{
		int charWidth, charHeight, offsetX, offsetY;
		unsigned char* charBitmap = stbtt_GetCodepointBitmap(&fontInfo, scale,
				scale, c, &charWidth, &charHeight, &offsetX, &offsetY);

		// Copy the single glyph bitmap into the main text bitmap
		for (int j = 0; j < charHeight; ++j)
		{
			for (int i = 0; i < charWidth; ++i)
			{
				// Calculate target position in the main bitmap
				// Use baseline offset calculated earlier
				int targetX = x + i + offsetX;
				int targetY = baseline + j + offsetY;

				// Ensure within bounds (safety check)
				if (targetX >= 0 && targetX < width && targetY >= 0 && targetY < height)
				{
					// stbtt_GetCodepointBitmap returns a luminance (alpha) value
					bitmap[targetY * width + targetX] = charBitmap[j * charWidth + i];
				}
			}
		}

		// stbtt_GetCodepointBitmap allocates memory internally that needs freeing
		stbtt_FreeBitmap(charBitmap, fontInfo.userdata);

		// Advance the current X position
		stbtt_GetCodepointHMetrics(&fontInfo, c, &advance, &lsb);
		x += int(advance * scale);
	}
	// --- End of drawing logic ---

	// Use a format that is guaranteed to be supported and defined by SDL
	// We can optimize the surface creation to use a single channel for better performance
	// if we use a specific SDL format that matches stb's output (Luminance only)
	Uint32 format = SDL_PIXELFORMAT_RGBA32;
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
			format);

	if (!surface)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return nullptr;
	}

	if (SDL_LockSurface(surface) == 0)
	{
		Uint32* pixels = static_cast<Uint32*>(surface->pixels);

		for (int i = 0; i < width * height; i++)
		{
			Uint8 alpha = bitmap[i];

			// Map the input color, using the bitmap value as the alpha channel
			pixels[i] = SDL_MapRGBA(surface->format, color.r, color.g, color.b,
					alpha);
		}

		SDL_UnlockSurface(surface);
	}
	else
	{
		SDL_Log("Failed to lock surface: %s", SDL_GetError());
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (!tex)
	{
		SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
	}
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
