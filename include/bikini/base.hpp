/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

#ifdef _DEBUG
#	pragma comment(lib, "base_d")
#else
#	pragma comment(lib, "base")
#endif

#pragma warning(disable:4355)	// warning C4355: 'this' : used in base member initializer list
#pragma warning(disable:4503)	// warning C4503: '...' : decorated name length exceeded, name was truncated

#include "../config.hpp"

#if defined(XBOX)
#	include "base/base_xbox.hpp"
#elif defined(WIN32)
#	include "base/base_win32.hpp"
#endif

#include <math.h>
#include <process.h>

#include <bitset>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>

/// bikini-iii main namespace
namespace bk { /*--------------------------------------------------------------------------------*/

#include "base/defines.hpp"
#include "base/types.hpp"
#include "base/constants.hpp"
#include "base/assert.hpp"
#include "base/typelist.hpp"
#include "base/traits.hpp"
#include "base/math.hpp"
#include "base/matrix.hpp"
#include "base/quat.hpp"
#include "base/color.hpp"
#include "base/rect.hpp"
#include "base/random.hpp"
#include "base/GUID.hpp"
#include "base/functor.hpp"
#include "base/variant.hpp"
#include "base/pool.hpp"
#include "base/manager.hpp"
#include "base/fsm.hpp"
#include "base/loader.hpp"
#include "base/watch.hpp"

} /* namespace bk -------------------------------------------------------------------------------*/
