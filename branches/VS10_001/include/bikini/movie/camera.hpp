/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct camera : sector::content
{
	struct info : sector::content::info
	{
		typedef camera object;
		info();
	};

	camera(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform);

	bool render() const;
};

DECLARE_UTEST(movie_camera);
