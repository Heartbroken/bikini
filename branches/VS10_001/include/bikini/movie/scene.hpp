/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct scene : manager
{
	struct object : manager::object
	{
		struct info : manager::object::info
		{
			typedef scene manager;
			info(uint _type);
		};

		struct type { enum
		{
			sector, portal, camera
		};};

		object(const info &_info, scene &_scene);
	};

	bool render() const;
};

DECLARE_UTEST(movie_scene);