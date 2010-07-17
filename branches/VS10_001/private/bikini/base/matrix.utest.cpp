/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

UTEST_FILE(matrix);

TEST(matrix, constructor_sets_elements)
{
	// when
	bk::real3x3 l_m( 1, 2, 3,
	                 4, 5, 6,
	                 7, 8, 9 );

	// then
	EXPECT_EQ(1, l_m.m11); EXPECT_EQ(2, l_m.m12); EXPECT_EQ(3, l_m.m13);
	EXPECT_EQ(4, l_m.m21); EXPECT_EQ(5, l_m.m22); EXPECT_EQ(6, l_m.m23);
	EXPECT_EQ(7, l_m.m31); EXPECT_EQ(8, l_m.m32); EXPECT_EQ(9, l_m.m33);
}

TEST(matrix, minus_op_negates_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2;
	// when
	l_m2 = -l_m1;

	// then
	EXPECT_EQ(-1, l_m2.m11); EXPECT_EQ(-2, l_m2.m12); EXPECT_EQ(-3, l_m2.m13);
	EXPECT_EQ(-4, l_m2.m21); EXPECT_EQ(-5, l_m2.m22); EXPECT_EQ(-6, l_m2.m23);
	EXPECT_EQ(-7, l_m2.m31); EXPECT_EQ(-8, l_m2.m32); EXPECT_EQ(-9, l_m2.m33);
}
TEST(matrix, assign_op_sets_corresponding_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2;
	// when
	l_m2 = l_m1;

	// then
	EXPECT_EQ(1, l_m2.m11); EXPECT_EQ(2, l_m2.m12); EXPECT_EQ(3, l_m2.m13);
	EXPECT_EQ(4, l_m2.m21); EXPECT_EQ(5, l_m2.m22); EXPECT_EQ(6, l_m2.m23);
	EXPECT_EQ(7, l_m2.m31); EXPECT_EQ(8, l_m2.m32); EXPECT_EQ(9, l_m2.m33);
}
TEST(matrix, add_assign_op_adds_corresponding_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 9, 8, 7,
	                                   6, 5, 4,
	                                   3, 2, 1 );

	// when
	l_m2 += l_m1;

	// then
	EXPECT_EQ(10, l_m2.m11); EXPECT_EQ(10, l_m2.m12); EXPECT_EQ(10, l_m2.m13);
	EXPECT_EQ(10, l_m2.m21); EXPECT_EQ(10, l_m2.m22); EXPECT_EQ(10, l_m2.m23);
	EXPECT_EQ(10, l_m2.m31); EXPECT_EQ(10, l_m2.m32); EXPECT_EQ(10, l_m2.m33);
}
TEST(matrix, sub_assign_op_subs_corresponding_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	l_m2 -= l_m1;

	// then
	EXPECT_EQ(0, l_m2.m11); EXPECT_EQ(0, l_m2.m12); EXPECT_EQ(0, l_m2.m13);
	EXPECT_EQ(0, l_m2.m21); EXPECT_EQ(0, l_m2.m22); EXPECT_EQ(0, l_m2.m23);
	EXPECT_EQ(0, l_m2.m31); EXPECT_EQ(0, l_m2.m32); EXPECT_EQ(0, l_m2.m33);
}
TEST(matrix, mul_assign_op_muls_corresponding_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	l_m2 *= l_m1;

	// then
	EXPECT_EQ(1*1, l_m2.m11); EXPECT_EQ(2*2, l_m2.m12); EXPECT_EQ(3*3, l_m2.m13);
	EXPECT_EQ(4*4, l_m2.m21); EXPECT_EQ(5*5, l_m2.m22); EXPECT_EQ(6*6, l_m2.m23);
	EXPECT_EQ(7*7, l_m2.m31); EXPECT_EQ(8*8, l_m2.m32); EXPECT_EQ(9*9, l_m2.m33);
}
TEST(matrix, div_assign_op_divs_corresponding_elements)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	l_m2 /= l_m1;

	// then
	EXPECT_EQ(1/1, l_m2.m11); EXPECT_EQ(2/2, l_m2.m12); EXPECT_EQ(3/3, l_m2.m13);
	EXPECT_EQ(4/4, l_m2.m21); EXPECT_EQ(5/5, l_m2.m22); EXPECT_EQ(6/6, l_m2.m23);
	EXPECT_EQ(7/7, l_m2.m31); EXPECT_EQ(8/8, l_m2.m32); EXPECT_EQ(9/9, l_m2.m33);
}
TEST(matrix, mul_scalar_assign_op_muls_elements_by_scalar)
{
	// given
	bk::real3x3 l_m( 1, 2, 3,
	                 4, 5, 6,
	                 7, 8, 9 );

	// when
	l_m *= 2;

	// then
	EXPECT_EQ(1*2, l_m.m11); EXPECT_EQ(2*2, l_m.m12); EXPECT_EQ(3*2, l_m.m13);
	EXPECT_EQ(4*2, l_m.m21); EXPECT_EQ(5*2, l_m.m22); EXPECT_EQ(6*2, l_m.m23);
	EXPECT_EQ(7*2, l_m.m31); EXPECT_EQ(8*2, l_m.m32); EXPECT_EQ(9*2, l_m.m33);
}
TEST(matrix, div_scalar_assign_op_divs_elements_by_scalar)
{
	// given
	bk::real3x3 l_m( 1, 2, 3,
	                 4, 5, 6,
	                 7, 8, 9 );

	// when
	l_m /= 0.5f;

	// then
	EXPECT_EQ(1*2, l_m.m11); EXPECT_EQ(2*2, l_m.m12); EXPECT_EQ(3*2, l_m.m13);
	EXPECT_EQ(4*2, l_m.m21); EXPECT_EQ(5*2, l_m.m22); EXPECT_EQ(6*2, l_m.m23);
	EXPECT_EQ(7*2, l_m.m31); EXPECT_EQ(8*2, l_m.m32); EXPECT_EQ(9*2, l_m.m33);
}

TEST(matrix, add_op_makes_per_element_sum)
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
	EXPECT_EQ(10, l_m3.m11); EXPECT_EQ(10, l_m3.m12); EXPECT_EQ(10, l_m3.m13);
	EXPECT_EQ(10, l_m3.m21); EXPECT_EQ(10, l_m3.m22); EXPECT_EQ(10, l_m3.m23);
	EXPECT_EQ(10, l_m3.m31); EXPECT_EQ(10, l_m3.m32); EXPECT_EQ(10, l_m3.m33);
}
TEST(matrix, sub_op_makes_per_element_diff)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	bk::real3x3 l_m3 = l_m1 - l_m2;

	// then
	EXPECT_EQ(0, l_m3.m11); EXPECT_EQ(0, l_m3.m12); EXPECT_EQ(0, l_m3.m13);
	EXPECT_EQ(0, l_m3.m21); EXPECT_EQ(0, l_m3.m22); EXPECT_EQ(0, l_m3.m23);
	EXPECT_EQ(0, l_m3.m31); EXPECT_EQ(0, l_m3.m32); EXPECT_EQ(0, l_m3.m33);
}
TEST(matrix, mul_op_makes_per_element_prod)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	bk::real3x3 l_m3 = l_m1 * l_m2;

	// then
	EXPECT_EQ(1*1, l_m3.m11); EXPECT_EQ(2*2, l_m3.m12); EXPECT_EQ(3*3, l_m3.m13);
	EXPECT_EQ(4*4, l_m3.m21); EXPECT_EQ(5*5, l_m3.m22); EXPECT_EQ(6*6, l_m3.m23);
	EXPECT_EQ(7*7, l_m3.m31); EXPECT_EQ(8*8, l_m3.m32); EXPECT_EQ(9*9, l_m3.m33);
}
TEST(matrix, div_op_makes_per_element_quot)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	bk::real3x3 l_m3 = l_m1 / l_m2;

	// then
	EXPECT_EQ(1/1, l_m3.m11); EXPECT_EQ(2/2, l_m3.m12); EXPECT_EQ(3/3, l_m3.m13);
	EXPECT_EQ(4/4, l_m3.m21); EXPECT_EQ(5/5, l_m3.m22); EXPECT_EQ(6/6, l_m3.m23);
	EXPECT_EQ(7/7, l_m3.m31); EXPECT_EQ(8/8, l_m3.m32); EXPECT_EQ(9/9, l_m3.m33);
}
TEST(matrix, mul_scalar_op_muls_elements_by_scalar)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 );

	// when
	bk::real3x3 l_m2 = l_m1 * 2;

	// then
	EXPECT_EQ(1*2, l_m2.m11); EXPECT_EQ(2*2, l_m2.m12); EXPECT_EQ(3*2, l_m2.m13);
	EXPECT_EQ(4*2, l_m2.m21); EXPECT_EQ(5*2, l_m2.m22); EXPECT_EQ(6*2, l_m2.m23);
	EXPECT_EQ(7*2, l_m2.m31); EXPECT_EQ(8*2, l_m2.m32); EXPECT_EQ(9*2, l_m2.m33);
}
TEST(matrix, div_scalar_op_divs_elements_by_scalar)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 );

	// when
	bk::real3x3 l_m2 = l_m1 / 0.5f;

	// then
	EXPECT_EQ(1*2, l_m2.m11); EXPECT_EQ(2*2, l_m2.m12); EXPECT_EQ(3*2, l_m2.m13);
	EXPECT_EQ(4*2, l_m2.m21); EXPECT_EQ(5*2, l_m2.m22); EXPECT_EQ(6*2, l_m2.m23);
	EXPECT_EQ(7*2, l_m2.m31); EXPECT_EQ(8*2, l_m2.m32); EXPECT_EQ(9*2, l_m2.m33);
}

TEST(matrix, equal_op_compares_two_matrices)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	bool l_r = (l_m1 == l_m2);

	// then
	EXPECT_TRUE(l_r);
}
TEST(matrix, not_equal_op_compares_two_matrices)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 1, 2, 3,
	                                   4, 5, 6,
	                                   7, 8, 9 );

	// when
	bool l_r = (l_m1 != l_m2);

	// then
	EXPECT_FALSE(l_r);
}

TEST(matrix, transpose_fn_makes_transposed_matrix)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 );

	// when
	bk::real3x3 l_m2 = bk::transpose(l_m1);

	// then
	EXPECT_EQ(1, l_m2.m11); EXPECT_EQ(4, l_m2.m12); EXPECT_EQ(7, l_m2.m13);
	EXPECT_EQ(2, l_m2.m21); EXPECT_EQ(5, l_m2.m22); EXPECT_EQ(8, l_m2.m23);
	EXPECT_EQ(3, l_m2.m31); EXPECT_EQ(6, l_m2.m32); EXPECT_EQ(9, l_m2.m33);
}
TEST(matrix, minor_fn_calcs_matrix_minor)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 );

	// when
	bk::real2x2 l_m2 = bk::minor_<1, 1>(l_m1);

	// then
	EXPECT_EQ(1, l_m2.m11); EXPECT_EQ(3, l_m2.m12);
	EXPECT_EQ(7, l_m2.m21); EXPECT_EQ(9, l_m2.m22);
}
TEST(matrix, determinant_fn_calcs_matrix_determinant)
{
	// given
	bk::real3x3 l_m1( 1, 2, 0,
	                  0, 1, 0,
	                  0, 0, 1 );

	// when
	bk::real l_d = bk::determinant(l_m1);

	// then
	EXPECT_EQ(1, l_d);
}
TEST(matrix, inverse_fn_makes_inverted_matrix)
{
	// given
	bk::real3x3 l_m1( 2, 2, 0,
	                  0, 2, 0,
	                  0, 2, 2 );

	// when
	bk::real3x3 l_m2 = bk::inverse(l_m1);

	// then
	EXPECT_EQ(0.5, l_m2.m11); EXPECT_EQ(-.5, l_m2.m12); EXPECT_EQ(0.0, l_m2.m13);
	EXPECT_EQ(0.0, l_m2.m21); EXPECT_EQ(0.5, l_m2.m22); EXPECT_EQ(0.0, l_m2.m23);
	EXPECT_EQ(0.0, l_m2.m31); EXPECT_EQ(-.5, l_m2.m32); EXPECT_EQ(0.5, l_m2.m33);
}
TEST(matrix, mul_fn_multiplies_two_matrices)
{
	// given
	bk::real3x3 l_m1( 1, 2, 3,
	                  4, 5, 6,
	                  7, 8, 9 ), l_m2( 9, 8, 7,
	                                   6, 5, 4,
	                                   3, 2, 1 );

	// when
	bk::real3x3 l_m3 = bk::mul(l_m1, l_m2);

	// then
	EXPECT_EQ( 30, l_m3.m11); EXPECT_EQ( 24, l_m3.m12); EXPECT_EQ( 18, l_m3.m13);
	EXPECT_EQ( 84, l_m3.m21); EXPECT_EQ( 69, l_m3.m22); EXPECT_EQ( 54, l_m3.m23);
	EXPECT_EQ(138, l_m3.m31); EXPECT_EQ(114, l_m3.m32); EXPECT_EQ( 90, l_m3.m33);
}
