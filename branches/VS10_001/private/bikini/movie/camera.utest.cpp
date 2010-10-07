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

UTEST_FILE(movie_camera);

namespace utest
{

TEST(movie_camera, can_be_spawned)
{
	// given
	bk::movie::scene l_scene;
	bk::movie::camera::info l_camera_info;

	// when
	bk::uint l_camera_ID = l_scene.spawn(l_camera_info, bad_ID, r4x4_1);

	// then
	EXPECT_TRUE(l_scene.exists(l_camera_ID));
}

}

}

}