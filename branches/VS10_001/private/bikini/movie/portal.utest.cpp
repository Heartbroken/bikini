/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk
{
namespace movie
{

UTEST_FILE(movie_portal);

namespace utest
{

TEST(movie_portal, can_be_spawned)
{
	// given
	bk::movie::scene l_scene;
	bk::movie::portal::info l_portal_info;

	// when
	bk::uint l_portal_ID = l_scene.spawn(l_portal_info, bad_ID, r4x4_1);

	// then
	EXPECT_TRUE(l_scene.exists(l_portal_ID));
}

}

}

}