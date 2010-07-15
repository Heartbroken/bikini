/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

define_utest(matrix);
//namespace bk { int matrix_utest = 0; }

TEST(matrix, constructor_accepts_elements_values)
{
	// when
	bk::real3x3 l_m( 1, 2, 3,
					 4, 5, 6,
					 7, 8, 9 );

	// then
	EXPECT_EQ(1, l_m.m11);
	EXPECT_EQ(2, l_m.m12);
	EXPECT_EQ(3, l_m.m13);
	EXPECT_EQ(4, l_m.m21);
	EXPECT_EQ(5, l_m.m22);
	EXPECT_EQ(6, l_m.m23);
	EXPECT_EQ(7, l_m.m31);
	EXPECT_EQ(8, l_m.m32);
	EXPECT_EQ(9, l_m.m33);
}
TEST(matrix, assign_operator_assigns_elements_values)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
					  4, 5, 6,
					  7, 8, 9 ), l_m2;
	// when
	l_m2 = l_m1;

	// then
	EXPECT_EQ(1, l_m2.m11);
	EXPECT_EQ(2, l_m2.m12);
	EXPECT_EQ(3, l_m2.m13);
	EXPECT_EQ(4, l_m2.m21);
	EXPECT_EQ(5, l_m2.m22);
	EXPECT_EQ(6, l_m2.m23);
	EXPECT_EQ(7, l_m2.m31);
	EXPECT_EQ(8, l_m2.m32);
	EXPECT_EQ(9, l_m2.m33);
}
TEST(matrix, add_operator_adds_per_element)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
					  4, 5, 6,
					  7, 8, 9 ), l_m2( 9, 8, 7,
									   6, 5, 4,
									   3, 2, 1 );

	// when
	bk::real3x3 l_m3 = l_m1 + l_m2;

	// then
	EXPECT_EQ(10, l_m3.m11);
	EXPECT_EQ(10, l_m3.m12);
	EXPECT_EQ(10, l_m3.m13);
	EXPECT_EQ(10, l_m3.m21);
	EXPECT_EQ(10, l_m3.m22);
	EXPECT_EQ(10, l_m3.m23);
	EXPECT_EQ(10, l_m3.m31);
	EXPECT_EQ(10, l_m3.m32);
	EXPECT_EQ(10, l_m3.m33);
}
