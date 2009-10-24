/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _F, typename _S, typename _T>
inline uint typelist_<_F, typelist_<_S, _T> >::size(uint _i) {
	assert(_i < count);
	if(_i) return rest::size(_i - 1);
	return sizeof(first);
}
template<typename _F, typename _S, typename _T>
inline handle typelist_<_F, typelist_<_S, _T> >::construct(uint _i) {
	assert(_i < count);
	if(_i) return rest::construct(_i - 1);
	return construct(malloc(sizeof(first)), _i);
}
template<typename _F, typename _S, typename _T>
inline handle typelist_<_F, typelist_<_S, _T> >::construct(uint _i, pointer _v) {
	assert(_i < count);
	if(_i) return rest::construct(_i - 1, _v);
	return construct(malloc(sizeof(first)), _i, _v);
}
template<typename _F, typename _S, typename _T>
inline handle typelist_<_F, typelist_<_S, _T> >::construct(handle _h, uint _i) {
	assert(_i < count);
	if(_i) return rest::construct(_h, _i - 1);
	return new(_h) first;
}
template<typename _F, typename _S, typename _T>
inline handle typelist_<_F, typelist_<_S, _T> >::construct(handle _h, uint _i, pointer _v) {
	assert(_i < count);
	if(_i) return rest::construct(_h, _i - 1, _v);
	return new(_h) first(*reinterpret_cast<const first*>(_v));
}
template<typename _F, typename _S, typename _T>
inline void typelist_<_F, typelist_<_S, _T> >::destruct(handle _h, uint _i, bool _and_free = true) {
	assert(_i < count);
	if(_i) return rest::destruct(_h, _i - 1, _and_free);
	reinterpret_cast<first*>(_h)->~first();
	if(_and_free) free(_h);
}
template<typename _F, typename _S, typename _T>
inline bool typelist_<_F, typelist_<_S, _T> >::compare(uint _i, pointer _a, pointer _b) {
	assert(_i < count);
	if(_i) return rest::compare(_i - 1, _a, _b);
	return *reinterpret_cast<const first*>(_a) == *reinterpret_cast<const first*>(_b);
}

template<typename _F, typename _S, typename _T> template<typename _O>
inline static uint typelist_<_F, typelist_<_S, _T> >::otherlist_<_O>::remap(uint _i) {
	return _i ? otherlist_<typename _O::rest>::remap(_i - 1) : type_<typename _O::first>::index;
}
