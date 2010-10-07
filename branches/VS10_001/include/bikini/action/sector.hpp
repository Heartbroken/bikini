/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct sector : scene::object
{
	struct info : scene::object::info
	{
		typedef sector object;
		info();
	};

	sector(const info &_info, scene &_scene);
};

DECLARE_UTEST(action_sector);
