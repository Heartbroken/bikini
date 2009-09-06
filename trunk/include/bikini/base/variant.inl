/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _variant_helper_
template<typename _L, bool _D>
struct _variant_helper_ {
	static inline void construct(handle &_h, uint _t, pointer _v) { _h = _L::construct(_t, _v); }
	static inline void destruct(handle &_h, uint _t) { _L::destruct(_h, _t, true); }
};
template<typename _L>
struct _variant_helper_<_L, false> {
	static inline void construct(handle _h, uint _t, pointer _v) { _L::construct(_h, _t, _v); }
	static inline void destruct(handle _h, uint _t) { _L::destruct(_h, _t, false); }
};

template<typename _L, bool _D>
inline variant_<_L, _D>::variant_() : m_type(bad_ID) {
}
template<typename _L, bool _D>
inline variant_<_L, _D>::variant_(const variant_ &_v) : m_type(bad_ID) {
	construct(_v.type(), _v.data());
}
template<typename _L, bool _D> template<typename _T>
inline variant_<_L, _D>::variant_(const _T &_v) : m_type(bad_ID) {
	c_assert(_L::type_<_T>::exists);
	construct(_L::type_<_T>::index, &_v);
}
template<typename _L, bool _D> template<typename _L2, bool _D2>
inline variant_<_L, _D>::variant_(const variant_<_L2, _D2> &_v) : m_type(bad_ID) {
	construct(_L::otherlist<_L2>::remap(_v.type()), _v.data());
}
template<typename _L, bool _D>
inline variant_<_L, _D>::~variant_() {
	destruct();
}
template<typename _L, bool _D>
inline uint variant_<_L, _D>::type() const {
	return m_type;
}
template<typename _L, bool _D>
inline pointer variant_<_L, _D>::data() const {
	return m_data;
}
template<typename _L, bool _D>
inline void variant_<_L, _D>::construct(uint _type, pointer _data) {
	assert(_type < _L::count || _type == bad_ID);
	destruct();
	m_type = _type;
	if(_type != bad_ID) _variant_helper_<_L, _D>::construct(m_data, _type, _data);
}
template<typename _L, bool _D>
inline void variant_<_L, _D>::destruct() {
	if(m_type == bad_ID) return;
	_variant_helper_<_L, _D>::destruct(m_data, m_type);
	m_type = bad_ID;
}
template<typename _L, bool _D>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const variant_ &_v) {
	construct(_v.type(), _v.data());
	return *this;
}
template<typename _L, bool _D> template<typename _T>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const _T &_v) {
	c_assert(_L::type_<_T>::exists);
	construct(_L::type_<_T>::index, &_v);
	return *this;
}
template<typename _L, bool _D> template<typename _L2, bool _D2>
inline variant_<_L, _D>& variant_<_L, _D>::operator = (const variant_<_L2, _D2> &_v) {
	construct(_L::otherlist_<_L2>::remap(_v.type()), _v.data());
	return *this;
}
template<typename _L, bool _D>
inline bool variant_<_L, _D>::operator == (const variant_ &_v) const {
	return m_type != bad_ID && m_type == _v.type() && _L::compare(m_type, m_data, _v.data());
}
template<typename _L, bool _D> template<typename _T>
inline bool variant_<_L, _D>::operator == (const _T &_v) const {
	return m_type != bad_ID && m_type == typelist::type_<_T>::index && _L::compare(m_type, m_data, &_v);
}
template<typename _L, bool _D> template<typename _L2, bool _D2>
inline bool variant_<_L, _D>::operator == (const variant_<_L2, _D2> &_v) const {
	return m_type != bad_ID && m_type == _L::otherlist_<_L2>::remap(_v.type()) && _L::compare(m_type, m_data, _v.data());
}
template<typename _L, bool _D> template<typename _T>
inline bool variant_<_L, _D>::operator != (const _T &_v) const {
	return !(*this == _v);
}
template<typename _L, bool _D> template<typename _T>
inline static bool variant_<_L, _D>::can_take() {
	return _L::type_<_T>::exists;
}
template<typename _L, bool _D> template<typename _T>
inline static bool variant_<_L, _D>::can_take(const _T &_v) {
	return _L::type_<_T>::exists;
}
template<typename _L, bool _D> template<typename _L2, bool _D2>
inline static bool variant_<_L, _D>::can_take(const variant_<_L2, _D2> &_v) {
	return _L::otherlist_<_L2>::remap(_v.type()) != bad_ID;
}
template<typename _L, bool _D>
inline bool variant_<_L, _D>::is_nothing() const {
	return m_type == bad_ID;
}
template<typename _L, bool _D> template<typename _T>
inline bool variant_<_L, _D>::is_() const {
	return !is_nothing() && _L::type_<_T>::index == m_type;
}
template<typename _L, bool _D> template<typename _T>
inline const _T& variant_<_L, _D>::get_() const {
	return *reinterpret_cast<const _T*>(m_data);
}
template<typename _L, bool _D> template<typename _T>
inline const _T& variant_<_L, _D>::def(const _T &_def) const {
	return is_<_T>() ? get_<_T>() : _def;
}
