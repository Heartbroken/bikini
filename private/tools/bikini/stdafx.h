// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here

// bikini-iii
#include <bikini.hpp>

// bikini-iii external
#include <pugixml/pugixml.hpp>
#pragma comment(lib, "pugixml ("_PLATFORM_"!"_CONFIGURATION_")")

// internal
#include "bikini.h"
