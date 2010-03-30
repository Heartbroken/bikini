// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

extern bool create();
extern void destroy();

} // namespace bikini /*-------------------------------------------------------------------------*/

BOOL APIENTRY DllMain(HMODULE _module, DWORD _reason, LPVOID)
{
	switch (_reason)
	{
		case DLL_PROCESS_ATTACH :
		{
			commands::create();
			commands::add("Create", bk::functor_<bool>(&bikini::create));
			commands::add("Destroy", bk::functor(&bikini::destroy));
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
			commands::remove("Destroy");
			commands::remove("Create");
			commands::destroy();
			break;
		}
	}
	return TRUE;
}

