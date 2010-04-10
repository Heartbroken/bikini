// test_script.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const bk::wchar l_code[] =
L"														\
	for (local i = 0; i < 10; ++i) print(i);			\
";

int _tmain(int argc, _TCHAR* argv[])
{
	bk::script::machine l_script;

	bk::script::object l_programm = l_script.compile(l_code, L"Test code");

	bk::script::object l_result = l_programm();

	return 0;
}

