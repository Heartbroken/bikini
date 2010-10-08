/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk /*----------------------------------------------------------------------------------*/
{
namespace movie /*-------------------------------------------------------------------------------*/
{

UTEST_FILE(movie_sector);

namespace utest /*-------------------------------------------------------------------------------*/
{

TEST(movie_sector, can_be_spawned)
{
	// given
	bk::movie::scene l_scene;
	bk::movie::sector::info l_sector_info;

	// when
	bk::uint l_sector_ID = l_scene.spawn(l_sector_info);

	// then
	EXPECT_TRUE(l_scene.exists(l_sector_ID));
}

} /* namespace utest ----------------------------------------------------------------------------*/
} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
