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

	struct content : scene::object
	{
		struct info : scene::object::info
		{
			typedef uint a0;
			typedef const r4x4& a1;
			info(uint _type);
		};

		inline uint sector_ID() const { return m_sector_ID; }
		inline const r4x4& xform() const { return m_xform; }

		content(const info &_info, scene &_scene, uint _sector_ID, const r4x4 &_xform);
		virtual ~content();

		sector& get_sector() const;

	private:
		uint m_sector_ID;
		r4x4 m_xform;
	};

	inline uint object_count() const { return m_content.size(); }
	inline uint get_object_ID(uint _index) const { return m_content[_index]; }

	sector(const info &_info, scene &_scene);
	virtual ~sector();

	bool render(const context &_c) const;

private:
	uint_array m_content;
	void add_content(const content &_content);
	void remove_content(const content &_content);
	void kill_all_content();
};

DECLARE_UTEST(movie_sector);
