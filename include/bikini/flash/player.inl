/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// player::_renderer_interface

struct player::_renderer_interface
{
	virtual ~_renderer_interface() {}
};

// _player_renderer_helper_

template<typename _Renderer, typename _Interface> struct _player_renderer_proxy_ : _Interface
{
	inline _player_renderer_proxy_(_Renderer &_renderer)
	:
		m_renderer(_renderer)
	{}
	void draw_line(const real2 &_s, const real2 &_e, const color &_c, real _width)
	{
		return m_renderer.draw_line(_s, _e, _c, _width);
	}
	void draw_tris(const real2 *_points, const uint *_tris, uint _count, const color &_c, const r3x3 &_position)
	{
		return m_renderer.draw_tris(_points, _tris, _count, _c, _position);
	}

private:
	_Renderer &m_renderer;
};

//

struct player::_loader_interface
{
	virtual ~_loader_interface() {}
	virtual uint open(const wchar* _path) = 0;
	virtual bool good(uint _ID) const = 0;
	virtual uint seek(uint _ID, sint _offset = 0, uint _from = 1) = 0;
	virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
	virtual void close(uint _ID) = 0;
};

// _player_loader_helper_

template<typename _Loader, typename _Interface> struct _player_loader_proxy_ : _Interface
{
	inline _player_loader_proxy_(_Loader &_loader)
	:
		m_loader(_loader)
	{}
	uint open(const wchar* _path)
	{
		return m_loader.open(_path);
	}
	bool good(uint _ID) const
	{
		return m_loader.good(_ID);
	}
	uint seek(uint _ID, sint _offset = 0, uint _from = 0)
	{
		return m_loader.seek(_ID, _offset, _from);
	}
	uint read(uint _ID, handle _buffer, uint _length)
	{
		return m_loader.read(_ID, _buffer, _length);
	}
	void close(uint _ID)
	{
		m_loader.close(_ID);
	}

private:
	_Loader &m_loader;
};

// player

//inline renderer& player::get_renderer() const
//{
//	return *m_renderer_p;
//}
//inline loader& player::get_loader() const
//{
//	return *m_loader_p;
//}
template<typename _R>
inline bool player::create(_R &_renderer)
{
	return m_create(* new _player_renderer_proxy_<_R, _renderer_interface>(_renderer), * new _player_loader_proxy_<bk::loader, _loader_interface>(m_def_loader));
}
template<typename _R, typename _L>
inline bool player::create(_R &_renderer, _L &_loader)
{
	return m_create(* new _player_renderer_proxy_<_R, _renderer_interface>(_renderer), * new _player_loader_proxy_<_L, _loader_interface>(_loader));
}

// player::object

inline player& player::object::get_player() const
{
	return static_cast<player&>(get_manager());
}
