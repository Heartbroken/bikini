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

		struct types { enum
		{
			sector, portal, camera, decor
		};};

		inline scene& get_scene() const { return get_manager_<scene>(); }

		object(const info &_info, scene &_scene);
	};

	scene();

	bool create();
	bool update(real _dt);
	bool render() const;
	void destroy();

	inline uint default_sector_ID() const { return m_default_sector_ID; }
	inline uint default_camera_ID() const { return m_default_camera_ID; }
	inline uint active_camera_ID() const { return m_active_camera_ID; }
	inline void set_active_camera_ID(uint _camera_ID) { m_active_camera_ID = _camera_ID; }

private:
	uint m_default_sector_ID;
	uint m_default_camera_ID, m_active_camera_ID;
};

DECLARE_UTEST(movie_scene);
