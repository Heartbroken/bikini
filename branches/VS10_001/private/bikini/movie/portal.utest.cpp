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

UTEST_FILE(movie_portal);

namespace utest /*-------------------------------------------------------------------------------*/
{

struct movie_portal : testing::Test /*-----------------------------------------------------------*/
{
	void SetUp()
	{
		m_scene.create(m_renderer);
		m_sector_ID = m_scene.spawn(m_sector_info);
	}
	void TearDown()
	{
		m_scene.destroy();
	}

protected:
	renderer m_renderer;
	scene m_scene;
	sector::info m_sector_info;
	uint m_sector_ID;

}; /*--------------------------------------------------------------------------------------------*/

TEST_F(movie_portal, can_be_spawned)
{
	// given
	bk::movie::portal::info l_portal_info;

	// when
	bk::uint l_portal_ID = m_scene.spawn(l_portal_info, m_sector_ID, r4x4_1);

	// then
	EXPECT_TRUE(m_scene.exists(l_portal_ID));
}

} /* namespace utest ----------------------------------------------------------------------------*/
} /* namespace movie ----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
