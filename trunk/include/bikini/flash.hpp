/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "flash_d")
//#	pragma comment(lib, "avmplus_d")
//#	pragma comment(lib, "mmgc_d")
//#	pragma comment(lib, "nanojit_d")
#else
#	pragma comment(lib, "flash")
//#	pragma comment(lib, "avmplus")
//#	pragma comment(lib, "mmgc")
//#	pragma comment(lib, "nanojit")
#endif

//#pragma comment(lib, "winmm")
//#pragma comment(lib, "shlwapi")

//#define AVMPLUS_IA32
//#pragma warning(disable: 4291)
//#include "flash/tamarin/avmplus.h"

#include "base.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

#include "flash/loader.hpp"
#include "flash/renderer.hpp"
//#include "flash/swftagtypes.hpp"
//#include "flash/swfstream.hpp"
#include "flash/player.hpp"
//#include "flash/actionscript.hpp"
#include "flash/objects.hpp"

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
