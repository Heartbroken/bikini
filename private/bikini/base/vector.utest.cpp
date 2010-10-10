/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk
{

UTEST_FILE(vector);

namespace utest
{

TEST(vector, constructor_sets_elements)
{
	// when
	bk::real3 l_v(1, 2, 3);

	// then
	EXPECT_EQ(1, l_v.x);
	EXPECT_EQ(2, l_v.y);
	EXPECT_EQ(3, l_v.z);
}

TEST(vector, dot_fn_calcs_two_vectors_dot_prod)
{
	// given
	bk::real3 l_v1(1, 2, 3), l_v2(3, 2, 1);

	// when
	bk::real l_dot = bk::dot(l_v1, l_v2);

	// then
	EXPECT_EQ(10, l_dot);
}

TEST(vector, length_fn_calcs_vector_length)
{
	// given
	bk::real3 l_v(1, 2, 3);

	// when
	bk::real l_length = bk::length(l_v);

	// then
	EXPECT_EQ(3.7416574954986572, l_length);
}
TEST(vector, length2_fn_calcs_vector_squared_length)
{
	// given
	bk::real3 l_v(1, 2, 3);

	// when
	bk::real l_length2 = bk::length2(l_v);

	// then
	EXPECT_EQ(14, l_length2);
}

TEST(vector, normalize_fn_calcs_normalized_vector)
{
	// given
	bk::real3 l_v1(1, 2, 3);

	// when
	bk::real3 l_v2 = bk::normalize(l_v1);

	// then
	bk::real l_length1 = bk::length(l_v1);
	bk::real l_length2 = bk::length(l_v2);
	bk::real l_dot = bk::dot(l_v1, l_v2);
	EXPECT_NEAR(1, l_length2, bk::eps);
	EXPECT_NEAR(l_length1, l_dot, bk::eps);
}

TEST(vector, cross_fn_calcs_cross_vector_of_vector2)
{
	// given
	bk::real2 l_v1(1, 2);

	// when
	bk::real2 l_v2 = bk::cross(l_v1);

	// then
	EXPECT_EQ( 2, l_v2.x);
	EXPECT_EQ(-1, l_v2.y);
}
TEST(vector, cross_fn_calcs_cross_scalar_of_two_vector2)
{
	// given
	bk::real2 l_v1(1, 2), l_v2(2, 1);

	// when
	bk::real l_cross = bk::cross(l_v1, l_v2);

	// then
	EXPECT_EQ(-3, l_cross);
}
TEST(vector, cross_fn_calcs_cross_vector_of_two_vector3)
{
	// given
	bk::real3 l_v1(1, 0, 0), l_v2(0, 1, 0);

	// when
	bk::real3 l_v3 = bk::cross(l_v1, l_v2);

	// then
	EXPECT_EQ(0, l_v3.x);
	EXPECT_EQ(0, l_v3.y);
	EXPECT_EQ(1, l_v3.z);
}
TEST(vector, cross_fn_calcs_cross_scalar_of_three_vector3)
{
	// given
	bk::real3 l_v1(1, 0, 0), l_v2(0, 1, 0), l_v3(0, 0, 1);

	// when
	bk::real l_cross = bk::cross(l_v1, l_v2, l_v3);

	// then
	EXPECT_EQ(1, l_cross);
}

TEST(vector, mul_fn_multiplies_vector_and_matrix)
{
	// given
	bk::real3 l_v1(1, 0, 0); bk::real3x3 l_m( 0, 1, 0,
											  1, 0, 0,
											  0, 0, 1 );

	// when
	bk::real3 l_v2 = bk::mul(l_v1, l_m);

	// then
	EXPECT_EQ(0, l_v2.x);
	EXPECT_EQ(1, l_v2.y);
	EXPECT_EQ(0, l_v2.z);
}

}

}