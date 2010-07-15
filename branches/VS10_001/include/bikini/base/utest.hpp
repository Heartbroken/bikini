/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

void run_unit_tests();

#define declare_utest(name)						\
	extern int name##_utest;					\
	static int s_##name##_utest = name##_utest;

#define define_utest(name)	\
	namespace bk { int name##_utest = 0; }
