#include "stdafx.h"

// base/pool
TEST(base_pool, should_report_value_exists) {
	// given
	bk::uint l_test_value = 12345;
	bk::pool_<bk::uint> l_pool1, l_pool2;
	bk::uint l_ID = l_pool1.add(l_test_value);

	// when
	bool l_exists1 = l_pool1.exists(l_ID);
	bool l_exists2 = l_pool2.exists(l_ID);

	// then
	EXPECT_TRUE(l_exists1);
	EXPECT_FALSE(l_exists2);
}
TEST(base_pool, should_return_value_by_ID) {
	// given
	bk::uint l_test_value = 12345;
	bk::pool_<bk::uint> l_pool;
	bk::uint l_ID = l_pool.add(l_test_value);

	// when
	bk::uint l_value = l_pool.get(l_ID);

	// then
	EXPECT_EQ(l_value, l_test_value);
}
TEST(base_pool, should_return_pool_size) {
	// given
	bk::pool_<bk::uint> l_pool;
	bk::uint_array l_IDs;
	l_IDs.push_back(l_pool.add(1));
	l_IDs.push_back(l_pool.add(2));
	l_IDs.push_back(l_pool.add(3));
	l_pool.remove(l_IDs[0]);

	// when
	bk::uint l_size = l_pool.size();

	// then
	EXPECT_EQ(l_size, 2);
}
TEST(base_pool, should_report_pool_is_empty) {
	// given
	bk::pool_<bk::uint> l_pool1, l_pool2;
	bk::uint l_ID = l_pool1.add(12345);

	// when
	bool l_empty1 = l_pool1.empty();
	bool l_empty2 = l_pool2.empty();

	// then
	EXPECT_FALSE(l_empty1);
	EXPECT_TRUE(l_empty2);
}

