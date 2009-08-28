/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct device : manager {
	struct object : manager::object {
		struct info : manager::object::info {
			info(uint _type);
		};
		inline device& get_device() const { return static_cast<device&>(get_manager()); }
		inline bool valid() const { return m_version < infinity; }
		inline real version() const { return m_version; }
		object(const info &_info, device &_device);
		~object();
		//virtual bool create();
		//virtual void destroy();
	protected:
		typedef thread::locker lock;
		inline thread::section& section() { return m_section; }
		inline void set_invalid() { m_version = infinity; }
		inline void update_version() { m_version = (real)sys_time(); }
	private:
		thread::section m_section;
		real m_version;
	};
	bool update(real _dt);
};