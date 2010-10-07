/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

bool run_unittests();

#define DECLARE_UTEST(NAME)						\
	extern int NAME##_utest;					\
	static int s_##NAME##_utest = NAME##_utest;

#define UTEST_FILE(NAME)						\
	int NAME##_utest = 0;
	//namespace bk { int NAME##_utest = 0; }
