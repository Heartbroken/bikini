/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

typedef matrix_<1, 2, s16> short2;
typedef matrix_<1, 3, f32> float3;
typedef matrix_<2, 3, f32> xform;

///	flash player
/**	[TODO]
 */
struct player
{
	player();
	~player();

	template<typename _Renderer> inline bool create(_Renderer &_renderer);
	template<typename _Renderer, typename _Sensor> inline bool create(_Renderer &_renderer, _Sensor &_sensor);
	template<typename _Renderer, typename _Sensor, typename _Loader> inline bool create(_Renderer &_renderer, _Sensor &_sensor, _Loader &_loader);

	bool update(real _dt);
	bool render() const;

	void destroy();

	bool play(const astring &_path);
	bool play(const wstring &_path);
	bool pause(bool _yes = true);
	bool stop();

private:
	// flash renderer interface
	struct renderer
	{
		virtual uint create_texture(uint _format, pointer _data, uint _width, uint _height, uint _pitch) = 0;
		virtual void destroy_texture(uint _ID) = 0;
		virtual bool begin_render(const color &_background, const rect &_viewport) = 0;
		virtual void set_xform(const xform &_xform) = 0;
		virtual void set_color(const color &_color) = 0;
		virtual void set_texture(uint _ID, const xform &_txform) = 0;
		virtual void draw_tristrip(const short2* _points, uint _count) = 0;
		virtual void end_render() = 0;
	};

	// flash sensor interface
	struct sensor
	{
		virtual uint key_count() const = 0;
		virtual void key_state(uint _i, uint &_code, bool &_state) const = 0;
		virtual void mouse_state(short2 &_point, bool &_button) const = 0;
	};

	// flash loader interface
	struct loader
	{
		virtual uint open(const wchar* _path) = 0;
		virtual bool good(uint _ID) const = 0;
		virtual uint seek(uint _ID, sint _offset = 0, uint _from = 0) = 0;
		virtual uint read(uint _ID, handle _buffer, uint _length) = 0;
		virtual void close(uint _ID) = 0;
	};

	bool create(renderer &_renderer, sensor &_sensor, loader &_loader);
	struct _private; _private *m_private;
};

#include "player.inl"