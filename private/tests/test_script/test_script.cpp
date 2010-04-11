// test_script.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const bk::wchar l_code[] = L"							\n\
	for (local i = 0; i < 10; ++i) print(i);			\n\
	print(\"\\n\");										\n\
	function test(_a, _b)								\n\
	{													\n\
		print(\"a + b = \" + (_a + _b));				\n\
		print(\"\\n\");									\n\
	}													\n\
";

int _tmain(int argc, _TCHAR* argv[])
{
	bk::script::machine l_script;

	bk::script::object l_programm = l_script.compile(l_code, L"test code");
	bk::script::object l_result = l_programm();

	bk::script::object l_test = l_script.root()[L"test"];
	l_test(1, 2);

	return 0;
}

