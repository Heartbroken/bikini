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

private:
	friend scene;
	friend sector;
	bool render(const context &_c) const;
	bool render(const context &_c, const decor &_decor) const;
	bool render(const context &_c, const actor &_actor) const;
	bool render(const context &_c, const portal &_portal) const;
};

DECLARE_UTEST(movie_camera);
