// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

extern "C"
__declspec(dllexport)
const char * __stdcall Request(const char * _XML)
{
	return "Hello!!!";
}
