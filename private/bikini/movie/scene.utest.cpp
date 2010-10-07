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

UTEST_FILE(movie_scene);

namespace utest
{

TEST(movie_scene, spawn_fn_creates_objects)
{
	// given
	bk::movie::scene l_scene;
	bk::movie::sector::info l_sector_info;
	bk::movie::portal::info l_portal_info;
	bk::movie::camera::info l_camera_info;

	// when
	bk::uint l_sector_ID = l_scene.spawn(l_sector_info);
	bk::uint l_portal_ID = l_scene.spawn(l_portal_info, l_sector_ID, r4x4_1);
	bk::uint l_camera_ID = l_scene.spawn(l_camera_info, l_sector_ID, r4x4_1);

	// then
	EXPECT_TRUE(l_scene.exists(l_sector_ID));
	EXPECT_TRUE(l_scene.exists(l_portal_ID));
	EXPECT_TRUE(l_scene.exists(l_camera_ID));
}

}

}

}