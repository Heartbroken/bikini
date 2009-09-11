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
	// loading

	static loader *loader_p;

	static inline sint read(handle _buffer, sint _length, handle _ID) { return loader_p->read((uint)_ID, _buffer, _length); }
	static inline sint write(pointer _buffer, sint _length, handle _ID) { assert(0); return 0; }
	static inline sint seek(sint _offset, handle _ID) { return loader_p->seek((uint)_ID, _offset, 0); }
	static inline sint seek_to_end(handle _ID) { return loader_p->seek((uint)_ID, 0, 2); }
	static inline sint tell(pointer _ID) { return loader_p->seek((uint)_ID, 0, 1); }
	static inline bool get_eof(handle _ID) { return false; }
	static inline sint close(handle _ID) { loader_p->close((uint)_ID); return 0; }

	static tu_file* open(const char* _path)
	{
		uint l_alength = strlen(_path) + 1;
		uint l_wlength = MultiByteToWideChar(CP_UTF8, 0, _path, l_alength, 0, 0);
		wchar* l_path = (wchar*)_malloca(l_wlength * sizeof(wchar));
		MultiByteToWideChar(CP_UTF8, 0, _path, (int)l_alength, l_path, (int)l_wlength);
		uint l_ID = loader_p->open(l_path);
		return new tu_file((handle)l_ID, &read, &write, &seek, &seek_to_end, &tell, &get_eof, &close);
	}

	// log

	static void log(bool _error, const char* _message)
	{
		if (_error) std::cerr << _message;
		else std::cout << _message;
	}

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

	// members

	renderer &m_renderer;
	loader &m_loader;
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
		m_player.drop_ref();
		delete &m_renderer;
		delete &m_loader;
	}
	bool play(const achar* _path)
	{
		loader_p = &m_loader;
		smart_ptr<gameswf::root> l_movie = m_player.load_file(_path);
		loader_p = 0;
		if (l_movie == 0) return false;
		l_movie->add_ref();
		m_player.set_root(l_movie.get_ptr());
		return true;

	}

	// render_handler overrides

	// Your handler should return these with a ref-count of 0.  (@@ is that the right policy?)
	bitmap_info* create_bitmap_info_empty() { return new bitmap; }	// used when DO_NOT_LOAD_BITMAPS is set
	bitmap_info* create_bitmap_info_alpha(sint _w, sint _h, u8* _data) { return new bitmap(_w, _h, _data); }
	bitmap_info* create_bitmap_info_rgb(image::rgb* _data) { return new bitmap(_data); }
	bitmap_info* create_bitmap_info_rgba(image::rgba* _data) { return new bitmap(_data); }
	video_handler* create_video_handler() { return 0; }

	// Bracket the displaying of a frame from a movie.
	// Fill the background color, and set up default
	// transforms, etc.
	void begin_display(rgba _background_color, sint _viewport_x0, sint _viewport_y0, sint _viewport_width, sint _viewport_height, f32 _x0, f32 _x1, f32 _y0, f32 _y1)
	{
	}
	void end_display()
	{
	}

	// Geometric and color transforms for mesh and line_strip rendering.
	void set_matrix(const matrix &_m)
	{
	}
	void set_cxform(const cxform &_cx)
	{
	}

	// Draw triangles using the current fill-style 0.
	// Clears the style list after rendering.
	//
	// coords is a list of (x,y) coordinate pairs, in
	// triangle-strip order.  The type of the array should
	// be Sint16[vertex_count*2]
	void draw_mesh_strip(pointer _coords, sint _vertex_count)
	{
	}
	// As above, but coords is in triangle list order.
	void draw_triangle_list(pointer _coords, sint _vertex_count)
	{
	}

	// Draw a line-strip using the current line style.
	// Clear the style list after rendering.
	//
	// Coords is a list of (x,y) coordinate pairs, in
	// sequence.  Each coord is a 16-bit signed integer.
	void draw_line_strip(pointer _coords, sint _vertex_count)
	{
	}

	// Set line and fill styles for mesh & line_strip
	// rendering.
	void fill_style_disable(sint _fill_side)
	{
	}
	void fill_style_color(sint _fill_side, const rgba &_color)
	{
	}
	void fill_style_bitmap(sint _fill_side, bitmap_info *_bi_p, const matrix &_m, bitmap_wrap_mode _wm)
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
};
player::loader *player::_gameswf::loader_p = 0;

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
	return true;
}
bool player::render() const
{
	return true;
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
	uint l_alength = WideCharToMultiByte(CP_UTF8, 0, _path.c_str(), l_wlength, 0, 0, 0, 0);
	achar* l_path = (achar*)_malloca(l_alength * sizeof(achar));
	WideCharToMultiByte(CP_UTF8, 0, _path.c_str(), (int)l_wlength, l_path, (int)l_alength, 0, 0);
	return m_gameswf_p->play(l_path);
}
bool player::pause(bool _yes)
{
	return _yes;
}
bool player::stop()
{
	return true;
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
