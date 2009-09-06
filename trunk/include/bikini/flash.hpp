/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#include "base.hpp"

#pragma comment(lib, "flash ("_PLATFORM"!"_CONFIGURATION")")

namespace gameswf {

struct player;

}

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

#include "flash/loader.hpp"
#include "flash/renderer.hpp"
#include "flash/player.hpp"
#include "flash/objects.hpp"

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
