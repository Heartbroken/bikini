/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct watch
{
	// type_ID
	typedef pointer type_ID;


	// type
	struct type
	{
		struct member;
		struct base;

		// aide_ - helper class for registering members of the type
		template<typename _Type, bool _POD = traits_<_Type>::is_fundamental> struct aide_ { inline aide_(type &_t) {} }; // This prevents user from adding members to fundamental types
		template<typename _Type> struct aide_<_Type, false>
		{
			// constructor
			inline aide_(type &_t);
			template<typename _Base> inline const aide_& add_base_() const;
			//template<typename _Member> const aide_& add_member_(_Member _member, const achar *_name) const;
			template<typename _Member> const aide_& add_member(_Member _member, const achar *_name) const;

		private:
			type &m_type;
		};

		type_ID ID;
		astring name;

		// constructor
		inline type(const watch &_watch);
		// destructor
		inline ~type();

		// base types manipulation
		template<typename _Type> inline base& add_base_();
		inline uint base_count() const;
		inline const base& get_base(uint _i) const;

		// members manipulation
		template<typename _Type> member& add_member_(const achar *_name);
		uint member_count() const;
		const member& get_member(uint _i) const;
		handle member_base_cast(uint _i, handle _p) const;
		uint find_member(const achar *_name) const;

		// watch object accessor
		inline const watch& get_watch() const;

		// value destroying helpers
		template<typename _Type> inline void set_destroy_();
		inline void destroy_value(handle _p) const;

		// value printing helpers
		template<typename _Type> inline void set_print_();
		inline astring print_value(pointer _p) const;

	private:
		const watch &m_watch;
		array_<base*> m_bases;
		array_<member*> m_members;
		void (*m_destroy_fn)(handle);
		astring (*m_print_fn)(pointer);
	};

	// varaible
	struct varaible
	{
		array_<uint> path;

		// constructors
		inline varaible(const watch &_watch);
		inline varaible(const varaible &_v);

		// assignment
		inline varaible& operator = (const varaible &_v);

		// name
		inline const char* name() const;
		inline const char* type_name() const;

		// print
		inline astring print() const;

		// watch object accessor
		inline const watch& get_watch() const;

		inline bool valid() const;
		inline uint member_count() const;
		inline varaible get_member(uint _i) const;
		inline varaible operator [] (uint _i) const;
		inline varaible get_member(const achar *_name) const;
		inline varaible operator [] (const achar *_name) const;
		template<typename _Type> inline _Type get_() const;

	private:
		const watch &m_watch;
	};

	// constructor
	watch();
	// destructor
	~watch();

	// register a type
	template<typename _Type> type::aide_<_Type> add_type_(const achar *_name);
	// get type count
	uint type_count() const;
	// get type by index
	const type& get_type(uint _i) const;
	// register varaible
	template<typename _Type> varaible add_global(_Type _v, const achar *_name);
	// get global varaibles count
	uint global_count() const;
	// get global varaible by index
	varaible get_global(uint _i) const;
	// find varaible by name
	varaible find_varaible(const achar *_path) const;
	// remove all types and varaibles
	void clear();

private:
	array_<type*> m_types;
};

#include "watch.inl"