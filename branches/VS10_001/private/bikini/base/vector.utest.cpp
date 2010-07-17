/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

UTEST_FILE(vector);

TEST(vector, constructor_sets_elements)
{
	// when
	bk::real3 l_v(1, 2, 3);

	// then
	EXPECT_EQ(1, l_v.x);
	EXPECT_EQ(2, l_v.y);
	EXPECT_EQ(3, l_v.z);
}

TEST(vector, length_fn_tells_vector_length)
{
	// given
	bk::real3 l_v(1, 2, 3);

	// when
	bk::real l_length = bk::length(l_v);

	// then
	EXPECT_EQ(3.7416574954986572, l_length);
}
