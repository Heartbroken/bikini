/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct actor : sector::content
{
	struct info : sector::content::info
	{
		typedef actor object;
		info();
	};

	actor(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform);
};

DECLARE_UTEST(movie_actor);
