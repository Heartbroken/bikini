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

UTEST_FILE(action_portal);

namespace utest
{

TEST(action_portal, can_be_spawned)
{
	// given
	bk::action::scene l_scene;
	bk::action::portal::info l_portal_info;

	// when
	bk::uint l_portal_ID = l_scene.spawn(l_portal_info);

	// then
	EXPECT_TRUE(l_scene.exists(l_portal_ID));
}

}

}

}