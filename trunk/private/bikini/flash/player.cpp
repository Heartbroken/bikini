/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// gameswf callbacks

struct player::_gameswf : gameswf::render_handler
{
	// loading ------------------------------------------------------------------------------------

	static loader *loader_p;

	static inline s32 read(handle _buffer, s32 _length, handle _ID) { return (s32)loader_p->read((uint)_ID, _buffer, _length); }
	static inline s32 write(pointer _buffer, s32 _length, handle _ID) { assert(0); return 0; }
	static inline s32 seek(s32 _offset, handle _ID) { return (s32)loader_p->seek((uint)_ID, _offset, 0); }
	static inline s32 seek_to_end(handle _ID) { return (s32)loader_p->seek((uint)_ID, 0, 2); }
	static inline s32 tell(pointer _ID) { return (s32)loader_p->seek((uint)_ID, 0, 1); }
	static inline bool get_eof(handle _ID) { return false; }
	static inline s32 close(handle _ID) { loader_p->close((uint)_ID); return 0; }

	static tu_file* open(const char* _path)
	{
		uint l_alength = strlen(_path) + 1;
		uint l_wlength = MultiByteToWideChar(CP_UTF8, 0, _path, (s32)l_alength, 0, 0);
		wchar* l_path = (wchar*)_malloca(l_wlength * sizeof(wchar));
		MultiByteToWideChar(CP_UTF8, 0, _path, (s32)l_alength, l_path, (s32)l_wlength);
		uint l_ID = loader_p->open(l_path);
		return new tu_file((handle)l_ID, &read, &write, &seek, &seek_to_end, &tell, &get_eof, &close);
	}

	// log ----------------------------------------------------------------------------------------

	static void log(bool _error, const char* _message)
	{
		if (_error) std::cerr << _message;
		else std::cout << _message;
	}

	// rendering ----------------------------------------------------------------------------------

	// gameswf types

	typedef gameswf::bitmap_info bitmap_info;
	typedef gameswf::video_handler video_handler;
	typedef gameswf::rgba rgba;
	typedef gameswf::matrix matrix;
	typedef gameswf::cxform cxform;
	typedef gameswf::rect rect;

	// bitmap

	struct bitmap : bitmap_info
	{
		inline bitmap() {}
		inline bitmap(sint _w, sint _h, u8* _data) {}
		inline bitmap(image::rgb* _data) {}
		inline bitmap(image::rgba* _data) {}
	};

	// state variables

	static renderer *renderer_p;
	matrix m_matrix;
	cxform m_cxform;

	// overrides

	// Your handler should return these with a ref-count of 0.  (@@ is that the right policy?)
	bitmap_info* create_bitmap_info_empty() // used when DO_NOT_LOAD_BITMAPS is set
	{
		return new bitmap;
	}
	bitmap_info* create_bitmap_info_alpha(s32 _w, s32 _h, u8* _data)
	{
		return new bitmap(_w, _h, _data);
	}
	bitmap_info* create_bitmap_info_rgb(image::rgb* _data)
	{
		return new bitmap(_data);
	}
	bitmap_info* create_bitmap_info_rgba(image::rgba* _data)
	{
		return new bitmap(_data);
	}
	video_handler* create_video_handler()
	{
		return 0;
	}

	// Bracket the displaying of a frame from a movie.
	// Fill the background color, and set up default
	// transforms, etc.
	void begin_display(rgba _background_color, s32 _viewport_x0, s32 _viewport_y0, s32 _viewport_width, s32 _viewport_height, f32 _x0, f32 _x1, f32 _y0, f32 _y1)
	{
	}
	void end_display()
	{
	}

	// Geometric and color transforms for mesh and line_strip rendering.
	void set_matrix(const matrix &_m)
	{
		m_matrix = _m;
	}
	void set_cxform(const cxform &_cx)
	{
		m_cxform = _cx;
	}

	// Draw triangles using the current fill-style 0.
	// Clears the style list after rendering.
	//
	// coords is a list of (x,y) coordinate pairs, in
	// triangle-strip order.  The type of the array should
	// be Sint16[vertex_count*2]
	void draw_mesh_strip(pointer _coords, s32 _vertex_count)
	{
	}
	// As above, but coords is in triangle list order.
	void draw_triangle_list(pointer _coords, s32 _vertex_count)
	{
	}

	// Draw a line-strip using the current line style.
	// Clear the style list after rendering.
	//
	// Coords is a list of (x,y) coordinate pairs, in
	// sequence.  Each coord is a 16-bit signed integer.
	void draw_line_strip(pointer _coords, s32 _vertex_count)
	{
	}

	// Set line and fill styles for mesh & line_strip
	// rendering.
	void fill_style_disable(s32 _fill_side)
	{
	}
	void fill_style_color(s32 _fill_side, const rgba &_color)
	{
	}
	void fill_style_bitmap(s32 _fill_side, bitmap_info *_bi_p, const matrix &_m, bitmap_wrap_mode _wm)
	{
	}

	void line_style_disable()
	{
	}
	void line_style_color(rgba _color)
	{
	}
	void line_style_width(f32 _width)
	{
	}

	// Special function to draw a rectangular bitmap;
	// intended for textured glyph rendering.  Ignores
	// current transforms.
	void draw_bitmap(const matrix &_m, bitmap_info *_bi_p, const rect &_coords, const rect &_uv_coords, rgba _color)
	{
	}
	void set_antialiased(bool _enable)
	{
	}

	void begin_submit_mask()
	{
	}
	void end_submit_mask()
	{
	}
	void disable_mask()
	{
	}

	// Mouse cursor handling.
	void set_cursor(cursor_type _cursor)
	{
	}
	bool is_visible(const rect &_bound)
	{
		return true;
	}
	void open()
	{
	}

	// members

	loader &m_loader;
	renderer &m_renderer;
	gameswf::player &m_player;

	_gameswf(renderer &_renderer, loader &_loader)
	:
		m_renderer(_renderer), m_loader(_loader),
		m_player(* new gameswf::player())
	{
		m_player.add_ref();
		gameswf::register_file_opener_callback(&_gameswf::open);
	}
	~_gameswf()
	{
		stop();
		m_player.drop_ref();
		delete &m_renderer;
		delete &m_loader;
	}
	void set_handlers()
	{
		loader_p = &m_loader;
		renderer_p = &m_renderer;
		gameswf::set_render_handler(this);
		gameswf::register_log_callback(log);
	}
	void reset_handlers()
	{
		loader_p = 0;
		renderer_p = 0;
		gameswf::set_render_handler(0);
		gameswf::register_log_callback(0);
	}
	bool play(const achar* _path)
	{
		set_handlers();
		smart_ptr<gameswf::root> l_movie = m_player.load_file(_path);
		reset_handlers();
		if (l_movie == 0) return false;
		l_movie->add_ref();
		return true;
	}
	bool pause(bool _yes)
	{
		if (m_player.get_root() == 0) return false;
		set_handlers();
		m_player.get_root()->set_play_state(_yes ? gameswf::character::PLAY : gameswf::character::STOP);
		reset_handlers();
		return true;
	}
	bool stop()
	{
		if (m_player.get_root() == 0) return false;
		set_handlers();
		m_player.get_root()->drop_ref();
		reset_handlers();
		return true;
	}
	bool update(real _dt)
	{
		set_handlers();
		m_player.get_root()->advance(_dt);
		reset_handlers();
		return true;
	}
	bool render()
	{
		set_handlers();
		m_player.get_root()->display();
		reset_handlers();
		return true;
	}
};
player::loader *player::_gameswf::loader_p = 0;
player::renderer *player::_gameswf::renderer_p = 0;

// player

player::player()
:
	m_gameswf_p(0)
{}
player::~player()
{}
bool player::create(renderer &_renderer, loader &_loader)
{
	m_gameswf_p = new _gameswf(_renderer, _loader);
	return true;
}
bool player::update(real _dt)
{
	return m_gameswf_p->update(_dt);
}
bool player::render() const
{
	return m_gameswf_p->render();
}
void player::destroy()
{
	delete m_gameswf_p;
	m_gameswf_p = 0;
}
bool player::play(const astring &_path)
{
	return m_gameswf_p->play(_path.c_str());
}
bool player::play(const wstring &_path)
{
	uint l_wlength = _path.length() + 1;
	uint l_alength = WideCharToMultiByte(CP_UTF8, 0, _path.c_str(), (s32)l_wlength, 0, 0, 0, 0);
	achar* l_path = (achar*)_malloca(l_alength * sizeof(achar));
	WideCharToMultiByte(CP_UTF8, 0, _path.c_str(), (int)l_wlength, l_path, (int)l_alength, 0, 0);
	return m_gameswf_p->play(l_path);
}
bool player::pause(bool _yes)
{
	return m_gameswf_p->pause(_yes);
}
bool player::stop()
{
	return m_gameswf_p->stop();
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
