/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _watch_type_member_getter

struct _watch_type_member_getter
{
	bool valid, by_value; uint value_size;
	inline _watch_type_member_getter() : valid(true), by_value(false), value_size(0) {}
	virtual void operator( ) (handle _value, pointer _object) const = 0;
};

// getter templates

template<typename _Type> struct _getter_ : _watch_type_member_getter
{
	inline _getter_(_Type) { valid = false; }
	void operator () (handle _value, pointer _object) const {}
};
template<typename _T> struct _getter_<void (*)(_T)> : _watch_type_member_getter
{
	inline _getter_(void (*)(_T)) { valid = false; }
	void operator () (handle _value, pointer _object) const {}
};
template<typename _T, typename _O> struct _getter_<void (_O::*)(_T)> : _watch_type_member_getter
{
	inline _getter_(void (_O::*)(_T)) { valid = false; }
	void operator () (handle _value, pointer _object) const {}
};
template<typename _T, typename _O> struct _getter_<void (*)(_O, _T)> : _watch_type_member_getter
{
	inline _getter_(void (*)(_O, _T)) { valid = false; }
	void operator () (handle _value, pointer _object) const {}
};
template<typename _T> struct _getter_<_T*> : _watch_type_member_getter
{
	inline _getter_(_T *_p) : m_p(_p) { value_size = sizeof(_T*); }
	void operator () (handle _value, pointer _object) const { *(_T**)_value = m_p; }
private:
	_T *m_p;
};
template<typename _T, typename _O> struct _getter_<_T _O::*> : _watch_type_member_getter
{
	inline _getter_(_T _O:: *_p) : m_p(_p) { by_value = false; value_size = sizeof(_T*); }
	void operator () (handle _value, pointer _object) const { *(_T**)_value = &(((_O*)_object)->*m_p); }
private:
	_T _O::* m_p;
};
template<typename _T> struct _getter_<_T (*)()> : _watch_type_member_getter
{
	typedef _T (*fn)();
	template<typename _R> struct _helper_ {
		static const bool by_value = true; static const uint value_size = sizeof(_R);
		static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R(_fn()); }
	};
	template<typename _R> struct _helper_<_R&> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &_fn(); }
	};
	template<typename _R> struct _helper_<_R*> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = _fn(); }
	};
	inline _getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
	void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};
template<typename _T, typename _O> struct _getter_<_T (_O::*)() const> : _watch_type_member_getter
{
	typedef _T (_O::*fn)() const;
	template<typename _R> struct _helper_ {
		static const bool by_value = true; static const uint value_size = sizeof(_R);
		static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R((((_O*)_object)->*_fn)()); }
	};
	template<typename _R> struct _helper_<_R&> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &(((_O*)_object)->*_fn)(); }
	};
	template<typename _R> struct _helper_<_R*> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = (((_O*)_object)->*_fn)(); }
	};
	inline _getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
	void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};
// If your accessor doesn't match any of getter templates or matches wrong one,
// make a wrapper function like
//
// MemberType Get_MyClass_Member1(const MyClass &_o) { return _o.Get_Member1(); }
//
// and register it.
template<typename _T, typename _O> struct _getter_<_T (*)(const _O&)> : _watch_type_member_getter
{
	typedef _T (*fn)(const _O&);
	template<typename _R> struct _helper_ {
		static const bool by_value = true; static const uint value_size = sizeof(_R);
		static inline void call(handle _value, pointer _object, fn _fn) { new(_value) _R(_fn(*(_O*)_object)); }
	};
	template<typename _R> struct _helper_<_R&> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = &_fn(*(_O*)_object); }
	};
	template<typename _R> struct _helper_<_R*> {
		static const bool by_value = false; static const uint value_size = sizeof(_R*);
		static inline void call(handle _value, pointer _object, fn _fn) { *(_R**)_value = _fn(*(_O*)_object); }
	};
	inline _getter_(fn _fn) : m_fn(_fn) { by_value = _helper_<_T>::by_value; value_size = _helper_<_T>::value_size; }
	void operator () (handle _value, pointer _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};

// _watch_type_member_setter

struct _watch_type_member_setter
{
	bool valid;
	inline _watch_type_member_setter() : valid(true) {}
	virtual void operator () (pointer _value, handle _object) const = 0;
};

// setter templates

template<typename _Type> struct _setter_ : _watch_type_member_setter
{
	inline _setter_(_Type) { valid = false; }
	void operator () (pointer _value, handle _object) const {}
};
template<typename _T> struct _setter_<_T*> : _watch_type_member_setter
{
	inline _setter_(_T *_p) : m_p(_p) {}
	void operator () (pointer _value, handle _object) const { *m_p = *(_T*)_value; }
private:
	_T *m_p;
};
template<typename _T> struct _setter_<_T(*)()> : _watch_type_member_setter
{
	inline _setter_(_T(*)()){ valid = false; }
	void operator () (pointer _value, handle _object) const {}
};
template<typename _T, typename _O> struct _setter_<_T _O::*> : _watch_type_member_setter
{
	inline _setter_(_T _O:: *_p) : m_p(_p) {}
	void operator () (pointer _value, handle _object) const { ((_O*)_object)->*m_p = *(_T*)_value; }
private:
	_T _O::* m_p;
};
template<typename _R, typename _T> struct _setter_<_R (*)(_T)> : _watch_type_member_setter
{
	typedef _R (*fn)(_T);
	template<typename _V> struct _helper_ {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V&> {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V*> {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn((_V*)_value); }
	};
	inline _setter_(fn _fn) : m_fn(_fn) {}
	void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};
template<typename _R, typename _O, typename _T> struct _setter_<_R (_O::*)(_T)> : _watch_type_member_setter
{
	typedef _R (_O::*fn)(_T);
	template<typename _V> struct _helper_ {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)(*(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V&> {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)(*(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V*> {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)((_V*)_value); }
	};
	inline _setter_(fn _fn) : m_fn(_fn) {}
	void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};
template<typename _O, typename _T> struct _setter_<_T& (_O::*)()> : _watch_type_member_setter
{
	typedef _T& (_O::*fn)();
	template<typename _V> struct _helper_ {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = *(_V*)_value; }
	};
	template<typename _V> struct _helper_<_V&> {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = *(_V*)_value; }
	};
	template<typename _V> struct _helper_<_V*> {
		static inline void call(pointer _value, handle _object, fn _fn) { (((_O*)_object)->*_fn)() = (_V*)_value; }
	};
	inline _setter_(fn _fn) : m_fn(_fn) {}
	void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};
// If your accessor doesn't match any of setter templates or matches wrong one,
// make a wrapper function like
//
// void Set_MyClass_Member1(MyClass &_o, const MemberType &_v) { _o.Set_Member1(_v); }
//
// and register it
template<typename _O, typename _T> struct _setter_<void (*)(_O&, _T)> : _watch_type_member_setter
{
	typedef void (*fn)(_O&, _T);
	template<typename _V> struct _helper_ {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, *(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V&> {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, *(_V*)_value); }
	};
	template<typename _V> struct _helper_<_V*> {
		static inline void call(pointer _value, handle _object, fn _fn) { _fn(*(_O*)_object, (_V*)_value); }
	};
	inline _setter_(fn _fn) : m_fn(_fn) {}
	void operator () (pointer _value, handle _object) const { _helper_<_T>::call(_value, _object, m_fn); }
private:
	fn m_fn;
};

// watch::type::aide_
//template<typename _Type> struct watch::type::aide_<_Type, false>
//{
template<typename _T>
inline watch::type::aide_<_T, false>::aide_(type &_t) : m_type(_t)
{
}
template<typename _T> template<typename _B>
inline const watch::type::aide_<_T, false>& watch::type::aide_<_T, false>::add_base_() const
{
	type::base &l_base = m_type.add_base_<_B>();
	l_base.base_cast = type::base::cast_<_T, _B>;

	return *this;
}
//template<typename _T> template<typename _M>
//inline const watch::type::aide_<_T, false>& watch::type::aide_<_T, false>::add_member_(_M _member, const achar *_name) const
//{
//	return add_member(_member, _name);
//}
template<typename _T> template<typename _M>
inline const watch::type::aide_<_T, false>& watch::type::aide_<_T, false>::add_member(_M _member, const achar *_name) const
{
	type::member &l_member = m_type.add_member_<_M>(_name);

	_watch_type_member_getter *l_get = new _getter_<_M>(_member);
	if (l_get->valid) l_member.get = l_get;
	else delete l_get;

	_watch_type_member_setter *l_set = new _setter_<_M>(_member);
	if (l_set->valid) l_member.set = l_set;
	else delete l_set;

	return *this;
}

//private:
//	type &m_type;
//};

// watch::type

//struct watch::type
//{
	// member
struct watch::type::member
{
	uint type;
	astring name;
	_watch_type_member_getter *get;
	_watch_type_member_setter *set;

	member() : get(0), set(0)
	{
	}
	~member()
	{
		delete get;
		delete set;
	}
	template<typename _T> struct _const_helper_
	{
		static uint index(const watch &_watch) { return _get_index_of_<_T>(_watch); }
	};
	template<typename _T> struct _const_helper_<const _T>
	{
		static uint index(const watch &_watch) { return _get_index_of_<_T>(_watch); }
	};
	template<typename _T> struct _ref_helper_
	{
		static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
	};
	template<typename _T> struct _ref_helper_<_T*>
	{
		static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
	};
	template<typename _T> struct _ref_helper_<_T&>
	{
		static uint index(const watch &_watch) { return _const_helper_<_T>::index(_watch); }
	};
	template<typename _T> struct type_
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _T> struct type_<_T*>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _T, typename _S> struct type_<_T _S::*>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _T> struct type_<_T (*)()>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _T, typename _S> struct type_<_T (_S::*)() const>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _T, typename _S> struct type_<_T (_S::*)()>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _R, typename _T> struct type_<_R (*)(_T)>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _R, typename _S, typename _T> struct type_<_R (_S::*)(_T)>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _S, typename _T> struct type_<_T (*)(const _S&)>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
	template<typename _S, typename _T> struct type_<void (*)(_S&, _T)>
	{
		static uint index(const watch &_watch) { return _ref_helper_<_T>::index(_watch); }
	};
};
struct watch::type::base
{
	uint type;
	handle (*base_cast)(handle);
	template<typename _T, typename _B> static handle cast_(handle _p) { return static_cast<_B*>((_T*)_p); }
};

	//type_ID ID;
	//astring name;

inline watch::type::type(const watch &_watch) : m_watch(_watch), m_destroy_fn(0), m_print_fn(0)
{
}
inline watch::type::~type()
{
	while (!m_members.empty())
	{
		delete m_members.back();
		m_members.pop_back();
	}
	while (!m_bases.empty())
	{
		delete m_bases.back();
		m_bases.pop_back();
	}
}
template<typename _Type> inline watch::type::base& watch::type::add_base_()
{
	uint l_type = _get_index_of_<_Type>(m_watch);
	//uint l_type = member::type_<_Type>::index(m_watch);
	if (l_type == bad_ID)
	{
		std::cerr << "ERROR: (Watch) Base type of type " << name << " is not registered\n";
		assert(0);
	}
	m_bases.push_back(new base);
	m_bases.back()->type = l_type;

	return *m_bases.back();
}
inline uint watch::type::base_count() const
{
	return m_bases.size();
}
inline const watch::type::base& watch::type::get_base(uint _i) const
{
	return *m_bases[_i];
}
template<typename _Type> watch::type::member& watch::type::add_member_(const achar *_name)
{
	uint l_type = member::type_<_Type>::index(m_watch);

	if (l_type == bad_ID)
	{
		std::cerr << "ERROR: (Watch) Member '" << _name << "' type is not registered\n";
	}

	for (uint i = 0, s = m_members.size(); i < s; ++i)
	{
		member &l_member = *m_members[i];
		if (l_member.name == _name)
		{
			if (l_member.type != l_type)
			{
				std::cerr << "ERROR: (Watch) Member '" << _name << "' already defined with different type\n";
				assert(0);
			}

			return l_member;
		}
	}
	m_members.push_back(new member);

	member &l_member = *m_members.back();
	l_member.type = l_type;
	l_member.name = _name;

	return l_member;
}
//inline uint own_member_count() const
//{
//	return m_members.size();
//}
inline const watch& watch::type::get_watch() const
{
	return m_watch;
}
template<typename _Type> inline void _watch_type_destroy_(handle _p)
{
	((_Type*)_p)->~_Type();
}
template<typename _Type> inline void watch::type::set_destroy_()
{
	m_destroy_fn = _watch_type_destroy_<_Type>;
}
inline void watch::type::destroy_value(handle _p) const
{
	if (m_destroy_fn != 0) m_destroy_fn(_p);
}
template<typename _Type> inline astring _watch_type_print_(pointer _p)
{
	return astring();
}
template<> inline astring _watch_type_print_<int>(pointer _p)
{
	const uint buffer_max = 64; char buffer[buffer_max];
	if (sprintf_s(buffer, buffer_max, "%d", *(int*)_p) != -1) return buffer;
	return astring();
}
template<typename _Type> inline void watch::type::set_print_()
{
	m_print_fn = _watch_type_print_<_Type>;
}
inline astring watch::type::print_value(pointer _p) const
{
	if (m_print_fn != 0) return m_print_fn(_p);
	return astring();
}

//private:
//	watch &m_watch;
//	array_<base*> m_bases;
//	array_<member*> m_members;
//	void (*m_destroy_fn)(handle);
//	template<typename _Type> static inline void destroy_(handle _p) { ((_Type*)_p)->~_Type(); }
//};

// watch::varaible

const watch::type::member& _varaible_resolve_member(const watch::varaible &_v);
void _varaible_resolve_get(const watch::varaible &_v, handle _value);
void _varaible_resolve_set(const watch::varaible &_v, handle _value);

inline watch::varaible::varaible(const watch &_watch) : m_watch(_watch)
{
}
inline watch::varaible::varaible(const varaible &_v) : m_watch(_v.get_watch()), path(_v.path)
{
}
inline watch::varaible& watch::varaible::operator = (const watch::varaible &_v)
{
	this->~varaible(); new(this) varaible(_v); return *this;
}
inline const char* watch::varaible::name() const
{
	assert(valid());

	const type::member &l_member = _varaible_resolve_member(*this);

	return l_member.name.c_str();
}
inline const char* watch::varaible::type_name() const
{
	assert(valid());

	const type::member &l_member = _varaible_resolve_member(*this);
	const type &l_type = m_watch.get_type(l_member.type);

	return l_type.name.c_str();
}
inline astring watch::varaible::print() const
{
	assert(valid());

	astring l_result;

	if (member_count() > 0)
	{
		l_result += "{ ";
		for (uint i = 0, s = member_count(); i < s; ++i)
		{
			varaible l_member = get_member(i);
			l_result += l_member.name(); l_result +=  " = "; l_result += l_member.print();
			if (i + 1 < s) l_result +=  " ";
		}
		l_result += " }";
	}
	else
	{
		const type::member &l_member = _varaible_resolve_member(*this);
		const type &l_type = m_watch.get_type(l_member.type);

		handle l_value;
		if (l_member.get->by_value)
		{
			l_value = _malloca(l_member.get->value_size);
			_varaible_resolve_get(*this, l_value);
			l_result = l_type.print_value(l_value);
			l_type.destroy_value(l_value);
		}
		else
		{
			_varaible_resolve_get(*this, &l_value);
			l_result = l_type.print_value(l_value);
		}
	}

	return l_result;
}
inline const watch& watch::varaible::get_watch() const
{
	return m_watch;
}
inline bool watch::varaible::valid() const
{
	return !path.empty();
}
inline uint watch::varaible::member_count() const
{
	assert(valid());

	const type::member &l_member = _varaible_resolve_member(*this);
	const type &l_type = m_watch.get_type(l_member.type);

	return l_type.member_count();
}
inline watch::varaible watch::varaible::get_member(uint _i) const
{
	assert(valid() && _i < member_count());

	varaible l_v = *this;
	l_v.path.push_back(_i);

	return l_v;
}
inline watch::varaible watch::varaible::operator [] (uint _i) const
{
	return get_member(_i);
}
inline watch::varaible watch::varaible::get_member(const achar *_name) const
{
	assert(valid());

	const type::member &l_member = _varaible_resolve_member(*this);
	const type &l_type = m_watch.get_type(l_member.type);
	uint l_i = l_type.find_member(_name);

	if (l_i == bad_ID) return varaible(m_watch);

	varaible l_v = *this;
	l_v.path.push_back(l_i);

	return l_v;
}
inline watch::varaible watch::varaible::operator [] (const achar *_name) const
{
	return get_member(_name);
}
template<typename _T> struct _varaible_get_helper_
{
	static inline _T get(const watch::varaible &l_v, bool _byval)
	{
		if (_byval)
		{
			u8 l_value[sizeof(_T)]; _varaible_resolve_get(l_v, l_value);
			_T l_result(*(_T*)l_value); ((_T*)l_value)->~_T();
			return l_result;
		}
		_T* l_value; _varaible_resolve_get(l_v, &l_value); return *l_value;
	}
};
template<typename _T> struct _varaible_get_helper_<_T*>
{
	static inline _T* get(const watch::varaible &l_v, bool _byval)
	{
		if (_byval)
		{
			std::cerr << "ERROR: (Watch) An attempt to get pointer to temporary value\n"; assert(0); return (_T*)0;
		}
		_T* l_value; _varaible_resolve_get(l_v, &l_value); return l_value;
	}
};
template<typename _T> struct _varaible_get_helper_<_T&>
{
	static inline _T& get(const watch::varaible &l_v, bool _byval)
	{
		if (_byval)
		{
			std::cerr << "ERROR: (Watch) An attempt to get reference to temporary value\n"; assert(0); return *(_T*)0;
		}
		_T* l_value; _varaible_resolve_get(l_v, &l_value); return *l_value;
	}
};
template<typename _Type> inline _Type watch::varaible::get_() const
{
	assert(!path.empty());

	const type::member &l_member = _varaible_resolve_member(*this);
	const type &l_type = m_watch.get_type(l_member.type);

	if (l_type.ID == _get_ID_of_<_Type>() || l_type.ID == _get_ID_of_<traits_<_Type>::pointed>() || l_type.ID == _get_ID_of_<traits_<_Type>::referred>())
	{
		return _varaible_get_helper_<_Type>::get(*this, l_member.get->by_value);
	}

	std::cerr << "ERROR: (Watch) An attempt get value of wrong type\n";

	return *(traits_<_Type>::referred*)0;
}

// watch

template<typename _Type> watch::type::aide_<_Type> watch::add_type_(const achar *_name)
{
	assert(!m_types.empty());

	for (uint i = 0, s = m_types.size(); i < s; ++i)
	{
		type &l_type = *m_types[i];
		if (l_type.ID == _get_ID_of_<_Type>())
		{
			if (l_type.name != _name)
			{
				std::cerr << "WARNING: (Watch) Type '" << _name << "' redefines type '" << l_type.name << "'\n";
				l_type.name = _name;
			}
			return type::aide_<_Type>(l_type);
		}
	}

	m_types.push_back(new type(*this));

	type &l_type = *m_types.back();
	l_type.name = _name;
	l_type.ID = _get_ID_of_<_Type>();
	l_type.set_destroy_<_Type>();
	l_type.set_print_<_Type>();

	return type::aide_<_Type>(l_type);
}
template<typename _Type> watch::varaible watch::add_global(_Type _v, const achar *_name)
{
	assert(!m_types.empty());

	type &l_root = *m_types[0];

	assert(l_root.base_count() == 0);

	type::aide_<_Type>(l_root).add_member(_v, _name);

	varaible l_v(*this);
	l_v.path.push_back(l_root.member_count() - 1);

	return l_v;
}
template<typename _Type> watch::type_ID _get_ID_of_()
{
	static uint sl_ID = bad_ID;
	return &sl_ID;
}
template<typename _Type> uint _get_index_of_(const watch &_watch)
{
	for (uint i = 0, s = _watch.type_count(); i < s; ++i)
	{
		const watch::type &l_type = _watch.get_type(i);
		if (l_type.ID == _get_ID_of_<_Type>()) return i;
	}

	return bad_ID;
}
