// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

namespace bikini { /*----------------------------------------------------------------------------*/

extern void create();
extern void destroy();

} // namespace bikini /*-------------------------------------------------------------------------*/

bool test_command(bk::sint _a, const bk::astring &_b)
{
	return true;
}

BOOL APIENTRY DllMain(HMODULE _module, DWORD _reason, LPVOID)
{
	switch (_reason)
	{
		case DLL_PROCESS_ATTACH :
		{
			commands::create();
			bk::functor_<bool, bk::sint, const bk::astring&> l_command(&test_command);
			commands::add("Test", l_command);
			bikini::create();
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
			bikini::destroy();
			commands::destroy();
			break;
		}
	}
	return TRUE;
}

