/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2011 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk /*----------------------------------------------------------------------------------*/
{
namespace dyne /*--------------------------------------------------------------------------------*/
{

UTEST_FILE(dyne_simulator);

namespace utest /*-------------------------------------------------------------------------------*/
{

TEST(dyne_simulator, can_be_created)
{
	// given
	bk::dyne::simulator l_simulator;

	// when
	bool l_created = l_simulator.create();

	// then
	EXPECT_TRUE(l_created);

	// clear
	l_simulator.destroy();
}

} /* namespace utest ----------------------------------------------------------------------------*/
} /* namespace dyne -----------------------------------------------------------------------------*/
} /* namespace bk -------------------------------------------------------------------------------*/
