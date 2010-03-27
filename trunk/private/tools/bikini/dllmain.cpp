// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

bool test_command(int _a, const bk::astring &_b)
{
	return true;
}

BOOL APIENTRY DllMain(HMODULE _module, DWORD _reason, LPVOID)
{
	switch (_reason)
	{
	case DLL_PROCESS_ATTACH :
		commands::create();
		commands::add_command("Test", bk::functor_<bool, int, const bk::astring&>(&test_command));
		break;
	case DLL_THREAD_ATTACH :
		break;
	case DLL_THREAD_DETACH :
		break;
	case DLL_PROCESS_DETACH :
		commands::destroy();
		break;
	}
	return TRUE;
}

