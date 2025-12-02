//==============================================================================
// File       : TextSDL.h
// Author     : riyufuchi
// Created on : Dec 2, 2025
// Last edit  : Dec 2, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ComponentSDL
//==============================================================================

#ifndef SRC_INC_TEXTSDL_H_
#define SRC_INC_TEXTSDL_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <cstring>
#include <fstream>


#include "SDL3/SDL.h"
#include "../external/stb_truetype.h"

namespace sdl
{

class TextSDL
{
private:
	SDL_Renderer* renderer;
	stbtt_fontinfo fontInfo;
	SDL_Texture* texture;
	SDL_Color color;
	std::string textText;
	float fontHeight;
	int textWidth, textHeight;
	std::vector<unsigned char> fontBuffer;
public:
	TextSDL(SDL_Renderer* renderer, const std::string& fontPath, const std::string& text, float pixelHeight, SDL_Color color);
	virtual ~TextSDL();
	SDL_Texture* renderText(const std::string& text, SDL_Color color);
	void setText(const std::string& text);
	void setText(const std::string& text, SDL_Color& color);
	const std::string& getText() const;
	SDL_Texture* getTexture() const;
	int getWidth() const;
	int getHeight() const;
	float getFontSize() const;
	SDL_Renderer* getRenderer() const;

};

} /* namespace sdl */

#endif /* SRC_INC_TEXTSDL_H_ */
