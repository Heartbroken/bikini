/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

TEST(math_matrix, should_assign_elements_values)
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

namespace bk { /*--------------------------------------------------------------------------------*/

void run_unit_tests()
{
	int argc = 1; char* argv = "";
	testing::InitGoogleTest(&argc, &argv);

	RUN_ALL_TESTS();
}

} /* namespace bk -------------------------------------------------------------------------------*/
