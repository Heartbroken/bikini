// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE _module, DWORD _reason, LPVOID)
{
	switch (_reason)
	{
		case DLL_PROCESS_ATTACH :
		{
			commands::create();
			commands::add("CreateWorkspace", bk::functor_<bool>(get_bikini(), &bikini::create));
			break;
		}
		case DLL_THREAD_ATTACH :
		{
			break;
		}
		case DLL_THREAD_DETACH :
		{
			break;
		}
		case DLL_PROCESS_DETACH :
		{
			commands::remove("CreateWorkspace");
			commands::destroy();
			break;
		}
	}
	return TRUE;
}

