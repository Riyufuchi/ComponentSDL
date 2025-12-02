//==============================================================================
// File       : Button.h
// Author     : riyufuchi
// Created on : Feb 18, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_GUI_UTILS_IMAGE_BUTTON_H_
#define CONSOLEART_GUI_UTILS_IMAGE_BUTTON_H_

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <utility>

#include "ComponentSDL.h"

namespace sdl
{
class ImageButtonSDL : public ComponentSDL
{
private:
	SDL_Texture* texture;
	SDL_Texture* textureHover;
	std::function<void()> onClickEvt;
public:
	ImageButtonSDL(int x, int y, int width, int height, SDL_Texture* texture, SDL_Texture* textureHover, std::function<void()> callback = nullptr);
	ImageButtonSDL(int x, int y, int width, int height, std::pair<SDL_Texture*, SDL_Texture*> texturePair, std::function<void()> callback = nullptr);
	ImageButtonSDL(int width, int height, std::pair<SDL_Texture*, SDL_Texture*> texturePair, std::function<void()> callback = nullptr);
	~ImageButtonSDL();
	virtual void draw(SDL_Renderer* renderer) override;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_GUI_UTILS_BUTTON_H_ */
