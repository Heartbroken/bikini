// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

extern bool create();
extern void destroy();

} // namespace bikini /*-------------------------------------------------------------------------*/

bool create_bikini()
{
	return bikini::create();
}
void destroy_bikini()
{
	bikini::destroy();
}

BOOL APIENTRY DllMain(HMODULE _module, DWORD _reason, LPVOID)
{
	switch (_reason)
	{
		case DLL_PROCESS_ATTACH :
		{
			commands::create();
			commands::add("Create", bk::functor_<bool>(&create_bikini));
			commands::add("Destroy", bk::functor(&destroy_bikini));
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

