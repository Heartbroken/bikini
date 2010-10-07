/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk
{
namespace action
{

UTEST_FILE(action_sector);

namespace utest
{

TEST(action_sector, can_be_spawned)
{
	// given
	bk::action::scene l_scene;
	bk::action::sector::info l_sector_info;

	// when
	bk::uint l_sector_ID = l_scene.spawn(l_sector_info);

	// then
	EXPECT_TRUE(l_scene.exists(l_sector_ID));
}

}

}

}