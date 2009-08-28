/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "system_d")
#else
#	pragma comment(lib, "system")
#endif

#include "base.hpp"

#if defined(WIN32)
#	include "system/system_win32.hpp"
#endif

namespace bk { /*--------------------------------------------------------------------------------*/

#include "system/time.hpp"
#include "system/thread.hpp"
#include "system/ticker.hpp"
#include "system/application.hpp"
#include "system/device.hpp"
#include "system/video.hpp"
#include "system/audio.hpp"
#include "system/input.hpp"
#include "system/window.hpp"

} /* namespace bk -------------------------------------------------------------------------------*/
