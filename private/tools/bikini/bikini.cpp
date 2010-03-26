// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

extern "C"
__declspec(dllexport)
const bk::wchar* __stdcall request(const bk::wchar* _command)
{
	return L"Hello!!!";
}
