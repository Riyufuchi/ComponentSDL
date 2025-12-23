//==============================================================================
// File       : StateSDL.cpp
// Author     : riyufuchi
// Created on : Feb 26, 2025
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: consoleart
//==============================================================================

#include "../component_sdl_lib/base/state_sdl.h"

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
} /* namespace consoleart */
