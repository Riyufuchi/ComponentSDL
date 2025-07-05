//==============================================================================
// File       : StateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Feb 26, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: ConsoleArt
//==============================================================================

#include "../inc/StateSDL.h"

namespace sdl
{
StateSDL::StateSDL(WindowInfo& winInfo) : renderer(winInfo.renderer), winInfo(winInfo)
{
}

StateSDL::~StateSDL()
{
}
void StateSDL::exitApplication()
{
	winInfo.keepRunning = false;
}
} /* namespace ConsoleArt */
