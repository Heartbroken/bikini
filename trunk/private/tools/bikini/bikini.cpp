// bikini.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

extern "C"
__declspec(dllexport)
const wchar_t * __stdcall Request(const wchar_t * _XML)
{
	return L"Hello!!!";
}

//extern "C"
//__declspec(dllexport)
//void __stdcall Request2()
//{
//}
