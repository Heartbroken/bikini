/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// watch::type

uint watch::type::member_count() const
{
	uint l_count = m_members.size();

	for (uint i = 0, s = base_count(); i < s; ++i)
	{
		const base &l_base = get_base(i);
		const type &l_type = m_watch.get_type(l_base.type);
		l_count += l_type.member_count();
	}

	return l_count;
}
const watch::type::member& watch::type::get_member(uint _i) const
{
	if (_i < m_members.size())
	{
		return *m_members[_i];
	}

	uint l_i = _i - m_members.size();

	for (uint i = 0, s = base_count(); i < s; ++i)
	{
		const base &l_base = get_base(i);
		const type &l_type = m_watch.get_type(l_base.type);

		uint l_count = l_type.member_count();

		if (l_i < l_count) return l_type.get_member(l_i);

		l_i -= l_count;
	}

	std::cerr << "ERROR: (Watch) Bad member index\n";
	assert(0);

	return *(member*)0;
}
handle watch::type::member_base_cast(uint _i, handle _p) const
{
	if (_i < m_members.size())
	{
		return _p;
	}

	uint l_i = _i - m_members.size();

	for (uint i = 0, s = base_count(); i < s; ++i)
	{
		const base &l_base = get_base(i);
		const type &l_type = m_watch.get_type(l_base.type);

		uint l_count = l_type.member_count();

		if (l_i < l_count) return l_type.member_base_cast(l_i, l_base.base_cast(_p));

		l_i -= l_count;
	}

	std::cerr << "ERROR: (Watch) Bad member index\n";
	assert(0);

	return _p;
}
uint watch::type::find_member(const achar *_name) const
{
	for (uint i = 0, s = member_count(); i < s; ++i)
	{
		const member &l_member = get_member(i);
		if (l_member.name == _name) return i;
	}

	return bad_ID;
}

// watch::varaible

const watch::type::member& _varaible_resolve_member(const watch::varaible &_v)
{
	uint l_type = 0;
	for (uint i = 0, s = _v.path.size(); i < s; ++i)
	{
		const watch::type::member &l_member = _v.get_watch().get_type(l_type).get_member(_v.path[i]);
		l_type = l_member.type;

		if (i + 1 == s) return l_member;
	}

	assert(0);

	return *(watch::type::member*)0;
}
struct _varaible_tmp_object { uint type; handle object; };
void _varaible_resolve_get(const watch::varaible &_v, handle _value)
{
	array_<_varaible_tmp_object> l_tmp_objects;
	uint l_type = 0;
	handle l_object = 0;
	for (uint i = 0, s = _v.path.size(); i < s; ++i)
	{
		uint l_step = _v.path[i];
		const watch::type &l_object_type = _v.get_watch().get_type(l_type);
		const watch::type::member &l_member = l_object_type.get_member(l_step);

		handle l_value = i + 1 < s ? _malloca(l_member.get->value_size) : _value;
		(*l_member.get)(l_value, l_object_type.member_base_cast(l_step, l_object));

		if (i + 1 == s) break;

		if (l_member.get->by_value)
		{
			_varaible_tmp_object l_tmp; l_tmp.type = l_member.type; l_tmp.object = l_value;
			l_tmp_objects.push_back(l_tmp);
			l_object = l_value;
		}
		else
		{
			l_object = *(void**)l_value;
		}

		l_type = l_member.type;
	}

	while (!l_tmp_objects.empty())
	{
		const _varaible_tmp_object &l_tmp = l_tmp_objects.back();
		_v.get_watch().get_type(l_tmp.type).destroy_value(l_tmp.object);

		l_tmp_objects.pop_back();
	}
}
void _varaible_resolve_set(const watch::varaible &_v, pointer _value)
{
	array_<_varaible_tmp_object> l_tmp_objects;
	uint l_type = 0;
	handle l_object = 0;
	for (uint i = 0, s = _v.path.size(); i < s; ++i)
	{
		uint l_step = _v.path[i];
		const watch::type &l_object_type = _v.get_watch().get_type(l_type);
		const watch::type::member &l_member = l_object_type.get_member(l_step);

		handle l_value = 0;

		if (i + 1 < s)
		{
			l_value = _malloca(l_member.get->value_size);
			(*l_member.get)(l_value, l_object_type.member_base_cast(l_step, l_object));
		}
		else
		{
			(*l_member.set)(_value, l_object_type.member_base_cast(l_step, l_object));
		}

		if (i + 1 == s) break;

		if (l_member.get->by_value)
		{
			_varaible_tmp_object l_tmp; l_tmp.type = l_member.type; l_tmp.object = l_value;
			l_tmp_objects.push_back(l_tmp);
			l_object = l_value;
		}
		else
		{
			l_object = *(void**)l_value;
		}

		l_type = l_member.type;
	}

	while (!l_tmp_objects.empty())
	{
		const _varaible_tmp_object &l_tmp = l_tmp_objects.back();
		_v.get_watch().get_type(l_tmp.type).destroy_value(l_tmp.object);

		l_tmp_objects.pop_back();
	}
}

// watch

watch::watch()
{
	clear();
}
watch::~watch()
{
	while (!m_types.empty())
	{
		delete m_types.back();
		m_types.pop_back();
	}
}
uint watch::type_count() const
{
	return m_types.size();
}
const watch::type& watch::get_type(uint _i) const
{
	return *m_types[_i];
}
uint watch::global_count() const
{
	assert(!m_types.empty());

	const type &l_root = get_type(0);

	return l_root.member_count();
}
watch::varaible watch::get_global(uint _i) const
{
	assert(_i < global_count());

	varaible l_v(*this);
	l_v.path.push_back(_i);

	return l_v;
}
watch::varaible watch::find_varaible(const achar *_path) const
{
	assert(!m_types.empty());

	astring l_path = _path;
	astring l_name = l_path.substr(0, l_path.find("::"));
	l_path.erase(0, l_name.length() + 2);
	type &l_root = *m_types[0];
	uint l_i = l_root.find_member(l_name.c_str());

	if (l_i == bad_ID) return varaible(*this);

	varaible l_v(*this);
	l_v.path.push_back(l_i);

	while (l_path != "")
	{
		l_name = l_path.substr(0, l_path.find("::"));
		l_path.erase(0, l_name.length() + 2);

		l_v = l_v[l_name.c_str()];
	}

	return l_v;
}
void watch::clear()
{
	while (!m_types.empty())
	{
		delete m_types.back();
		m_types.pop_back();
	}

	m_types.push_back(new type(*this));

	type &l_type = *m_types.back();
	l_type.name = "root";
	l_type.ID = _get_ID_of_<watch>();
}


} /* namespace bk -------------------------------------------------------------------------------*/
