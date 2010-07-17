/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

UTEST_FILE(quat);

TEST(quat, constructor_sets_elements)
{
	// when
	bk::quat l_q(0, 0, 0, 1);

	// then
	EXPECT_EQ(0, l_q.i);
	EXPECT_EQ(0, l_q.j);
	EXPECT_EQ(0, l_q.k);
	EXPECT_EQ(1, l_q.r);
}

