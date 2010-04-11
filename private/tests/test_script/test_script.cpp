// test_script.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const bk::wchar l_code[] = L"							\n\
	for (local i = 0; i < 10; ++i) print(i);			\n\
	print(\"\\n\");										\n\
														\n\
	function test(_a, _b)								\n\
	{													\n\
		print(\"a + b = \" + (_a + _b));				\n\
		print(\"\\n\");									\n\
	}													\n\
														\n\
	tbl <- { a = 1, b = 2 };							\n\
	arr <- [1, 2, 3];									\n\
	class cls { name = \"aaa\" };						\n\
														\n\
	foreach (i, v in arr) print(\"[\" + i + \"] = \" + v + \"; \");	\n\
	print(\"\\n\");										\n\
														\n\
";

int _tmain(int argc, _TCHAR* argv[])
{
	bk::script::machine l_script;

	bk::script::object l_root = l_script.root();

	bk::script::object l_programm = l_script.compile(l_code, L"test code");
	bk::script::object l_result = l_programm();

	bk::script::object l_test = l_root[L"test"];
	l_test(1, 2);

	bk::script::object l_tbl = l_root[L"tbl"];
	assert(l_tbl.is_table());
	bk::script::object l_arr = l_root[L"arr"];
	assert(l_arr.is_array());
	bk::script::object l_cls = l_root[L"cls"];
	assert(l_cls.is_class());

	return 0;
}

