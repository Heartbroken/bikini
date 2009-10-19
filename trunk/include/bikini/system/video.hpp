/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct rc
{
};

struct video : device
{

	/* rendering interface ----------------------------------------------------------------------*/

	struct rendering
	{
		/* rendering commands -------------------------------------------------------------------*/

		struct create_schain { uint ID; handle window; };
		struct create_viewport { uint ID; rect area; real2 depth; };
		struct create_vformat { uint ID; pointer data; };
		struct create_vbuffer { uint ID; uint size; };
		struct write_vbuffer { uint ID, size; bool reset; };
		struct create_vshader { uint ID; pointer data; };
		struct create_pshader { uint ID; pointer data; };
		struct create_vbufset { uint ID, vformat_ID, vbuffer_IDs[8], offsets[8], strides[8]; };
		struct create_states { uint ID; pointer data; };
		struct create_consts { uint ID; };
		struct write_consts { uint ID, size; bool reset; };
		struct create_texture { uint ID; sint2 size; uint format; };
		struct write_texture { uint ID; uint size; };
		struct create_texset { uint ID, texture_IDs[8]; };
		struct destroy_resource { uint ID; };
		struct begin_scene {};
		struct clear_viewport { uint target_ID, viewport_ID; struct { uint f; color c; real z; uint s; } clear; };
		struct draw_primitive { uint target_ID, viewport_ID, vbufset_ID, vshader_ID, pshader_ID, states_ID, consts_ID, texset_ID, type, start, size; };
		struct end_scene {};
		struct present_schain { uint ID; };

		typedef make_typelist_<
			create_schain, create_viewport, create_vformat, create_vbuffer, write_vbuffer,
			create_vshader, create_pshader, create_vbufset, create_states, create_consts, write_consts,
			create_texture, write_texture, create_texset,
			destroy_resource,
			begin_scene, clear_viewport, draw_primitive, end_scene,
			present_schain
		>::type command_types;

		typedef variant_<command_types, false> command;
		typedef ring_<command> command_ring;

		typedef ring_<byte> data_ring;

		/* rendering issues ---------------------------------------------------------------------*/

		struct validate_resource { uint ID; };
		struct invalidate_resource { uint ID; };

		typedef make_typelist_<
			validate_resource, invalidate_resource
		>::type issue_types;

		typedef variant_<issue_types> issue;
		typedef ring_<issue> issue_ring;

		/* rendering ----------------------------------------------------------------------------*/

		video& get_video() const { return m_video; }

		rendering(video &_video);
		virtual ~rendering();
		virtual bool initialize() = 0;
		virtual void finalize() = 0;
		virtual bool execute(const command &_command) = 0;

	protected:
		void set_valid(uint _ID);
		void set_invalid(uint _ID);
		bool get_data(handle _data, uint _size);
		void throw_data(uint _size);

	private:
		friend video;
		bool create();
		void destroy();
		video &m_video;
		thread::task m_task;
		bool m_run;
		void m_proc();
		command_ring m_cbuffer;
		static const uint cbuffer_size = 1000;
		thread::flag m_has_command;
		bool add_command(const command &_command);
		data_ring m_dbuffer;
		static const uint dbuffer_size = 1024 * 1024 * 5;
		static const uint dbuffer_MTU = 1024;
		static const uint dbuffer_timeout = 1000;
		thread::flag m_can_read_data;
		thread::flag m_can_write_data;
		bool add_data(pointer _data, uint _size);
		issue_ring m_ibuffer;
		static const uint ibuffer_size = 1000;
		bool add_issue(const issue &_issue);
		issue get_issue();
	};
	
	/* video object -----------------------------------------------------------------------------*/

	struct object : device::object
	{
		struct info : device::object::info
		{
			typedef video manager;
			info(uint _type);
		};

		struct context;

		inline video& get_video() const { return static_cast<video&>(get_device()); }

		object(const info &_info, video &_video);

	protected:
		inline void add_command(const rendering::command &_command) const { get_video().add_command(_command); }
		inline void add_command(u64 _sort_key, const rendering::command &_command) const { get_video().add_command(_sort_key, _command); }
		inline void add_data(pointer _data, uint _size) const { get_video().add_data(_data, _size); }
		inline uint obtain_resource_ID() const { return get_video().obtain_resource_ID(); }
		inline void release_resource_ID(uint _ID) const { get_video().release_resource_ID(_ID); }
		inline bool resource_exists(uint _ID) const { return get_video().resource_exists(_ID); }
		inline bool resource_valid(uint _ID) const { return get_video().resource_valid(_ID); }
	};

	struct ot { enum object_type
	{
		window, viewport, drawcall, vformat, vbuffer, memreader, vshader, pshader, vbufset, states, consts, texture, texset
	};};

	/* video ------------------------------------------------------------------------------------*/

	struct tf { enum texture_format
	{
		a8, b8g8r8, a8b8g8r8, a8r8g8b8
	};};

	video();
	~video();

	bool create();
	bool update(real _dt);
	void destroy();

private:
	rendering &m_rendering;
	rendering& new_rendering(video &_video);
	inline rendering& get_rendering() const { return m_rendering; }

	typedef rendering::command command;
	typedef std::multimap<u64, command> command_map;
	command_map m_cbuffer;
	inline void add_command(const command &_command);
	inline void add_command(u64 _sort_key, const command &_command);
	inline void add_data(pointer _data, uint _size);

	pool_<bool> m_resources;
	uint obtain_resource_ID();
	void release_resource_ID(uint _ID);
	bool resource_exists(uint _ID);
	bool resource_valid(uint _ID);
	void set_resource_valid(uint _ID);
	void set_resource_invalid(uint _ID);
};

namespace cf { enum clear_flags {
	color = 1<<0,
	depth = 1<<1,
	stencil = 1<<2,
	all = color|depth|stencil,
};}

namespace vo { /* video objects -----------------------------------------------------------------*/

/// texset
struct texset : video::object
{
	struct info : video::object::info
	{
		typedef texset object;
		info();
	};

	static const uint texture_count = 8;

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	texset(const info &_info, video &_video);
	~texset();

	bool update(real _dt);

	void set_texture(uint _i, uint _ID);

private:
	uint m_resource_ID;
	uint m_texture_IDs[texture_count];
};

/// texture
struct texture : video::object
{
	struct info : video::object::info
	{
		typedef texture object;
		uint format; sint2 size; uint levels;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	texture(const info &_info, video &_video);
	~texture();

	bool update(real _dt);

	void set_source(uint _ID);

private:
	uint m_resource_ID;
	uint m_source_ID;
};

/// consts
struct consts : video::object
{
	struct info : video::object::info
	{
		typedef consts object;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	consts(const info &_info, video &_video);
	~consts();

	bool update(real _dt);

	void write(uint _type, uint _offset, pointer _data, uint _size);
	template<typename _Type> inline void write(uint _type, uint _offset, const _Type &_v) { write(_type, _offset, &_v, sizeof(_v)); }

private:
	uint m_resource_ID;
	byte_array m_data;
};

/// states
struct states : video::object
{
	struct info : video::object::info
	{
		typedef states object;
		pointer data;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	states(const info &_info, video &_video);
	~states();

	bool update(real _dt);

private:
	uint m_resource_ID;
};

/// vbufset
struct vbufset : video::object
{
	struct info : video::object::info
	{
		typedef vbufset object;
		info();
	};

	static const uint vbuffer_count = 8;

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	vbufset(const info &_info, video &_video);
	~vbufset();

	bool update(real _dt);

	void set_vformat(uint _ID);
	void set_vbuffer(uint _i, uint _ID, uint _offset, uint _stride);

private:
	uint m_resource_ID;
	uint m_vformat_ID;
	uint m_vbuffer_IDs[vbuffer_count], m_offsets[vbuffer_count], m_strides[vbuffer_count];
};

/// pshader
struct pshader : video::object
{
	struct info : video::object::info
	{
		typedef pshader object;
		pointer data;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	pshader(const info &_info, video &_video);
	~pshader();

	bool update(real _dt);

private:
	uint m_resource_ID;
};

/// vshader
struct vshader : video::object
{
	struct info : video::object::info
	{
		typedef vshader object;
		pointer data;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	vshader(const info &_info, video &_video);
	~vshader();

	bool update(real _dt);

private:
	uint m_resource_ID;
};

/// memreader
struct memreader : video::object
{
	struct info : video::object::info
	{
		typedef memreader object;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline bool empty() const { return m_data.empty(); }
	inline uint size() const { return m_data.size(); }
	inline pointer data() const { return m_data.empty() ? 0 : &m_data[0]; }

	memreader(const info &_info, video &_video);
	~memreader();

	bool update(real _dt);

	void clear();
	void write(pointer _data, uint _size);

private:
	byte_array m_data;
};

/// vbuffer
struct vbuffer : video::object
{
	struct info : video::object::info
	{
		typedef vbuffer object;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	vbuffer(const info &_info, video &_video);
	~vbuffer();

	bool update(real _dt);

	void set_source(uint _ID);

private:
	uint m_resource_ID;
	uint m_source_ID;
	uint m_size;
};

/// vformat
struct vformat : video::object
{
	struct info : video::object::info
	{
		typedef vformat object;
		pointer data;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	vformat(const info &_info, video &_video);
	~vformat();

	bool update(real _dt);

private:
	uint m_resource_ID;
};

/// drawcall
struct drawcall : video::object
{
	struct info : video::object::info
	{
		typedef drawcall object;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline void set_start(uint _start) { m_start = _start; }
	inline void set_size(uint _size) { m_size = _size; }

	drawcall(const info &_info, video &_video);
	~drawcall();

	bool update(real _dt);

	void set_vbufset(uint _ID);
	void set_shaders(uint _vshader_ID, uint _pshader_ID);
	void set_states(uint _ID);
	void write_consts(uint _type, uint _offset, pointer _data, uint _size);
	template<typename _Type> inline void write_consts(uint _type, uint _offset, const _Type &_v) { write_consts(_type, _offset, &_v, sizeof(_v)); }
	void set_texset(uint _ID);

	void add_commands(const context &_context) const;

private:
	uint m_start, m_size;
	uint m_vbufset_ID;
	uint m_vshader_ID, m_pshader_ID;
	uint m_states_ID;
	consts::info m_consts; uint m_consts_ID;
	uint m_texset_ID;
};

/// viewport
struct viewport : video::object
{
	struct info : video::object::info
	{
		typedef viewport object;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	inline const rect& area() const { return m_area; }
	inline void set_area(const rect &_r) { m_area = _r; }
	inline const real2& depth() const { return m_depth; }
	inline void set_depth(const real2 &_d) { m_depth = _d; }
	inline void set_clear_flags(uint _f) { m_clear.f = _f; }
	inline void set_clear_color(const color &_c) { m_clear.c = _c; }

	viewport(const info &_info, video &_video);
	~viewport();

	drawcall& add_drawcall();
	void remove_drawcall(uint _i);
	uint drawcall_count() const;
	uint drawcall_ID(uint _i) const;
	void clear();

	bool update(real _dt);

	void add_commands(const context &_context) const;

private:
	uint m_resource_ID;
	rect m_area; real2 m_depth;
	struct { uint f; color c; } m_clear;
	drawcall::info m_drawcall;
	uint_array m_drawcalls;
};

/// window
struct window : video::object
{
	struct info : video::object::info
	{
		typedef window object;
		typedef HWND a0;
		info();
	};

	inline const info& get_info() const { return get_info_<info>(); }
	inline uint resource_ID() const { return m_resource_ID; }

	window(const info &_info, video &_video, HWND _window);
	~window();

	bool update(real _dt);

	uint add_viewport();
	void remove_viewport(uint _i);
	uint viewport_count() const;
	uint viewport_ID(uint _i) const;
	void clear();

private:
	HWND m_window;
	uint m_resource_ID;
	static long _stdcall _wndproc(HWND _window, uint _message, uint _wparam, uint _lparam);
	static window *first_p; window *next_p;
	long m_wndproc(uint _message, uint _wparam, uint _lparam);
	WNDPROC m_oldwndproc;
	viewport::info m_viewport_info;
	uint_array m_viewports;
	enum { erase_background = (1<<0), force_redraw = (1<<1) };
	uint m_flags;
};

} /* video objects ------------------------------------------------------------------------------*/