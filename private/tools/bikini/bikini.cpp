// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

extern "C" __declspec(dllexport) const char * __stdcall bikini_command(const char * _XML)
{
	return "Hello!!!";
}
