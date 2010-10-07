/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk /*----------------------------------------------------------------------------------*/
{
namespace action /*------------------------------------------------------------------------------*/
{

// portal

portal::portal(const info &_info, scene &_scene)
:
	scene::object(_info, _scene)
{}

// portal::info

portal::info::info()
:
	scene::object::info(type::portal)
{}

} /* namespace action ---------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
