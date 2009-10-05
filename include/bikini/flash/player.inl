/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _player_renderer_helper_

template<typename _Renderer, typename _Interface> struct _player_renderer_proxy_ : _Interface
{
	inline _player_renderer_proxy_(_Renderer &_renderer) : m_renderer(_renderer) {}
	bool begin_render(const rect &_viewport) { return m_renderer.begin_render(_viewport); }
	void draw_tristrip(const xform &_xform, const color &_color, const short2* _points, uint _count) { m_renderer.draw_tristrip(_xform, _color, _points, _count); }
	void end_render() { m_renderer.end_render(); }

private:
	_Renderer &m_renderer;
};

// _player_loader_helper_

template<typename _Loader, typename _Interface> struct _player_loader_proxy_ : _Interface
{
	inline _player_loader_proxy_(_Loader &_loader) : m_loader(_loader) {}
	uint open(const wchar* _path) { return m_loader.open(_path); }
	bool good(uint _ID) const { return m_loader.good(_ID); }
	uint seek(uint _ID, sint _offset = 0, uint _from = 0) { return m_loader.seek(_ID, _offset, _from); }
	uint read(uint _ID, handle _buffer, uint _length) { return m_loader.read(_ID, _buffer, _length); }
	void close(uint _ID) { m_loader.close(_ID); }

private:
	_Loader &m_loader;
};

// player

template<typename _R>
inline bool player::create(_R &_renderer)
{
	return create(*(renderer*) new _player_renderer_proxy_<_R, renderer>(_renderer),
				  *(loader*) new _player_loader_proxy_<bk::loader, loader>(m_defloader));
}
template<typename _R, typename _L>
inline bool player::create(_R &_renderer, _L &_loader)
{
	return create(*(renderer*) new _player_renderer_proxy_<_R, renderer>(_renderer),
				  *(loader*) new _player_loader_proxy_<_L, loader>(_loader));
}
