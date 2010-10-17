/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct portal : sector::object
{
	struct info : sector::object::info
	{
		typedef portal object;
		info();
	};

	portal(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform);

	inline uint target_ID() const { return m_target_ID; }
	inline void set_target_ID(uint _portal_ID) { m_target_ID = _portal_ID; }

private:
	uint m_target_ID;
};

DECLARE_UTEST(movie_portal);
