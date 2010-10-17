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

	struct object : scene::object
	{
		struct info : scene::object::info
		{
			typedef uint a0;
			typedef const r4x4& a1;
			info(uint _type);
		};

		inline uint sector_ID() const { return m_sector_ID; }
		inline const r4x4& xform() const { return m_xform; }

		object(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform);
		virtual ~object();

		sector& get_sector() const;

	private:
		uint m_sector_ID;
		r4x4 m_xform;
	};

	sector(const info &_info, scene &_scene);
	virtual ~sector();

	inline uint object_count() const { return m_objects.size(); }
	inline uint object_ID(uint _index) const { return m_objects[_index]; }

private:
	uint_array m_objects;
	void add_object(const object &_object);
	void remove_object(const object &_object);
};

DECLARE_UTEST(movie_sector);
