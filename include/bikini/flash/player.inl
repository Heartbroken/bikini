/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _player_renderer_proxy_

template<typename _Renderer, typename _Interface> struct _player_renderer_proxy_ : _Interface
{
	inline _player_renderer_proxy_(_Renderer &_renderer) : m_renderer(_renderer) {}
	uint create_texture(uint _format, pointer _data, uint _width, uint _height, uint _pitch) { return m_renderer.create_texture(_format, _data, _width, _height, _pitch); }
	void destroy_texture(uint _ID) { m_renderer.destroy_texture(_ID); }
	bool begin_render(const color &_background, const rect &_viewport) { return m_renderer.begin_render(_background, _viewport); }
	void set_xform(const xform &_xform) { m_renderer.set_xform(_xform); }
	void set_color(const color &_color) { m_renderer.set_color(_color); }
	void set_texture(uint _ID, const xform &_txform) { m_renderer.set_texture(_ID, _txform); }
	void draw_tristrip(const short2* _points, uint _count) { m_renderer.draw_tristrip(_points, _count); }
	void end_render() { m_renderer.end_render(); }

private:
	_Renderer &m_renderer;
};

// _player_loader_proxy_

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

// _player_sensor_prox_

template<typename _Sensor, typename _Interface> struct _player_sensor_prox_ : _Interface
{
	inline _player_sensor_prox_(_Sensor &_sensor) : m_sensor(_sensor) {}
	uint key_count() const { return m_sensor.key_count(); }
	void key_state(uint _i, uint &_code, bool &_state) const { m_sensor.key_state(_i, _code, _state); }
	void mouse_state(short2 &_point, bool &_button) const { m_sensor.mouse_state(_point, _button); }

private:
	_Sensor &m_sensor;
};

// player

extern bk::loader default_loader;

struct null_sensor
{
	inline uint key_count() const { return 0; }
	inline void key_state(uint _i, uint &_code, bool &_state) const {}
	inline void mouse_state(short2 &_point, bool &_button) const { _point = short2(0, 0); _button = false; }
};
extern null_sensor default_sensor;

template<typename _R>
inline bool player::create(_R &_renderer)
{
	return create(*(renderer*) new _player_renderer_proxy_<_R, renderer>(_renderer),
				  *(sensor*) new _player_sensor_prox_<null_sensor, sensor>(default_sensor),
				  *(loader*) new _player_loader_proxy_<bk::loader, loader>(default_loader));
}
template<typename _R, typename _S>
inline bool player::create(_R &_renderer, _S &_sensor)
{
	return create(*(renderer*) new _player_renderer_proxy_<_R, renderer>(_renderer),
				  *(sensor*) new _player_sensor_prox_<_S, sensor>(_sensor),
				  *(loader*) new _player_loader_proxy_<bk::loader, loader>(default_loader));
}
template<typename _R, typename _S, typename _L>
inline bool player::create(_R &_renderer, _S &_sensor, _L &_loader)
{
	return create(*(renderer*) new _player_renderer_proxy_<_R, renderer>(_renderer),
				  *(sensor*) new _player_sensor_prox_<_S, sensor>(_sensor),
				  *(loader*) new _player_loader_proxy_<_L, loader>(_loader));
}
