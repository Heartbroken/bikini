/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

TEST(base_math, matrix_assign)
{
	bk::real3 l_v(1, 2, 3);
	EXPECT_EQ(1, l_v.x);
	EXPECT_EQ(2, l_v.y);
	EXPECT_EQ(3, l_v.z);
}
