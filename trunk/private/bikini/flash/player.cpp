/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

// gameswf callbacks

namespace _gameswf_helper {

static loader *loader_p = 0;

static inline sint read(handle _buffer, sint _length, handle _ID) {
	return loader_p->read((uint)_ID, _buffer, _length);
}
static inline sint write(pointer _buffer, sint _length, handle _ID) {
	assert(0); return 0;
}
static inline sint seek(sint _offset, handle _ID) {
	return loader_p->seek((uint)_ID, _offset);
}
static inline sint seek_to_end(handle _ID) {
	return loader_p->seek((uint)_ID, 0, 2);
}
static inline sint tell(pointer _ID) {
	return loader_p->seek((uint)_ID);
}
static inline bool get_eof(handle _ID) {
	return false;
}
static inline sint close(handle _ID) {
	loader_p->close((uint)_ID); return 0;
}
static inline tu_file* open(const char* _path) {
	uint l_alength = strlen(_path) + 1;
	uint l_wlength = MultiByteToWideChar(CP_UTF8, 0, _path, l_alength, 0, 0);
	wchar* l_path = (wchar*)_malloca(l_wlength * sizeof(wchar));
	MultiByteToWideChar(CP_UTF8, 0, _path, (int)l_alength, l_path, (int)l_wlength);
	uint l_ID = loader_p->open(l_path);
	return new tu_file((handle)l_ID, &read, &write, &seek, &seek_to_end, &tell, &get_eof, &close);
}
static inline void log(bool _error, const char* _message) {
	if (_error) std::cerr << _message;
	else std::cout << _message;
}

struct render_handler : gameswf::render_handler {

	typedef gameswf::bitmap_info bitmap_info;
	typedef gameswf::video_handler video_handler;
	typedef gameswf::rgba rgba;
	typedef gameswf::matrix matrix;
	typedef gameswf::cxform cxform;
	typedef gameswf::rect rect;

	struct bitmap : bitmap_info {
		inline bitmap() {}
		inline bitmap(sint _w, sint _h, u8* _data) {}
		inline bitmap(image::rgb* _data) {}
		inline bitmap(image::rgba* _data) {}
	};

	// Your handler should return these with a ref-count of 0.  (@@ is that the right policy?)
	bitmap_info* create_bitmap_info_empty() { return new bitmap; }	// used when DO_NOT_LOAD_BITMAPS is set
	bitmap_info* create_bitmap_info_alpha(sint _w, sint _h, u8* _data) { return new bitmap(_w, _h, _data); }
	bitmap_info* create_bitmap_info_rgb(image::rgb* _data) { return new bitmap(_data); }
	bitmap_info* create_bitmap_info_rgba(image::rgba* _data) { return new bitmap(_data); }
	video_handler* create_video_handler() { return 0; }

	// Bracket the displaying of a frame from a movie.
	// Fill the background color, and set up default
	// transforms, etc.
	void begin_display(rgba _background_color, sint _viewport_x0, sint _viewport_y0, sint _viewport_width, sint _viewport_height, f32 _x0, f32 _x1, f32 _y0, f32 _y1) {
	}
	void end_display() {
	}

	// Geometric and color transforms for mesh and line_strip rendering.
	void set_matrix(const matrix &_m) {}
	void set_cxform(const cxform &_cx) {}

	// Draw triangles using the current fill-style 0.
	// Clears the style list after rendering.
	//
	// coords is a list of (x,y) coordinate pairs, in
	// triangle-strip order.  The type of the array should
	// be Sint16[vertex_count*2]
	void draw_mesh_strip(pointer _coords, sint _vertex_count) {}
	// As above, but coords is in triangle list order.
	void draw_triangle_list(pointer _coords, sint _vertex_count) {}

	// Draw a line-strip using the current line style.
	// Clear the style list after rendering.
	//
	// Coords is a list of (x,y) coordinate pairs, in
	// sequence.  Each coord is a 16-bit signed integer.
	void draw_line_strip(pointer _coords, sint _vertex_count) {}

	// Set line and fill styles for mesh & line_strip
	// rendering.
	void fill_style_disable(sint _fill_side) {}
	void fill_style_color(sint _fill_side, const rgba &_color) {}
	void fill_style_bitmap(sint _fill_side, bitmap_info *_bi_p, const matrix &_m, bitmap_wrap_mode _wm) {}

	void line_style_disable() {}
	void line_style_color(rgba _color) {}
	void line_style_width(f32 _width) {}

	// Special function to draw a rectangular bitmap;
	// intended for textured glyph rendering.  Ignores
	// current transforms.
	void draw_bitmap(const matrix &_m, bitmap_info *_bi_p, const rect &_coords, const rect &_uv_coords, rgba _color) {}
	void set_antialiased(bool _enable) {}

	void begin_submit_mask() {}
	void end_submit_mask() {}
	void disable_mask() {}

	// Mouse cursor handling.
	void set_cursor(cursor_type _cursor) {}
	bool is_visible(const rect &_bound) { return true; }
	void open() {}

private:
	//renderer &m_renderer;
} render_handler;

} // namespace _gameswf_helper

// player

player::player() :
	m_handle(0),
	m_renderer_p(0), m_delete_renderer(false),
	m_loader_p(0), m_delete_loader(false)
{}
player::~player() {
}
bool player::create(renderer &_renderer) {
	m_delete_loader = true;
	return create(_renderer, * new _player_loader_proxy_<bk::loader>(m_def_loader));
}
bool player::create(renderer &_renderer, loader &_loader) {
	m_renderer_p = &_renderer;
	m_loader_p = &_loader;
	gameswf::player &l_player = * new gameswf::player();
	l_player.add_ref();
	m_handle = &l_player;
	return true;
}
bool player::update(real _dt) {
	m_set_handlers();
	for(uint i = 0, s = m_levels.size(); i < s; ++i) if(exists(m_levels[i])) {
		get(m_levels[i]).update(_dt);
	}
	m_reset_handlers();
	return true;
}
void player::destroy() {
	while(!m_levels.empty()) {
		if(exists(m_levels.back())) kill(m_levels.back());
		m_levels.pop_back();
	}
	while(!m_movies.empty()) {
		delete m_movies.back();
		m_movies.pop_back();
		m_movie_names.pop_back();
	}
	((gameswf::player*)m_handle)->drop_ref();
	if(m_delete_renderer) delete m_renderer_p;
	m_renderer_p = 0;
	if(m_delete_loader) delete m_loader_p;
	m_loader_p = 0;
}
uint player::play(const wchar* _path, uint _level) {
	assert(m_renderer_p != 0 && m_loader_p != 0);
	if(m_renderer_p == 0 || m_loader_p == 0) return bad_ID;
	m_set_handlers();
	uint l_level = _level;
	po::movie::info &l_movie = static_cast<po::movie::info&>(m_load_movie(_path));
	if(l_level > m_levels.size()) {
		if(l_level == bad_ID) l_level = m_levels.size();
		m_levels.resize(l_level + 1, bad_ID);
	} else if(m_levels[l_level] != bad_ID) {
		if(exists(m_levels[l_level])) kill(m_levels[l_level]);
		m_levels[l_level] = bad_ID;
	}
	m_levels[l_level] = spawn(l_movie);
	m_reset_handlers();
	return l_level;
}
uint player::play(const achar* _path, uint _level) {
	uint l_length = strlen(_path) + 1;
	wchar* l_path  = (wchar*)_malloca(l_length);
	MultiByteToWideChar(CP_ACP, 0, _path, (int)l_length, l_path, (int)l_length);
	return play(l_path, _level);
}
bool player::pause(uint _level) {
	return true;
}
bool player::stop(uint _level) {
	return true;
}
bool player::show(uint _level) {
	return true;
}
bool player::hide(uint _level) {
	return true;
}
bool player::render(uint _level) const {
	m_set_handlers();
	for(uint i = 0, s = m_levels.size(); i < s; ++i) {
		if((_level == bad_ID || _level == i) && exists(m_levels[i])) {
			get<po::movie>(m_levels[i]).render();
		}
	}
	m_reset_handlers();
	return true;
}
player::object::info& player::m_load_movie(const wchar* _path) {
	array_<wstring>::iterator l_it = std::find(m_movie_names.begin(), m_movie_names.end(), _path);
	if(l_it != m_movie_names.end()) return *m_movies[l_it - m_movie_names.begin()];
	m_movie_names.push_back(_path);
	gameswf::player &l_player = *(gameswf::player*)m_handle;
	uint l_wlength = wcslen(_path) + 1;
	uint l_alength = WideCharToMultiByte(CP_UTF8, 0, _path, l_wlength, 0, 0, 0, 0);
	achar* l_path = (achar*)_malloca(l_alength);
	WideCharToMultiByte(CP_UTF8, 0, _path, l_wlength, l_path, l_alength, 0, 0);
	po::movie::info &l_movie = * new po::movie::info(l_player.create_movie(l_path));
	m_movies.push_back(&l_movie);
	return l_movie;
}
void player::m_set_handlers() const {
	_gameswf_helper::loader_p = m_loader_p;
	gameswf::register_file_opener_callback(_gameswf_helper::open);
	gameswf::register_log_callback(_gameswf_helper::log);
	gameswf::set_render_handler(&_gameswf_helper::render_handler);
}
void player::m_reset_handlers() const {
	_gameswf_helper::loader_p = 0;
	gameswf::register_file_opener_callback(0);
	gameswf::register_log_callback(0);
	gameswf::set_render_handler(0);
}

// player::object

player::object::object(const info &_info, player &_player) :
	manager::object(_info, _player)
{}

// player::object::info

player::object::info::info(uint _type) :
	bk::manager::object::info(_type)
{}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
