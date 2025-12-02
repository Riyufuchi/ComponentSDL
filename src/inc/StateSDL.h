//==============================================================================
// File       : StateSDL.h
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Dec 02, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#ifndef CONSOLEART_SDL_ABSTRACT_STATESDL_H_
#define CONSOLEART_SDL_ABSTRACT_STATESDL_H_

#include "SDL3/SDL.h"

namespace sdl
{
struct WindowInfo
{
	int w;
	int h;
	float mouseX;
	float mouseY;
	bool keepRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
class StateSDL
{
protected:
	SDL_Color backgroundColor {80, 80, 80, 255};
	SDL_Renderer* renderer;
	WindowInfo& winInfo;
public:
	StateSDL(WindowInfo& winInfo);
	virtual ~StateSDL();
	void exitApplication();
	virtual void handleTick(SDL_Event& event) = 0;
	virtual void render() = 0;
	virtual void onReturn() = 0;
	virtual void onWindowResize() = 0;
};
} /* namespace ConsoleArt */
#endif /* CONSOLEART_SDL_ABSTRACT_STATESDL_H_ */
