/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#include <bikini/flash.hpp>

// GameSWF
#include "base/tu_file.h"
#include "gameswf/gameswf_player.h"
#include "gameswf/gameswf_movie_def.h"

// GameSWF requires these libs
#pragma comment(lib, "gameswf ("_PLATFORM_"!"_CONFIGURATION_")")
#pragma comment(lib, "zlib ("_PLATFORM_"!"_CONFIGURATION_")")
#pragma comment(lib, "jpeg ("_PLATFORM_"!"_CONFIGURATION_")")
#pragma comment(lib, "png ("_PLATFORM_"!"_CONFIGURATION_")")
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm")
