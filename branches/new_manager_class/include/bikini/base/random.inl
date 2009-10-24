/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// random
inline random::random(uint _seed) : seed(_seed)
{}
inline uint random::get() {
	seed = seed * 1103515245 + 12345;
	return uint(seed / 65536) & max;
}
inline uint random::get(uint _max) {
	return get() % (_max + 1);
}
inline sint random::get(sint _min, sint _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(uint(_max - _min));
}
inline real random::get(real _max) {
	return bk::max(real(0), real(get()) * _max / real(max));
}
inline real random::get(real _min, real _max) {
	if(_max < _min) swap(_min, _max);
	return _min + get(_max - _min);
}
