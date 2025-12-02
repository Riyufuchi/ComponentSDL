//==============================================================================
// File       : ContentPanelSDL.h
// Author     : riyufuchi
// Created on : Feb 23, 2025
// Last edit  : Mar 24, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: This class assumes ownership of the components
//==============================================================================

#ifndef CONSOLEART_SDL_COMPONENTS_CONTENTPANELSDL_H_
#define CONSOLEART_SDL_COMPONENTS_CONTENTPANELSDL_H_

#include <vector>
#include <utility>
#include <unordered_map>

#include "ComponentSDL.h"

namespace sdl
{
class ContentPanelSDL: public ComponentSDL
{
private:
	std::unordered_map<int, std::vector<ComponentSDL*>> componentsAtY;
	std::unordered_map<int, int> widthAtY;
public:
	ContentPanelSDL();
	ContentPanelSDL(int x, int y);
	~ContentPanelSDL();
	virtual void draw(SDL_Renderer* renderer) override;
	void tickOnClick();
	void addComponent(int y, ComponentSDL* component);
	void reposeContent();
	void checkHoverOverContent(float& x, float& y);
	void clear();
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_SDL_COMPONENTS_CONTENTPANELSDL_H_ */
