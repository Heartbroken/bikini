/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

bool run_unit_tests()
{
	int argc = 1;
	wchar_t** argv = (wchar_t**)_alloca(sizeof(wchar_t*));
	argv[0] = (wchar_t*)_alloca(MAX_PATH * sizeof(wchar_t));
	GetModuleFileNameW(GetModuleHandleW(NULL), argv[0], MAX_PATH);

	testing::InitGoogleTest(&argc, argv);

	return (RUN_ALL_TESTS() == 0);
}

} /* namespace bk -------------------------------------------------------------------------------*/
