/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"


#define GWL_WNDPROC			(-4)
#define USE_RENDERING_THREAD	1

namespace bk { /*--------------------------------------------------------------------------------*/

// video::rendering

video::rendering::rendering(video &_video)
:
	m_video(_video),
	m_task(*this, &rendering::m_proc, "bikini-iii rendering"),
	m_cbuffer(cbuffer_size), m_dbuffer(dbuffer_size), m_ibuffer(ibuffer_size),
	m_has_command(false, false), m_can_read_data(false, false), m_can_write_data(false, true)
{}
video::rendering::~rendering()
{
}
bool video::rendering::create()
{
#if USE_RENDERING_THREAD
	m_run = true;
	if (!m_task.run())
	{
		m_run = false;
		return false;
	}
#else
	m_task.run();
	initialize();
#endif
	return true;
}
void video::rendering::destroy()
{
#if USE_RENDERING_THREAD
	if (m_run)
	{
		m_run = false;
		m_task.wait();
	}
#else
	finalize();
#endif
}
bool video::rendering::add_command(const command &_command)
{
	while (!m_cbuffer.push(_command)) sleep(0.001f);
	m_has_command.set();
	return true;
}
bool video::rendering::add_data(pointer _data, uint _size)
{
	byte* l_data = (byte*)_data;
	uint l_size = _size;

	while (l_size > 0)
	{
		uint l_write = min(l_size, dbuffer_MTU);

		if (m_dbuffer.write(l_data, l_write))
		{
			l_data += l_write;
			l_size -= l_write;

			m_can_read_data.set();
		}
		else
		{
			if (!m_can_write_data.wait(real(dbuffer_timeout) * real(0.001)))
			{
				std::cerr << "ERROR: Rendering data write failed.\n";
				return false;
			}
		}
	}

	return true;

////////
//	if (_size > m_dbuffer.free_space())
//	{
//		std::cerr << "ERROR: Renderer data buffer has no free space.\n";
//		return false;
//	}
//
//	m_dbuffer.write((byte*)_data, _size);
//
//	return true;
}
bool video::rendering::get_data(handle _data, uint _size)
{
	byte* l_data = (byte*)_data;
	uint l_size = _size;

	while (l_size > 0)
	{
		uint l_read = min(l_size, dbuffer_MTU);

		if (m_dbuffer.read(l_data, l_read))
		{
			l_data += l_read;
			l_size -= l_read;

			m_can_write_data.set();
		}
		else
		{
			if (!m_can_read_data.wait(real(dbuffer_timeout) * real(0.001)))
			{
				std::cerr << "ERROR: Rendering data read failed.\n";
				return false;
			}
		}
	}

	return true;

///////
//	if (_size > m_dbuffer.used_space())
//	{
//		std::cerr << "ERROR: Renderer data buffer has no data.\n";
//		return false;
//	}
//
//	return m_dbuffer.read((byte*)_data, _size);
}
void video::rendering::throw_data(uint _size)
{
	for (uint i = 0; i < _size; ++i)
	{
		if (m_dbuffer.empty())
		{
			std::cerr << "ERROR: Renderer data buffer has no data.\n";
			break;
		}

		m_dbuffer.pop();
	}
}
bool video::rendering::add_issue(const issue &_issue)
{
	while (!m_ibuffer.push(_issue)) sleep(0.001f);

	return true;
}
video::rendering::issue video::rendering::get_issue()
{
	issue l_issue;

	if (!m_ibuffer.empty())
	{
		l_issue = m_ibuffer.front();
		m_ibuffer.pop();
	}

	return l_issue;
}
void video::rendering::set_valid(uint _ID)
{
	validate_resource l_validate_resource;
	l_validate_resource.ID = _ID;
	add_issue(l_validate_resource);
}
void video::rendering::set_invalid(uint _ID)
{
	invalidate_resource l_invalidate_resource;
	l_invalidate_resource.ID = _ID;
	add_issue(l_invalidate_resource);
}

struct _key_field { uint start, size; };

static const uint key_size = sizeof(u64) * 8;
static const _key_field command_type = { key_size - 1, 3 };
static const _key_field command_draw_stage = { command_type.start - command_type.size, 3 };
static const _key_field command_draw_target = { command_draw_stage.start - command_draw_stage.size, 6 };
static const _key_field command_draw_viewport = { command_draw_target.start - command_draw_target.size, 6 };
static const _key_field command_draw_sequence = { command_draw_viewport.start - command_draw_viewport.size, 6 };

struct ct { enum command_types {
	begin, draw, end, present
};};

static inline void set_key_field(u64 & _key, const _key_field &_field, u64 _value)
{
	u64 l_field = _value << (key_size - _field.size) >> (key_size - _field.start - 1);
	_key = _key | l_field;
}

void video::rendering::m_proc()
{
#if USE_RENDERING_THREAD
	if (initialize())
	{
		while (m_run)
		{
			if (!m_cbuffer.empty())
			{
				m_has_command.wait(0);

				if (!execute(m_cbuffer.front()))
				{
					throw_data(m_cbuffer.front().get_<_command>().extra);
				}

				m_cbuffer.pop();
			}
			else
			{
				m_has_command.wait(real(0.1));
			}
		}

		finalize();
	}
#endif
}

// video

const video::vf::element video::vf::last_element = { 0, 0, video::vf::none, 0, 0 };

video::video()
:
	m_rendering(new_rendering(*this))
{}
video::~video()
{
	delete &m_rendering;
}
bool video::create()
{
	if (&m_rendering == 0) return false;

	if (!m_rendering.create()) return false;

	return true;
}
bool video::update(real _dt)
{
	rendering::issue l_issue;
	while (!(l_issue = m_rendering.get_issue()).is_nothing())
	{
		switch (l_issue.type())
		{
			case rendering::issue_types::type_<rendering::validate_resource>::index :
			{
				rendering::validate_resource &l_validate_resource = l_issue.get_<rendering::validate_resource>();
				if (resource_exists(l_validate_resource.ID))
				{
					set_resource_valid(l_validate_resource.ID);
				}
				break;
			}
			case rendering::issue_types::type_<rendering::invalidate_resource>::index :
			{
				rendering::invalidate_resource &l_invalidate_resource = l_issue.get_<rendering::invalidate_resource>();
				if (resource_exists(l_invalidate_resource.ID))
				{
					set_resource_invalid(l_invalidate_resource.ID);
				}
				break;
			}
		}
	}

	if(!super::update(_dt)) return false;

	if (!m_cbuffer.empty())
	{
		u64 l_key;

		l_key = 0;
		set_key_field(l_key, command_type, ct::begin);
		add_command(l_key, rendering::begin_scene());

		l_key = 0;
		set_key_field(l_key, command_type, ct::end);
		add_command(l_key, rendering::end_scene());

		for (command_map::iterator i = m_cbuffer.begin(), e = m_cbuffer.end(); i != e; ++i)
		{
#if USE_RENDERING_THREAD
			if (!m_rendering.add_command(i->second))
			{
				std::cerr << "WARNING: Rendering command buffer is full.\n";

				// If ring buffer is full. Wait and retry
				while (!m_rendering.add_command(i->second)) sleep(0);
			}
#else
			if (!m_rendering.execute(i->second))
			{
				m_rendering.throw_data(i->second.get_<_command>().extra);
			}
#endif
		}

		m_cbuffer.clear();
	}

	return true;
}
void video::destroy()
{
	m_rendering.destroy();
	super::destroy();
}
inline void video::add_command(const command &_command)
{
#if USE_RENDERING_THREAD
	m_rendering.add_command(_command);
#else
	m_rendering.execute(_command);
#endif
}
inline void video::add_command(u64 _sort_key, const command &_command)
{
	m_cbuffer.insert(std::pair<u64, command>(_sort_key, _command));
}
inline void video::add_data(pointer _data, uint _size)
{
	m_rendering.add_data(_data, _size);
}
uint video::obtain_resource_ID()
{
	return m_resources.add(false);
}
void video::release_resource_ID(uint _ID)
{
	m_resources.remove(_ID);
}
bool video::resource_exists(uint _ID)
{
	return m_resources.exists(_ID);
}
bool video::resource_valid(uint _ID)
{
	return m_resources.get(_ID);
}
void video::set_resource_valid(uint _ID)
{
	m_resources.get(_ID) = true;
}
void video::set_resource_invalid(uint _ID)
{
	m_resources.get(_ID) = false;
}

// video::object::info

video::object::info::info(uint _type)
:
	device::object::info(_type)
{}

// video::object

video::object::object(const info &_info, video &_video)
:
	device::object(_info, _video)
{}

// video::object::context

struct video::object::context
{
	uint target_ID;
	struct { rect area; real2 depth; } viewport;
	uint viewport_ID;
	uint sequence;
};


namespace vo { /* video objects -----------------------------------------------------------------*/

// texset::info

texset::info::info()
:
	video::object::info(video::ot::texset)
{}

// texset

texset::texset(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	memset(m_texture_IDs, 0xff, sizeof(m_texture_IDs));
	m_resource_ID = obtain_resource_ID();
}
texset::~texset()
{
	release_resource_ID(m_resource_ID);
}
bool texset::update(real _dt)
{
	if (!valid() || !resource_valid(m_resource_ID))
	{
		video::rendering::create_texset l_create_texset;
		l_create_texset.ID = m_resource_ID;
		for (uint i = 0; i < texture_count; ++i)
		{
			if (has_relation(m_texture_IDs[i]))
			{
				uint l_texture_ID = get_relation(m_texture_IDs[i]);
				if (get_video().exists(l_texture_ID) && get_video().get(l_texture_ID).type() == video::ot::texture)
				{
					texture &l_texture = get_video().get_<texture>(l_texture_ID);
					l_create_texset.texture_IDs[i] = l_texture.resource_ID();
					continue;
				}
			}
			l_create_texset.texture_IDs[i] = bad_ID;
		}
		add_command(l_create_texset);

		update_version();
	}

	return true;
}
void texset::set_texture(uint _i, uint _ID)
{
	if (_i >= texture_count) return;

	if (has_relation(m_texture_IDs[_i])) remove_relation(m_texture_IDs[_i]);

	if (get_video().exists(_ID)) m_texture_IDs[_i] = add_relation(_ID);
	else m_texture_IDs[_i] = bad_ID;
}

// texture::info

texture::info::info()
:
	video::object::info(video::ot::texture),
	format(video::tf::a8r8g8b8), size(sint2_1), levels(0)
{}

// texture

texture::texture(const info &_info, video &_video)
:
	video::object(_info, _video),
	m_source_ID(bad_ID)
{
	m_resource_ID = obtain_resource_ID();
}
texture::~texture()
{
	release_resource_ID(m_resource_ID);
}
bool texture::update(real _dt)
{
	if (has_relation(m_source_ID))
	{
		uint l_source_ID = get_relation(m_source_ID);
		if (get_video().exists(l_source_ID))
		{
			object &l_object = get_video().get_<object>(l_source_ID);
			if (!valid() || version() < l_object.version())
			{
				switch (l_object.type())
				{
					case video::ot::memreader :
					{
						video::rendering::create_texture l_create_texture;
						l_create_texture.ID = m_resource_ID;
						l_create_texture.format = get_info().format;
						l_create_texture.size = get_info().size;
						add_command(l_create_texture);

						memreader &l_reader = get_video().get_<memreader>(l_source_ID);

						video::rendering::write_texture l_write_texture;
						l_write_texture.ID = m_resource_ID;
						l_write_texture.extra = l_reader.size();
						add_command(l_write_texture);

						add_data(l_reader.data(), l_reader.size());

						break;
					}
				}

				update_version();
			}
		}
	}
	else
	{
		if (!valid() || !resource_valid(m_resource_ID))
		{
			video::rendering::create_texture l_create_texture;
			l_create_texture.ID = m_resource_ID;
			l_create_texture.format = get_info().format;
			l_create_texture.size = get_info().size;
			add_command(l_create_texture);

			update_version();
		}
	}

	return true;
}
void texture::set_source(uint _ID)
{
	if (has_relation(m_source_ID)) remove_relation(m_source_ID);

	if (get_video().exists(_ID)) m_source_ID = add_relation(_ID);
	else m_source_ID = bad_ID;
}

// consts::info

consts::info::info()
:
	video::object::info(video::ot::consts)
{}

// consts

consts::consts(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	m_resource_ID = obtain_resource_ID();
}
consts::~consts()
{
	release_resource_ID(m_resource_ID);
}
bool consts::update(real _dt)
{
	if (!m_data.empty() && !resource_valid(m_resource_ID))
	{
		video::rendering::create_consts l_create_consts;
		l_create_consts.ID = m_resource_ID;
		add_command(l_create_consts);

		video::rendering::write_consts l_write_consts;
		l_write_consts.ID = m_resource_ID;
		add_data(&m_data[0], m_data.size());
		l_write_consts.extra = m_data.size();
		l_write_consts.reset = true;
		add_command(l_write_consts);
	}

	return true;
}
void consts::write(uint _type, uint _offset, pointer _data, uint _size)
{
	struct _l { static inline void push(byte_array &_a, pointer _data, uint _size)
	{
		_a.insert(_a.end(), (byte*)_data, (byte*)_data + _size);
	}};

	_l::push(m_data, &_type, sizeof(_type));
	_l::push(m_data, &_offset, sizeof(_offset));
	_l::push(m_data, &_size, sizeof(_size));
	_l::push(m_data, _data, _size);
}

// states::info

states::info::info()
:
	video::object::info(video::ot::states),
	data(0)
{}

// states

states::states(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	m_resource_ID = obtain_resource_ID();
}
states::~states()
{
	release_resource_ID(m_resource_ID);
}
bool states::update(real _dt)
{
	if (!resource_valid(m_resource_ID))
	{
		video::rendering::create_states l_create_states;
		l_create_states.ID = m_resource_ID;
		l_create_states.data = get_info().data;
		add_command(l_create_states);
	}

	return true;
}

// vbufset::info

vbufset::info::info()
:
	video::object::info(video::ot::vbufset)
{}

// vbufset

vbufset::vbufset(const info &_info, video &_video)
:
	video::object(_info, _video),
	m_vformat_ID(bad_ID)
{
	memset(m_vbuffer_IDs, 0xff, sizeof(m_vbuffer_IDs));
	m_resource_ID = obtain_resource_ID();
}
vbufset::~vbufset()
{
	release_resource_ID(m_resource_ID);
}
bool vbufset::update(real _dt)
{
	if (!valid() || !resource_valid(m_resource_ID))
	{
		video::rendering::create_vbufset l_create_vbufset;
		l_create_vbufset.ID = m_resource_ID;
		if (has_relation(m_vformat_ID))
		{
			uint l_vformat_ID = get_relation(m_vformat_ID);
			if (get_video().exists(l_vformat_ID) && get_video().get(l_vformat_ID).type() == video::ot::vformat)
			{
				vformat &l_vformat = get_video().get_<vformat>(l_vformat_ID);
				l_create_vbufset.vformat_ID = l_vformat.resource_ID();
			}
		}
		for (uint i = 0; i < vbuffer_count; ++i)
		{
			if (has_relation(m_vbuffer_IDs[i]))
			{
				uint l_vbuffer_ID = get_relation(m_vbuffer_IDs[i]);
				if (get_video().exists(l_vbuffer_ID) && get_video().get(l_vbuffer_ID).type() == video::ot::vbuffer)
				{
					vbuffer &l_vbuffer = get_video().get_<vbuffer>(l_vbuffer_ID);
					l_create_vbufset.vbuffer_IDs[i] = l_vbuffer.resource_ID();
					l_create_vbufset.offsets[i] = m_offsets[i];
					l_create_vbufset.strides[i] = m_strides[i];
					continue;
				}
			}
			l_create_vbufset.vbuffer_IDs[i] = bad_ID;
		}
		add_command(l_create_vbufset);

		update_version();
	}

	return true;
}
void vbufset::set_vformat(uint _ID)
{
	if (has_relation(m_vformat_ID)) remove_relation(m_vformat_ID);

	if (get_video().exists(_ID)) m_vformat_ID = add_relation(_ID);
	else m_vformat_ID = bad_ID;
}
void vbufset::set_vbuffer(uint _i, uint _ID, uint _offset, uint _stride)
{
	if (_i >= vbuffer_count) return;

	if (has_relation(m_vbuffer_IDs[_i])) remove_relation(m_vbuffer_IDs[_i]);

	if (get_video().exists(_ID)) m_vbuffer_IDs[_i] = add_relation(_ID);
	else m_vbuffer_IDs[_i] = bad_ID;

	m_offsets[_i] = _offset;
	m_strides[_i] = _stride;
}

// pshader::info

pshader::info::info()
:
	video::object::info(video::ot::pshader),
	data(0)
{}

// pshader

pshader::pshader(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	m_resource_ID = obtain_resource_ID();
}
pshader::~pshader()
{
	release_resource_ID(m_resource_ID);
}
bool pshader::update(real _dt)
{
	if (!resource_valid(m_resource_ID))
	{
		video::rendering::create_pshader l_create_pshader;
		l_create_pshader.ID = m_resource_ID;
		l_create_pshader.data = get_info().data;
		add_command(l_create_pshader);
	}

	return true;
}

// vshader::info

vshader::info::info()
:
	video::object::info(video::ot::vshader),
	data(0)
{}

// vshader

vshader::vshader(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	m_resource_ID = obtain_resource_ID();
}
vshader::~vshader()
{
	release_resource_ID(m_resource_ID);
}
bool vshader::update(real _dt)
{
	if (!resource_valid(m_resource_ID))
	{
		video::rendering::create_vshader l_create_vshader;
		l_create_vshader.ID = m_resource_ID;
		l_create_vshader.data = get_info().data;
		l_create_vshader.size = get_info().size;
		add_command(l_create_vshader);
	}

	return true;
}

// memreader::info

memreader::info::info()
:
	video::object::info(video::ot::memreader)
{}

// memreader

memreader::memreader(const info &_info, video &_video)
:
	video::object(_info, _video)
{
}
memreader::~memreader()
{
}
bool memreader::update(real _dt)
{
	return true;
}
void memreader::clear()
{
	m_data.resize(0);
}
void memreader::write(pointer _data, uint _size)
{
	byte* l_data = (byte*)_data;
	m_data.insert(m_data.end(), l_data, l_data + _size);
	update_version();
}

// vbuffer::info

vbuffer::info::info()
:
	video::object::info(video::ot::vbuffer)
{}

// vbuffer

vbuffer::vbuffer(const info &_info, video &_video)
:
	video::object(_info, _video),
	m_source_ID(bad_ID), m_size(0)
{
	m_resource_ID = obtain_resource_ID();
	update_version();
}
vbuffer::~vbuffer()
{
	release_resource_ID(m_resource_ID);
}
bool vbuffer::update(real _dt)
{
	if (has_relation(m_source_ID))
	{
		uint l_source_ID = get_relation(m_source_ID);
		if (get_video().exists(l_source_ID))
		{
			object &l_object = get_video().get_<object>(l_source_ID);
			if (l_object.valid()) if (!valid() || version() < l_object.version())
			{
				switch (l_object.type())
				{
					case video::ot::memreader :
					{
						memreader &l_reader = get_video().get_<memreader>(l_source_ID);

						if (m_size < l_reader.size())
						{
							video::rendering::create_vbuffer l_create_vbuffer;
							l_create_vbuffer.ID = m_resource_ID;
							l_create_vbuffer.size = l_reader.size();
							add_command(l_create_vbuffer);

							m_size = l_reader.size();
						}

						if (m_size > 0)
						{
							add_data(l_reader.data(), l_reader.size());

							video::rendering::write_vbuffer l_write_vbuffer;
							l_write_vbuffer.ID = m_resource_ID;
							l_write_vbuffer.extra = l_reader.size();
							l_write_vbuffer.reset = true;
							add_command(l_write_vbuffer);
						}

						break;
					}
				}

				update_version();
			}
		}
	}

	return true;
}
void vbuffer::set_source(uint _ID)
{
	if (has_relation(m_source_ID)) remove_relation(m_source_ID);

	if (get_video().exists(_ID)) m_source_ID = add_relation(_ID);
	else m_source_ID = bad_ID;

	set_invalid();
}

// vformat::info

vformat::info::info()
:
	video::object::info(video::ot::vformat),
	data(0)
{}

// vformat

vformat::vformat(const info &_info, video &_video)
:
	video::object(_info, _video)
{
	m_resource_ID = obtain_resource_ID();
}
vformat::~vformat()
{
	release_resource_ID(m_resource_ID);
}
bool vformat::update(real _dt)
{
	if (!resource_valid(m_resource_ID))
	{
		video::rendering::create_vformat l_create_vformat;
		l_create_vformat.ID = m_resource_ID;
		l_create_vformat.data = get_info().data;
		add_command(l_create_vformat);
	}

	return true;
}

// drawcall::info

drawcall::info::info()
:
	video::object::info(video::ot::drawcall)
{}

// drawcall

drawcall::drawcall(const info &_info, video &_video)
:
	video::object(_info, _video),
	m_start(0), m_size(0), m_vbufset_ID(bad_ID), m_vshader_ID(bad_ID), m_pshader_ID(bad_ID), m_states_ID(bad_ID), m_consts_ID(bad_ID), m_texset_ID(bad_ID)
{}
drawcall::~drawcall()
{
	if (has_relation(m_consts_ID)) get_video().kill(get_relation(m_consts_ID));
}
bool drawcall::update(real _dt)
{
	return true;
}
void drawcall::set_vbufset(uint _ID)
{
	if (has_relation(m_vbufset_ID)) remove_relation(m_vbufset_ID);

	if (get_video().exists(_ID)) m_vbufset_ID = add_relation(_ID);
	else m_vbufset_ID = bad_ID;
}
void drawcall::add_commands(const context &_context) const
{
	u64 l_key = 0;
	set_key_field(l_key, command_type, ct::draw);
	set_key_field(l_key, command_draw_target, _context.target_ID); // @@@
	set_key_field(l_key, command_draw_viewport, _context.viewport_ID);
	set_key_field(l_key, command_draw_sequence, _context.sequence);
	video::rendering::draw_primitive l_draw_primitive;
	l_draw_primitive.target_ID = _context.target_ID;
	l_draw_primitive.viewport_ID = _context.viewport_ID;
	if (has_relation(m_vbufset_ID))
	{
		uint l_vbufset_ID = get_relation(m_vbufset_ID);
		if (get_video().exists(l_vbufset_ID) && get_video().get(l_vbufset_ID).type() == video::ot::vbufset)
		{
			vbufset &l_vbufset = get_video().get_<vbufset>(l_vbufset_ID);
			l_draw_primitive.vbufset_ID = l_vbufset.resource_ID();
		}
	}
	if (has_relation(m_vshader_ID))
	{
		uint l_vshader_ID = get_relation(m_vshader_ID);
		if (get_video().exists(l_vshader_ID) && get_video().get(l_vshader_ID).type() == video::ot::vshader)
		{
			vshader &l_vshader = get_video().get_<vshader>(l_vshader_ID);
			l_draw_primitive.vshader_ID = l_vshader.resource_ID();
		}
	}
	if (has_relation(m_pshader_ID))
	{
		uint l_pshader_ID = get_relation(m_pshader_ID);
		if (get_video().exists(l_pshader_ID) && get_video().get(l_pshader_ID).type() == video::ot::pshader)
		{
			pshader &l_pshader = get_video().get_<pshader>(l_pshader_ID);
			l_draw_primitive.pshader_ID = l_pshader.resource_ID();
		}
	}
	if (has_relation(m_states_ID))
	{
		uint l_states_ID = get_relation(m_states_ID);
		if (get_video().exists(l_states_ID) && get_video().get(l_states_ID).type() == video::ot::states)
		{
			states &l_states = get_video().get_<states>(l_states_ID);
			l_draw_primitive.states_ID = l_states.resource_ID();
		}
	}
	if (has_relation(m_consts_ID))
	{
		uint l_consts_ID = get_relation(m_consts_ID);
		if (get_video().exists(l_consts_ID) && get_video().get(l_consts_ID).type() == video::ot::consts)
		{
			consts &l_consts = get_video().get_<consts>(l_consts_ID);
			l_draw_primitive.consts_ID = l_consts.resource_ID();
		}
	}
	if (has_relation(m_texset_ID))
	{
		uint l_texset_ID = get_relation(m_texset_ID);
		if (get_video().exists(l_texset_ID) && get_video().get(l_texset_ID).type() == video::ot::texset)
		{
			texset &l_texset = get_video().get_<texset>(l_texset_ID);
			l_draw_primitive.texset_ID = l_texset.resource_ID();
		}
	}
	l_draw_primitive.type = D3DPT_TRIANGLESTRIP;
	l_draw_primitive.start = m_start;
	l_draw_primitive.size = m_size;
	add_command(l_key, l_draw_primitive);
}
void drawcall::set_shaders(uint _vshader_ID, uint _pshader_ID)
{
	if (has_relation(m_vshader_ID)) remove_relation(m_vshader_ID);

	if (has_relation(m_pshader_ID)) remove_relation(m_pshader_ID);

	if (get_video().exists(_vshader_ID)) m_vshader_ID = add_relation(_vshader_ID);
	else m_vshader_ID = bad_ID;

	if (get_video().exists(_pshader_ID)) m_pshader_ID = add_relation(_pshader_ID);
	else m_pshader_ID = bad_ID;
}
void drawcall::set_states(uint _ID)
{
	if (has_relation(m_states_ID)) remove_relation(m_states_ID);

	if (get_video().exists(_ID)) m_states_ID = add_relation(_ID);
	else m_states_ID = bad_ID;
}
void drawcall::write_consts(uint _type, uint _offset, pointer _data, uint _size)
{
	if (!has_relation(m_consts_ID))
	{
		m_consts_ID = add_relation(get_video().spawn(m_consts));
	}

	uint l_consts_ID = get_relation(m_consts_ID);

	consts &l_consts = get_video().get_<consts>(l_consts_ID);
	l_consts.write(_type, _offset, _data, _size);
}
void drawcall::set_texset(uint _ID)
{
	if (has_relation(m_texset_ID)) remove_relation(m_texset_ID);

	if (get_video().exists(_ID)) m_texset_ID = add_relation(_ID);
	else m_texset_ID = bad_ID;
}

// viewport::info

viewport::info::info()
:
	video::object::info(video::ot::viewport)
{}

// viewport

viewport::viewport(const info &_info, video &_video)
:
	video::object(_info, _video),
	m_area(0, 0, uint(-1) >> 1, uint(-1) >> 1), m_depth(real2_y)
{
	m_clear.f = 0;
	m_resource_ID = obtain_resource_ID();
	update_version();
}
viewport::~viewport()
{
	clear();

	release_resource_ID(m_resource_ID);
}
bool viewport::update(real _dt)
{
	return true;
}
void viewport::add_commands(const context &_context) const
{
	context l_context = _context;
	l_context.viewport.area &= m_area;
	l_context.viewport.depth = m_depth;
	l_context.viewport_ID = m_resource_ID;
	l_context.sequence++;

	video::rendering::create_viewport l_create_viewport;
	l_create_viewport.ID = m_resource_ID;
	l_create_viewport.area = l_context.viewport.area;
	l_create_viewport.depth = l_context.viewport.depth;
	add_command(l_create_viewport);

	u64 l_key = 0;
	set_key_field(l_key, command_type, ct::draw);
	set_key_field(l_key, command_draw_target, l_context.target_ID); // @@@
	set_key_field(l_key, command_draw_viewport, l_context.viewport_ID);
	set_key_field(l_key, command_draw_sequence, l_context.sequence);
	video::rendering::clear_viewport l_clear_viewport;
	l_clear_viewport.target_ID = l_context.target_ID;
	l_clear_viewport.viewport_ID = l_context.viewport_ID;
	l_clear_viewport.clear.f = m_clear.f;
	l_clear_viewport.clear.c = m_clear.c;
	add_command(l_key, l_clear_viewport);

	l_context.sequence++;

	for (uint i = 0, s = drawcall_count(); i < s; ++i)
	{
		get_video().get_<drawcall>(drawcall_ID(i)).add_commands(l_context);
	}
}
drawcall& viewport::add_drawcall()
{
	uint l_drawcall_ID = get_video().spawn(m_drawcall);
	m_drawcalls.push_back(add_relation(l_drawcall_ID));
	return get_video().get_<drawcall>(l_drawcall_ID);
}
void viewport::remove_drawcall(uint _i)
{
	assert(_i < m_drawcalls.size());
	uint l_drawcall_ID = get_relation(m_drawcalls[_i]);
	remove_relation(m_drawcalls[_i]);
	get_video().kill(l_drawcall_ID);
	m_drawcalls.erase(m_drawcalls.begin() + _i);
}
uint viewport::drawcall_count() const
{
	return m_drawcalls.size();
}
uint viewport::drawcall_ID(uint _i) const
{
	assert(_i < m_drawcalls.size());
	return get_relation(m_drawcalls[_i]);
}
void viewport::clear()
{
	while (drawcall_count())
	{
		remove_drawcall(drawcall_count() - 1);
	}
}

// window::info

window::info::info()
:
	video::object::info(video::ot::window)
{}

// window

window *window::first_p = 0;

window::window(const info &_info, video &_video, HWND _window)
:
	video::object(_info, _video),
	m_window(_window), next_p(0),
	m_flags(0)
{
	next_p = first_p;
	first_p = this;

	m_oldwndproc = (WNDPROC)SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)_wndproc);

	m_resource_ID = obtain_resource_ID();

	add_viewport();
}
window::~window()
{
	clear();

	video::rendering::destroy_resource l_destroy_resource;
	l_destroy_resource.ID = m_resource_ID;
	add_command(l_destroy_resource);

	release_resource_ID(m_resource_ID);

	window **l_window_pp = &first_p;
	while (*l_window_pp)
	{
		if (*l_window_pp == this)
		{
			*l_window_pp = next_p;
			break;
		}
		l_window_pp = &((*l_window_pp)->next_p);
	}

	if (m_window != 0 && GetWindowLongPtrW(m_window, GWL_WNDPROC) == (LONG_PTR)_wndproc)
		SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)m_oldwndproc);
}
bool window::reset(HWND _window)
{
	// We should do this only if prev window is already destroed !!!
	assert(m_window == 0);

	//if (m_window != 0 && GetWindowLongPtrW(m_window, GWL_WNDPROC) == (LONG_PTR)_wndproc)
	//	SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)m_oldwndproc);

	m_window = _window;
	m_oldwndproc = (WNDPROC)SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)_wndproc);
	set_invalid();
	return true;
}
bool window::update(real _dt)
{
	if (m_window == 0) return true;

	if (!valid() || !resource_valid(m_resource_ID))
	{
		video::rendering::create_schain l_create_schain;
		l_create_schain.ID = m_resource_ID;
		l_create_schain.window = m_window;
		add_command(l_create_schain);
	}

	if (!(m_flags & force_redraw))
	{
		for (uint i = 0, s = viewport_count(); i < s; ++i)
		{
			if (version() < get_video().get_<viewport>(viewport_ID(i)).version())
			{
				m_flags |= force_redraw;
				break;
			}
		}
	}

	if (m_flags & force_redraw)
	{
		m_flags &= ~force_redraw;

		context l_context;
		l_context.target_ID = m_resource_ID;
		RECT l_crect; GetClientRect(m_window, &l_crect);
		l_context.viewport.area = rect(0, 0, (uint)l_crect.right, (uint)l_crect.bottom);
		l_context.viewport.depth = real2_y;
		l_context.sequence = 0;

		for (uint i = 0, s = viewport_count(); i < s; ++i)
		{
			get_video().get_<viewport>(viewport_ID(i)).add_commands(l_context);
		}

		u64 l_key = 0;
		set_key_field(l_key, command_type, ct::present);
		video::rendering::present_schain l_present_schain;
		l_present_schain.ID = m_resource_ID;
		add_command(l_key, l_present_schain);

		update_version();
	}

	return true;
}
LRESULT _stdcall window::_wndproc(HWND _window, uint _message, uint _wparam, uint _lparam)
{
	window *l_window_p = window::first_p;
	while (l_window_p)
	{
		window &l_window = *l_window_p;
		if (l_window.m_window == _window)
		{
			return l_window.m_wndproc(_message, _wparam, _lparam);
		}
		l_window_p = l_window.next_p;
	}

	return 1;
}
LRESULT window::m_wndproc(uint _message, uint _wparam, uint _lparam)
{
	switch (_message)
	{
		case WM_ERASEBKGND :
		{
			m_flags |= erase_background;
			return 1;
		}
		case WM_SIZE :
		{
			set_invalid();
			break;
		}
		case WM_PAINT :
		{
			if (m_flags & erase_background)
			{
				HRGN l_rgn = CreateRectRgn(0, 0, 0, 0);
				if (GetUpdateRgn(m_window, l_rgn, TRUE) != ERROR)
				{
					RECT l_rect; GetClientRect(m_window, &l_rect);
					HRGN l_rgn2 = CreateRectRgn(l_rect.left, l_rect.top, l_rect.right, l_rect.bottom);
					if (EqualRgn(l_rgn, l_rgn2) == FALSE || !valid())
					{
						HDC l_hdc = GetDC(m_window);
						FillRgn(l_hdc, l_rgn, (HBRUSH)GetStockObject(BLACK_BRUSH));
						ReleaseDC(m_window, l_hdc);
					}
					DeleteObject(l_rgn2);
				}
				DeleteObject(l_rgn);

				m_flags &= ~erase_background;
			}
			m_flags |= force_redraw;
			break;
		}
		case WM_DESTROY :
		{
			LRESULT l_result = CallWindowProc(m_oldwndproc, m_window, (UINT)_message, _wparam, _lparam);
			SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)m_oldwndproc);
			m_window = 0;
			return l_result;
			break;
		}
	}

	return CallWindowProc(m_oldwndproc, m_window, (UINT)_message, _wparam, _lparam);
}
uint window::add_viewport()
{
	uint l_viewport_ID = get_video().spawn(m_viewport_info);
	m_viewports.push_back(add_relation(l_viewport_ID));
	return m_viewports.size() - 1;
}
void window::remove_viewport(uint _i)
{
	assert(_i < m_viewports.size());
	uint l_viewport_ID = get_relation(m_viewports[_i]);
	remove_relation(m_viewports[_i]);
	get_video().kill(l_viewport_ID);
	m_viewports.erase(m_viewports.begin() + _i);
}
uint window::viewport_count() const
{
	return m_viewports.size();
}
uint window::viewport_ID(uint _i) const
{
	assert(_i < m_viewports.size());
	return get_relation(m_viewports[_i]);
}
void window::clear()
{
	for (uint i = 0, s = viewport_count(); i < s; ++i)
	{
		remove_viewport(i);
	}
}

} /* video resources ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
