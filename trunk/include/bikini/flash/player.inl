/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _player_renderer_helper_

template<typename _Renderer> struct _player_renderer_proxy_ : player::renderer
{
	_player_renderer_proxy_(_Renderer &_renderer) : m_renderer(_renderer) {}

private:
	_Renderer &m_renderer;
};

// _player_loader_helper_

template<typename _Loader> struct _player_loader_proxy_ : player::loader
{
	_player_loader_proxy_(_Loader &_loader) : m_loader(_loader) {}
	uint open(const wchar* _path) { return m_loader.open(_path); }
	bool good(uint _ID) const { return m_loader.good(_ID); }
	uint seek(uint _ID, sint _offset = 0, uint _from = 0) { return m_loader.seek(_ID, _offset, _from); }
	uint read(uint _ID, handle _buffer, uint _length) { return m_loader.read(_ID, _buffer, _length); }
	void close(uint _ID) { m_loader.close(_ID); }

private:
	_Loader &m_loader;
};

// player

//inline player::renderer& player::get_renderer() const
//{
//	return *m_renderer_p;
//}
//inline player::loader& player::get_loader() const
//{
//	return *m_loader_p;
//}
template<typename _R>
inline bool player::create(_R &_renderer)
{
	return m_create(* new _player_renderer_proxy_<_R>(_renderer),
					* new _player_loader_proxy_<bk::loader>(m_def_loader));
}
template<typename _R, typename _L>
inline bool player::create(_R &_renderer, _L &_loader)
{
	return m_create(* new _player_renderer_proxy_<_R>(_renderer),
					* new _player_loader_proxy_<_L>(_loader));
}

// player::object

inline player& player::object::get_player() const
{
	return static_cast<player&>(get_manager());
}
