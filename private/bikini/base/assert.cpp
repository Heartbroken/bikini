/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

#if defined(XBOX)

#elif defined(WIN32)

bool ARI(wchar const* _expression, wchar const* _file, int _line, wchar const* _function, wchar const* _message)
{
	std::wstringstream l_cerr;
	l_cerr << L"Assertion failed ...\n";
	l_cerr << L"    Expression: " << wstring(_expression) << L"\n";
	l_cerr << L"    File: " << wstring(_file) << L"(" <<_line << L")\n";
	l_cerr << L"    Function: " << wstring(_function) << L"\n";
	if(_message) l_cerr << L"    " << wstring(_message) << L"\n";

	char l_oem[1024];
	CharToOemBuffW(l_cerr.str().c_str(), l_oem, 1024);

	std::cerr << l_oem;

	wstring l_message = format(L"%s\n\nFile: %s(%d)\nFunction: %s\n%s\n\nHit <Retry> to debug", _expression, _file, _line, _function, _message ? _message : L"").wstr;

	switch(MessageBoxW(0, l_message.c_str(), L"bikini | assertion failed", MB_ABORTRETRYIGNORE|MB_ICONERROR))
	{
		case IDABORT : std::cerr << L"... terminating\n"; Sleep(1); _exit(-1);
		case IDRETRY : std::cerr << L"... debugging\n"; return false;
		case IDIGNORE : std::cerr << L"... ignored\n"; return true;
	}
	return true;
}

#endif

} /* namespace bk -------------------------------------------------------------------------------*/
