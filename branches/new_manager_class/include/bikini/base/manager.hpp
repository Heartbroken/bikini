/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// manager
/**	[TODO]
 */
struct manager : noncopyable
{
	/// manager::object
	/**	[TODO]
	 */
	struct object
	{
		/// manager::object::info
		/**	[TODO]
		 */
		struct info : noncopyable
		{
			typedef object object;
			typedef manager manager;

			info(uint _type);
			virtual ~info();

			inline uint type() const;

		private:
			uint m_type;
		};

		/// manager::object::instance
		/**	[TODO]
		 */
		struct instance : noncopyable
		{
			instance(uint _ID, const info &_info)
			:
				m_ID(_ID), m_info(_info)
			{}

		private:
			uint m_ID;
			const info &m_info;
			pool_<uint> m_relations;
		};

		object(manager &_manager, uint _ID)
		:
			m_manager(_manager), m_ID(_ID)
		{}

		//inline const info& get_info() const;
		//template<typename _Info> const _Info& get_info_() const;
		//inline manager& get_manager() const;
		//inline uint type() const;
		//inline uint ID() const;
		//inline uint add_relation(uint _relation);
		//inline void remove_relation(uint _ID);
		//inline uint first_relation() const;
		//inline uint next_relation(uint _ID) const;
		//inline uint get_relation(uint _ID) const;
		//inline bool has_relation(uint _ID) const;
		//inline bool has_relations() const;
		//object(const info &_info, manager &_manager);
		//virtual ~object();
		//virtual bool update(real _dt);

	private:
		manager &m_manager;
		uint m_ID;
		//friend manager;
		//const info &m_info;
		//manager &m_manager;
		//uint m_ID;
		//pool_<uint> m_relations;
		//uint m_ref_count;
		//inline uint add_ref();
		//inline uint ref_count() const;
		//inline uint release();
	};

	manager();
	virtual ~manager();

	bool exists(uint _ID) const;
	object& get(uint _ID) const;
	template<typename _Type> inline _Type& get_(uint _ID) const;
	uint get_first_ID(uint _type = bad_ID) const;
	uint get_next_ID(uint _prev_ID, uint _type = bad_ID) const;

	template<typename _Info> inline _Info::object spawn(const _Info &_info);
	template<typename _Info> inline uint spawn(const _Info &_info, typename _Info::a0 _a0);
	template<typename _Info> inline uint spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1);
	template<typename _Info> inline uint spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2);
	template<typename _Info> inline uint spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3);
	template<typename _Info> inline uint spawn(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3, typename _Info::a4 _a4);
	void kill(uint _ID);

	//template<typename _Info> inline uint request(const _Info &_info);
	//template<typename _Info> inline uint request(const _Info &_info, typename _Info::a0 _a0);
	//template<typename _Info> inline uint request(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1);
	//template<typename _Info> inline uint request(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2);
	//template<typename _Info> inline uint request(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3);
	//template<typename _Info> inline uint request(const _Info &_info, typename _Info::a0 _a0, typename _Info::a1 _a1, typename _Info::a2 _a2, typename _Info::a3 _a3, typename _Info::a4 _a4);
	//uint release(uint _ID);

	virtual bool update(real _dt);
	virtual void clear();
	virtual void destroy();

private:
	//uint add(object &_object);
	//void remove(uint _ID);
	pool_<object::instance*> m_objects;
	//array_<uint> m_shared;
	//template<typename _Info> inline uint m_find_shared(const _Info &_info);
	array_<uint> m_update_order;
	void m_build_update_order();
	//uint m_counter;
};

#include "manager.inl"