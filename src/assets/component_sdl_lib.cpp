//==============================================================================
// File       : ConsoleLib.cpp
// Author     : riyufuchi
// Created on : Mar 27, 2024
// Last edit  : Dec 23, 2025
// Copyright  : Copyright (c) 2024, riyufuchi
// Description: consolelib
//==============================================================================

#include "../component_sdl_lib/component_sdl_lib.h"

namespace sdl
{
std::string aboutLibrary()
{
	return std::format("ComponentSDL library {}\n{}\nCompiled on: {} {}\nC++ version: {}", _VERSION, _COPYRIGHT_HEADER, __DATE__, __TIME__, __cplusplus);
}
}
