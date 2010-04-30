#include "stdafx.h"

// base/math
TEST(base_math, matrix_assign) {
	bk::real3 l_v(1, 2, 3);
	EXPECT_EQ(1, l_v.x());
	EXPECT_EQ(2, l_v.y());
	EXPECT_EQ(3, l_v.z());
}
TEST(base_math, matrix_add) {
	bk::real3 l_v1(1, 2, 3), l_v2(1, 2, 3);
	bk::real3 l_v3 = l_v1 + l_v2;
	EXPECT_EQ(2, l_v3.x());
	EXPECT_EQ(4, l_v3.y());
	EXPECT_EQ(6, l_v3.z());
}

// base/random
TEST(base_random, set_seed) {
	bk::random l_random(12345);
	bk::uint l_test_count = 20;
	bk::uint_array l_res0, l_res1;
	for(bk::uint i = 0; i < l_test_count; ++i) {
		l_res0.push_back(l_random.get());
	}
	l_random.seed = 12345;
	for(bk::uint i = 0; i < l_test_count; ++i) {
		l_res1.push_back(l_random.get());
	}
	for(bk::uint i = 0; i < l_test_count; ++i) {
		EXPECT_EQ(l_res0[i], l_res1[i]);
	}
}
TEST(base_random, get_range) {
	bk::random l_random(2);
	bk::uint l_test_count = 20;
	//
	{
		//bk::uint l_max = 0;
		//bk::uint l_test_count = 2000000;
		//for(bk::uint i = 0; i < l_test_count; ++i) {
		//	bk::uint l_v = l_random.get();
		//	l_max = bk::max(l_max, l_v);
		//}
		//EXPECT_EQ(bk::random::max, l_max);
	}
	//
	{
		const bk::uint l_max0 = 10;
		bk::uint l_min1 = 10, l_max1 = 0;
		for(bk::uint i = 0; i < l_test_count; ++i) {
			bk::uint l_v = l_random.get(l_max0);
			l_min1 = bk::min(l_min1, l_v);
			l_max1 = bk::max(l_max1, l_v);
		}
		EXPECT_EQ(0U, l_min1);
		EXPECT_EQ(l_max0, l_max1);
	}
	//
	{
		const bk::sint l_min0 = -5, l_max0 = 5;
		bk::sint l_min1 = 5, l_max1 = -5;
		for(bk::uint i = 0; i < l_test_count; ++i) {
			bk::sint l_v = l_random.get(l_min0, l_max0);
			l_min1 = bk::min(l_min1, l_v);
			l_max1 = bk::max(l_max1, l_v);
		}
		EXPECT_EQ(l_min0, l_min1);
		EXPECT_EQ(l_max0, l_max1);
	}
	//
	{
		bk::real l_rmin = -100, l_rmax = 100;
		bk::real l_r0 = l_random.get(l_rmax);
		EXPECT_LE(l_r0, l_rmax);
	}
	//
	{
		bk::real l_rmin = -100, l_rmax = 100;
		bk::real l_r1 = l_random.get(l_rmin, l_rmax);
		EXPECT_GE(l_r1, l_rmin);
		EXPECT_LE(l_r1, l_rmax);
	}
}
