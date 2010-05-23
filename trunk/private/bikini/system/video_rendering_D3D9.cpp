/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

#pragma comment(lib, "d3d9")

namespace bk { /*--------------------------------------------------------------------------------*/

// _video_rendering_helper

struct _video_rendering_helper
{
	static HWND create_dummy_window()
	{
		HINSTANCE l_instance = GetModuleHandle(0);
		wchar_t* l_window_class_name = L"bikini-iii video dummy window";
		WNDCLASSW l_window_class = { 0, DefWindowProcW, 0, 0, l_instance, 0, 0, 0, 0, l_window_class_name };
		RegisterClassW(&l_window_class);
		HWND l_handle = CreateWindowExW(0, l_window_class_name, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 10, 10, 0, 0, l_instance, 0);
		if(l_handle == 0) std::cerr << "ERROR: Can't create dummy window\n";
		return l_handle;
	}
};

// rendering_D3D9

struct rendering_D3D9 : video::rendering
{
	rendering_D3D9(video &_video);
	~rendering_D3D9();
	bool initialize();
	void finalize();
	bool execute(const command &_command);

private:
	static IDirect3D9 *sm_D3D9_p;
	IDirect3DDevice9 *m_D3DDevice9_p;
	D3DPRESENT_PARAMETERS m_D3DPP;

	bool execute(const create_schain &_command);
	bool execute(const create_viewport &_command);
	bool execute(const create_vformat &_command);
	bool execute(const create_vbuffer &_command);
	bool execute(const write_vbuffer &_command);
	bool execute(const create_vshader &_command);
	bool execute(const create_pshader &_command);
	bool execute(const create_vbufset &_command);
	bool execute(const create_states &_command);
	bool execute(const create_consts &_command);
	bool execute(const write_consts &_command);
	bool execute(const create_texture &_command);
	bool execute(const write_texture &_command);
	bool execute(const create_texset &_command);
	bool execute(const destroy_resource &_command);
	bool execute(const begin_scene &_command);
	bool execute(const clear_viewport &_command);
	bool execute(const draw_primitive &_command);
	bool execute(const end_scene &_command);
	bool execute(const present_schain &_command);

	struct _resource { uint ID; };

	struct schain : _resource { IDirect3DSwapChain9 *D3DSChain9_p; };
	struct viewport : _resource { D3DVIEWPORT9 D3DViewport9; };
	struct vformat : _resource { IDirect3DVertexDeclaration9 *D3DVDecl9_p; };
	struct vbuffer : _resource { IDirect3DVertexBuffer9 *D3DVBuffer9_p; uint size, used; };
	struct vshader : _resource { IDirect3DVertexShader9 *D3DVShader9_p; };
	struct pshader : _resource { IDirect3DPixelShader9 *D3DPShader9_p; };
	struct vbufset : _resource { uint vformat_ID, vbuffer_IDs[8], offsets[8], strides[8]; };
	struct states : _resource { IDirect3DStateBlock9 *D3DSBlock9_p; };
	struct consts : _resource { byte_array data; };
	struct texture : _resource { IDirect3DTexture9 *D3DTexture9_p; };
	struct texset : _resource { uint texture_IDs[8]; };
	struct ibuffer : _resource {};
	struct rtarget : _resource {};
	struct material : _resource {};
	struct primitive : _resource {};

	typedef make_typelist_<
		schain, viewport, vformat, vbuffer, vshader, pshader, vbufset, states, consts, texture, texset
	>::type resource_types;

	typedef variant_<resource_types, false> resource;
	typedef array_<resource> resources;

	resources m_resources;

	void m_create_resource(const resource &_r);
	void m_destroy_resource(uint _ID);
	bool m_set_target(uint _ID);
	bool m_set_viewport(uint _ID);
	bool m_set_vformat(uint _ID);
	bool m_set_vbuffer(uint _i, uint _ID, uint _offset, uint _stride);
	bool m_set_vbuffers(uint _ID);
	bool m_set_vshader(uint _ID);
	bool m_set_pshader(uint _ID);
	bool m_set_states(uint _ID);
	bool m_set_consts(uint _ID);
	bool m_set_texture(uint _i, uint _ID);
	bool m_set_textures(uint _ID);
};

IDirect3D9 *rendering_D3D9::sm_D3D9_p = 0;

rendering_D3D9::rendering_D3D9(video &_video)
:
	video::rendering(_video),
	m_D3DDevice9_p(0)
{}
rendering_D3D9::~rendering_D3D9()
{
}
bool rendering_D3D9::initialize()
{
	if (sm_D3D9_p == 0)
	{
		if((sm_D3D9_p = Direct3DCreate9(D3D_SDK_VERSION)) == 0)
		{
			std::cerr << "ERROR: Can't create Direct3D object.\n";
			return false;
		}
	}
	else
	{
		sm_D3D9_p->AddRef();
	}

	memset(&m_D3DPP, 0, sizeof(m_D3DPP));
	m_D3DPP.hDeviceWindow = _video_rendering_helper::create_dummy_window();
	m_D3DPP.Windowed = true;
	m_D3DPP.BackBufferCount = 1;
	m_D3DPP.BackBufferWidth = 10;
	m_D3DPP.BackBufferHeight = 10;
	m_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_D3DPP.FullScreen_RefreshRateInHz = 0;
    m_D3DPP.EnableAutoDepthStencil = false;
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	DWORD l_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE|D3DCREATE_PUREDEVICE/*|D3DCREATE_MULTITHREADED*/;
	if(FAILED(sm_D3D9_p->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_D3DPP.hDeviceWindow,
		l_flags,
		&m_D3DPP,
		&m_D3DDevice9_p
	)))
	{
		std::cerr << "ERROR: Can't create D3D device\n";
		if (sm_D3D9_p->Release() == 0) sm_D3D9_p = 0;
		return false;
	}

	//m_D3DDevice9_p->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	
	return true;
}
void rendering_D3D9::finalize()
{
	while (!m_resources.empty())
	{
		resource &l_resource = m_resources.back();
		if (!l_resource.is_nothing())
		{
			m_destroy_resource(l_resource.get_<_resource>().ID);
		}
		m_resources.pop_back();
	}

	while (m_D3DDevice9_p->Release() != 0); m_D3DDevice9_p = 0;
	if (sm_D3D9_p->Release() == 0) sm_D3D9_p = 0;
}
void rendering_D3D9::m_create_resource(const resource &_r)
{
	if (!_r.is_nothing())
	{
		uint_ID l_ID(_r.get_<_resource>().ID);

		m_destroy_resource(l_ID);

		if (l_ID.index >= m_resources.size()) m_resources.resize(l_ID.index + 1);

		m_resources[l_ID.index] = _r;

		set_valid(l_ID);
	}
}
void rendering_D3D9::m_destroy_resource(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<schain>::index :
				{
					schain &l_schain = l_resource.get_<schain>();
					l_schain.D3DSChain9_p->Release();
					break;
				}
				case resource_types::type_<viewport>::index :
				{
					break;
				}
				case resource_types::type_<vformat>::index :
				{
					vformat &l_vformat = l_resource.get_<vformat>();
					l_vformat.D3DVDecl9_p->Release();
					break;
				}
				case resource_types::type_<vbuffer>::index :
				{
					vbuffer &l_vbuffer = l_resource.get_<vbuffer>();
					l_vbuffer.D3DVBuffer9_p->Release();
					break;
				}
				case resource_types::type_<vshader>::index :
				{
					vshader &l_vshader = l_resource.get_<vshader>();
					l_vshader.D3DVShader9_p->Release();
					break;
				}
				case resource_types::type_<pshader>::index :
				{
					pshader &l_pshader = l_resource.get_<pshader>();
					l_pshader.D3DPShader9_p->Release();
					break;
				}
				case resource_types::type_<vbufset>::index :
				{
					break;
				}
				case resource_types::type_<states>::index :
				{
					states &l_states = l_resource.get_<states>();
					l_states.D3DSBlock9_p->Release();
					break;
				}
				case resource_types::type_<consts>::index :
				{
					break;
				}
				case resource_types::type_<texture>::index :
				{
					texture &l_texture = l_resource.get_<texture>();
					l_texture.D3DTexture9_p->Release();
					break;
				}
			}
			l_resource.destruct();
			set_invalid(_ID);
		}
	}
}
bool rendering_D3D9::m_set_target(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<schain>::index :
				{
					schain &l_schain = l_resource.get_<schain>();
					IDirect3DSurface9 *l_D3DSurface9_p;
					if (FAILED(l_schain.D3DSChain9_p->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &l_D3DSurface9_p))) return false;
					m_D3DDevice9_p->SetRenderTarget(0, l_D3DSurface9_p);
					l_D3DSurface9_p->Release();
					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D9::m_set_viewport(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<viewport>::index :
				{
					viewport &l_viewport = l_resource.get_<viewport>();
					if (FAILED(m_D3DDevice9_p->SetViewport(&l_viewport.D3DViewport9))) return false;
					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D9::m_set_vformat(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<vformat>::index :
				{
					vformat &l_vformat = l_resource.get_<vformat>();
					if (FAILED(m_D3DDevice9_p->SetVertexDeclaration(l_vformat.D3DVDecl9_p))) return false;
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::m_set_vbuffer(uint _i, uint _ID, uint _offset, uint _stride)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<vbuffer>::index :
				{
					vbuffer &l_vbuffer = l_resource.get_<vbuffer>();
					if (FAILED(m_D3DDevice9_p->SetStreamSource((UINT)_i, l_vbuffer.D3DVBuffer9_p, (UINT)_offset, (UINT)_stride))) return false;
					break;
				}
			}
			return true;
		}

		m_D3DDevice9_p->SetStreamSource((UINT)_i, 0, 0, 0);
	}
	return true;
}
bool rendering_D3D9::m_set_vbuffers(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<vbufset>::index :
				{
					vbufset &l_vbufset = l_resource.get_<vbufset>();
					m_set_vformat(l_vbufset.vformat_ID);
					for (uint i = 0; i < 8; ++i)
					{
						m_set_vbuffer(i, l_vbufset.vbuffer_IDs[i], l_vbufset.offsets[i], l_vbufset.strides[i]);
					}
					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D9::m_set_vshader(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<vshader>::index :
				{
					vshader &l_vshader = l_resource.get_<vshader>();
					if (FAILED(m_D3DDevice9_p->SetVertexShader(l_vshader.D3DVShader9_p))) return false;
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::m_set_pshader(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<pshader>::index :
				{
					pshader &l_pshader = l_resource.get_<pshader>();
					if (FAILED(m_D3DDevice9_p->SetPixelShader(l_pshader.D3DPShader9_p))) return false;
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::m_set_states(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<states>::index :
				{
					states &l_states = l_resource.get_<states>();
					if (FAILED(l_states.D3DSBlock9_p->Apply())) return false;
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::m_set_consts(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<consts>::index :
				{
					consts &l_consts = l_resource.get_<consts>();

					if (!l_consts.data.empty())
					{
						byte* l_begin = &l_consts.data[0];
						sint l_length = l_consts.data.size();

						byte* l_current = &l_consts.data[0];

						while (l_current - l_begin < l_length)
						{
							uint l_type = *(uint*)l_current; l_current += sizeof(uint);
							uint l_offset = *(uint*)l_current; l_current += sizeof(uint);
							uint l_size = *(uint*)l_current; l_current += sizeof(uint);

							if (l_type & 1)
							{
								m_D3DDevice9_p->SetVertexShaderConstantF((UINT)l_offset, (const float*)l_current, (UINT)(l_size / 16));
							}
							if (l_type & 2)
							{
								m_D3DDevice9_p->SetPixelShaderConstantF((UINT)l_offset, (const float*)l_current, (UINT)(l_size / 16));
							}

							l_current += l_size;
						}
					}

					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::m_set_texture(uint _i, uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<texture>::index :
				{
					texture &l_texture = l_resource.get_<texture>();
					if (FAILED(m_D3DDevice9_p->SetTexture((UINT)_i, l_texture.D3DTexture9_p))) return false;
					break;
				}
			}
			return true;
		}

		m_D3DDevice9_p->SetTexture((UINT)_i, 0);
	}
	return true;
}
bool rendering_D3D9::m_set_textures(uint _ID)
{
	uint_ID l_ID(_ID);
	if (l_ID.index < m_resources.size())
	{
		resource &l_resource = m_resources[l_ID.index];
		if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _ID)
		{
			switch (l_resource.type())
			{
				case resource_types::type_<texset>::index :
				{
					texset &l_texset = l_resource.get_<texset>();
					for (uint i = 0; i < 8; ++i)
					{
						m_set_texture(i, l_texset.texture_IDs[i]);
					}
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D9::execute(const command &_command)
{
	switch (_command.type())
	{
		case command_types::type_<create_schain>::index : return execute(_command.get_<create_schain>());
		case command_types::type_<create_viewport>::index : return execute(_command.get_<create_viewport>());
		case command_types::type_<create_vformat>::index : return execute(_command.get_<create_vformat>());
		case command_types::type_<create_vbuffer>::index : return execute(_command.get_<create_vbuffer>());
		case command_types::type_<write_vbuffer>::index : return execute(_command.get_<write_vbuffer>());
		case command_types::type_<create_vshader>::index : return execute(_command.get_<create_vshader>());
		case command_types::type_<create_pshader>::index : return execute(_command.get_<create_pshader>());
		case command_types::type_<create_vbufset>::index : return execute(_command.get_<create_vbufset>());
		case command_types::type_<create_states>::index : return execute(_command.get_<create_states>());
		case command_types::type_<create_consts>::index : return execute(_command.get_<create_consts>());
		case command_types::type_<write_consts>::index : return execute(_command.get_<write_consts>());
		case command_types::type_<create_texture>::index : return execute(_command.get_<create_texture>());
		case command_types::type_<write_texture>::index : return execute(_command.get_<write_texture>());
		case command_types::type_<create_texset>::index : return execute(_command.get_<create_texset>());
		case command_types::type_<destroy_resource>::index : return execute(_command.get_<destroy_resource>());
		case command_types::type_<begin_scene>::index : return execute(_command.get_<begin_scene>());
		case command_types::type_<clear_viewport>::index : return execute(_command.get_<clear_viewport>());
		case command_types::type_<draw_primitive>::index : return execute(_command.get_<draw_primitive>());
		case command_types::type_<end_scene>::index : return execute(_command.get_<end_scene>());
		case command_types::type_<present_schain>::index : return execute(_command.get_<present_schain>());
	}
	return false;
}
bool rendering_D3D9::execute(const create_schain &_command)
{
	schain l_schain;
	l_schain.ID = _command.ID;

	D3DPRESENT_PARAMETERS l_D3DPP = {0};
	l_D3DPP.hDeviceWindow = (HWND)_command.window;
	l_D3DPP.Windowed = TRUE;
	l_D3DPP.BackBufferCount = 1;
	l_D3DPP.BackBufferWidth = 0;
	l_D3DPP.BackBufferHeight = 0;
	l_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	l_D3DPP.FullScreen_RefreshRateInHz = 0;
	l_D3DPP.MultiSampleType = (D3DMULTISAMPLE_TYPE)4;
	l_D3DPP.MultiSampleQuality = 0;
	l_D3DPP.EnableAutoDepthStencil = FALSE;
	l_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	l_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_D3DDevice9_p->CreateAdditionalSwapChain(&l_D3DPP, &l_schain.D3DSChain9_p))) return false;

	m_create_resource(l_schain);

	return true;
}
bool rendering_D3D9::execute(const create_viewport &_command)
{
	viewport l_viewport;
	l_viewport.ID = _command.ID;

	D3DVIEWPORT9 l_D3DViewport9 =
	{
		(DWORD)_command.area.min().x, (DWORD)_command.area.min().y,
		(DWORD)_command.area.size().x, (DWORD)_command.area.size().y,
		(float)_command.depth.x, (float)_command.depth.y
	};
	l_viewport.D3DViewport9 = l_D3DViewport9;

	m_create_resource(l_viewport);

	return true;
}
static D3DDECLTYPE get_DX9_element_type(video::vf::element_type _type)
{
	switch (_type)
	{
		case video::vf::short2 : return D3DDECLTYPE_SHORT2;
	}

	return D3DDECLTYPE_UNUSED;
}
static D3DDECLUSAGE get_DX9_element_usage(const achar* _semantic)
{
	if (strcmp(_semantic, "POSITION") == 0) return D3DDECLUSAGE_POSITION;
	if (strcmp(_semantic, "NORMAL") == 0) return D3DDECLUSAGE_NORMAL;

	return (D3DDECLUSAGE)-1;
}
bool rendering_D3D9::execute(const create_vformat &_command)
{
	vformat l_vformat;
	l_vformat.ID = _command.ID;

	uint l_element_count = 0;
	D3DVERTEXELEMENT9 l_DX9_elements[64];
	video::vf::element* l_elements = (video::vf::element*)_command.data;

	while (true)
	{
		video::vf::element &l_element = l_elements[l_element_count];
		if (l_element.semantic == 0) break;

		D3DVERTEXELEMENT9 &l_DX9_element = l_DX9_elements[l_element_count];
		l_DX9_element.Stream = l_element.slot;
		l_DX9_element.Offset = l_element.offset;
		l_DX9_element.Type = get_DX9_element_type(l_element.type);
		l_DX9_element.Method = D3DDECLMETHOD_DEFAULT;
		l_DX9_element.Usage = get_DX9_element_usage(l_element.semantic);
		l_DX9_element.UsageIndex = l_element.index;

		++l_element_count;
	}

	D3DVERTEXELEMENT9 l_end = D3DDECL_END();
	l_DX9_elements[l_element_count++] = l_end;

	if (FAILED(m_D3DDevice9_p->CreateVertexDeclaration(l_DX9_elements, &l_vformat.D3DVDecl9_p))) return false;

	m_create_resource(l_vformat);

	return true;
}
bool rendering_D3D9::execute(const create_vbuffer &_command)
{
	vbuffer l_vbuffer;
	l_vbuffer.ID = _command.ID;
	l_vbuffer.size = _command.size;
	l_vbuffer.used = 0;

	if (FAILED(m_D3DDevice9_p->CreateVertexBuffer((UINT)_command.size, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &l_vbuffer.D3DVBuffer9_p, 0))) return false;

	m_create_resource(l_vbuffer);

	return true;
}
bool rendering_D3D9::execute(const write_vbuffer &_command)
{
	uint_ID l_ID(_command.ID);

	resource &l_resource = m_resources[l_ID.index];
	if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _command.ID)
	{
		if (l_resource.type() == resource_types::type_<vbuffer>::index)
		{
			vbuffer &l_vbuffer = l_resource.get_<vbuffer>();

			if (_command.reset) l_vbuffer.used = 0;

			if (_command.extra <= l_vbuffer.size - l_vbuffer.used)
			{
				handle l_data;
				l_vbuffer.D3DVBuffer9_p->Lock((UINT)l_vbuffer.used, (UINT)_command.extra, &l_data, 0);

				get_data(l_data, _command.extra);

				l_vbuffer.D3DVBuffer9_p->Unlock();

				l_vbuffer.used += _command.extra;

				return true;
			}
		}
	}

	throw_data(_command.extra);

	return true;
}
bool rendering_D3D9::execute(const create_vshader &_command)
{
	vshader l_vshader;
	l_vshader.ID = _command.ID;

	if (FAILED(m_D3DDevice9_p->CreateVertexShader((CONST DWORD*)_command.data, &l_vshader.D3DVShader9_p))) return false;

	m_create_resource(l_vshader);

	return true;
}
bool rendering_D3D9::execute(const create_pshader &_command)
{
	pshader l_pshader;
	l_pshader.ID = _command.ID;

	if (FAILED(m_D3DDevice9_p->CreatePixelShader((CONST DWORD*)_command.data, &l_pshader.D3DPShader9_p))) return false;

	m_create_resource(l_pshader);

	return true;
}
bool rendering_D3D9::execute(const create_vbufset &_command)
{
	vbufset l_vbufset;
	l_vbufset.ID = _command.ID;

	l_vbufset.vformat_ID = _command.vformat_ID;
	memcpy(l_vbufset.vbuffer_IDs, _command.vbuffer_IDs, sizeof(l_vbufset.vbuffer_IDs));
	memcpy(l_vbufset.offsets, _command.offsets, sizeof(l_vbufset.offsets));
	memcpy(l_vbufset.strides, _command.strides, sizeof(l_vbufset.strides));

	m_create_resource(l_vbufset);

	return true;
}
bool rendering_D3D9::execute(const create_states &_command)
{
	states l_states;
	l_states.ID = _command.ID;

	if (FAILED(m_D3DDevice9_p->BeginStateBlock())) return false;

	DWORD* l_data = (DWORD*)_command.data;
	while (*l_data != DWORD(-1))
	{
		D3DRENDERSTATETYPE l_state = (D3DRENDERSTATETYPE)*l_data;
		DWORD l_value = *(l_data + 1);

		m_D3DDevice9_p->SetRenderState(l_state, l_value);

		l_data += 2;
	}

	if (FAILED(m_D3DDevice9_p->EndStateBlock(&l_states.D3DSBlock9_p))) return false;

	m_create_resource(l_states);

	return true;
}
bool rendering_D3D9::execute(const create_consts &_command)
{
	consts l_consts;
	l_consts.ID = _command.ID;

	m_create_resource(l_consts);

	return true;
}
bool rendering_D3D9::execute(const write_consts &_command)
{
	uint_ID l_ID(_command.ID);

	resource &l_resource = m_resources[l_ID.index];
	if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _command.ID)
	{
		if (l_resource.type() == resource_types::type_<consts>::index)
		{
			consts &l_consts = l_resource.get_<consts>();

			if (_command.reset) l_consts.data.resize(0);

			uint l_oldsize = l_consts.data.size();
			l_consts.data.resize(l_oldsize + _command.extra);

			get_data(&l_consts.data[l_oldsize], _command.extra);

			return true;
		}
	}

	throw_data(_command.extra);

	return true;
}
bool rendering_D3D9::execute(const create_texture &_command)
{
	texture l_texture;
	l_texture.ID = _command.ID;

	D3DFORMAT l_format;
	switch (_command.format)
	{
		case video::tf::a8 : l_format = D3DFMT_A8; break;
		case video::tf::b8g8r8 : l_format = D3DFMT_A8R8G8B8; break;
		case video::tf::a8b8g8r8 : l_format = D3DFMT_A8R8G8B8; break;
		case video::tf::a8r8g8b8 : l_format = D3DFMT_A8R8G8B8; break;
	}

	if (FAILED(m_D3DDevice9_p->CreateTexture((UINT)_command.size.x, (UINT)_command.size.y, 0, 0, l_format, D3DPOOL_DEFAULT, &l_texture.D3DTexture9_p, 0))) return false;

	m_create_resource(l_texture);

	return true;
}
bool rendering_D3D9::execute(const write_texture &_command)
{
	uint_ID l_ID(_command.ID);

	resource &l_resource = m_resources[l_ID.index];
	if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _command.ID)
	{
		if (l_resource.type() == resource_types::type_<texture>::index)
		{
			texture &l_texture = l_resource.get_<texture>();

			uint l_format; get_data(&l_format, sizeof(l_format));
			sint2 l_size; get_data(&l_size, sizeof(l_size));
			uint l_pitch; get_data(&l_pitch, sizeof(l_pitch));

			D3DFORMAT l_D3DFormat;
			switch (l_format)
			{
				case video::tf::a8 : l_D3DFormat = D3DFMT_A8; break;
				case video::tf::b8g8r8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
				case video::tf::a8b8g8r8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
				case video::tf::a8r8g8b8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
			}

			IDirect3DTexture9 *l_D3DTex9_p;
			if (FAILED(m_D3DDevice9_p->CreateTexture((UINT)l_size.x, (UINT)l_size.y, 1, 0, l_D3DFormat, D3DPOOL_SYSTEMMEM, &l_D3DTex9_p, 0)))
			{
				throw_data(l_size.y * l_pitch);
				return false;
			}

			D3DLOCKED_RECT l_rect;
			l_D3DTex9_p->LockRect(0, &l_rect, 0, 0);
			if (l_format == video::tf::b8g8r8 || l_format == video::tf::a8b8g8r8)
			{
				assert((uint)l_rect.Pitch >= l_pitch);
				uint l_width = l_size.x, l_height = l_size.y;

				for (uint y = 0; y < l_height; ++y)
				{
					byte* l_row = (byte*)l_rect.pBits + y * l_rect.Pitch;
					get_data(l_row, l_pitch);

					switch (l_format)
					{
						case video::tf::b8g8r8 :
						{
							for (uint x = 0; x < l_width; ++x)
							{
								uint l_pixel = l_width - 1 - x;

								uint l_pixel_3 = l_pixel * 3;
								byte l_r = l_row[l_pixel_3 + 2];
								byte l_g = l_row[l_pixel_3 + 1];
								byte l_b = l_row[l_pixel_3 + 0];
								byte l_a = 0xff;

								uint l_pixel_4 = l_pixel * 4;
								l_row[l_pixel_4 + 0] = l_r;
								l_row[l_pixel_4 + 1] = l_g;
								l_row[l_pixel_4 + 2] = l_b;
								l_row[l_pixel_4 + 3] = l_a;
							}
							break;
						}
						case video::tf::a8b8g8r8 :
						{
							for (uint x = 0; x < l_width; ++x)
							{
								uint l_pixel = (l_width - 1 - x) * 4;

								byte l_r = l_row[l_pixel + 2];
								byte l_g = l_row[l_pixel + 1];
								byte l_b = l_row[l_pixel + 0];
								byte l_a = l_row[l_pixel + 3];

								l_row[l_pixel + 0] = l_r;
								l_row[l_pixel + 1] = l_g;
								l_row[l_pixel + 2] = l_b;
								l_row[l_pixel + 3] = l_a;
							}
							break;
						}
					}
				}
			}
			else
			{
				get_data(l_rect.pBits, l_size.y * l_pitch);
			}
			l_D3DTex9_p->UnlockRect(0);

			l_texture.D3DTexture9_p->Release();

			DWORD l_usage = 0;
			if (l_size.x * l_size.y > 1) l_usage |= D3DUSAGE_AUTOGENMIPMAP;

			m_D3DDevice9_p->CreateTexture((UINT)l_size.x, (UINT)l_size.y, 0, l_usage, l_D3DFormat, D3DPOOL_DEFAULT, &l_texture.D3DTexture9_p, 0);

			if (l_usage & D3DUSAGE_AUTOGENMIPMAP) l_texture.D3DTexture9_p->SetAutoGenFilterType(D3DTEXF_ANISOTROPIC);
			
			IDirect3DSurface9 *l_D3DSrcSurf9_p; l_D3DTex9_p->GetSurfaceLevel(0, &l_D3DSrcSurf9_p);
			IDirect3DSurface9 *l_D3DDstSurf9_p; l_texture.D3DTexture9_p->GetSurfaceLevel(0, &l_D3DDstSurf9_p);
			m_D3DDevice9_p->UpdateSurface(l_D3DSrcSurf9_p, 0, l_D3DDstSurf9_p, 0);
			l_D3DDstSurf9_p->Release();
			l_D3DSrcSurf9_p->Release();

			l_D3DTex9_p->Release();

			return true;
		}
	}

	throw_data(_command.extra);

	return true;
}
bool rendering_D3D9::execute(const create_texset &_command)
{
	texset l_texset;
	l_texset.ID = _command.ID;

	memcpy(l_texset.texture_IDs, _command.texture_IDs, sizeof(l_texset.texture_IDs));

	m_create_resource(l_texset);

	return true;
}
bool rendering_D3D9::execute(const destroy_resource &_command)
{
	m_destroy_resource(_command.ID);

	return true;
}
bool rendering_D3D9::execute(const begin_scene &_command)
{
	if (FAILED(m_D3DDevice9_p->BeginScene())) return false;
	return true;
}
bool rendering_D3D9::execute(const clear_viewport &_command)
{
	if (!m_set_target(_command.target_ID)) return false;
	if (!m_set_viewport(_command.viewport_ID)) return false;

	DWORD l_flags = 0;
	if (_command.clear.f & cf::color) l_flags |= D3DCLEAR_TARGET;
	if (_command.clear.f & cf::depth) l_flags |= D3DCLEAR_ZBUFFER;
	if (_command.clear.f & cf::stencil) l_flags |= D3DCLEAR_STENCIL;

	if (l_flags != 0)
	{
		D3DCOLOR l_color = (D3DCOLOR)_command.clear.c;
		float l_z = (float)_command.clear.z;
		DWORD l_stencil = (DWORD)_command.clear.s;

		if (FAILED(m_D3DDevice9_p->Clear(0, 0, l_flags, l_color, l_z, l_stencil))) return false;
	}

	return true;
}
bool rendering_D3D9::execute(const draw_primitive &_command)
{
	if (!m_set_target(_command.target_ID)) return false;
	if (!m_set_viewport(_command.viewport_ID)) return false;
	if (!m_set_vbuffers(_command.vbufset_ID)) return false;
	if (!m_set_vshader(_command.vshader_ID)) return false;
	if (!m_set_pshader(_command.pshader_ID)) return false;
	if (!m_set_states(_command.states_ID)) return false;
	if (!m_set_consts(_command.consts_ID)) return false;
	if (!m_set_textures(_command.texset_ID)) return false;

	if (FAILED(m_D3DDevice9_p->DrawPrimitive((D3DPRIMITIVETYPE)_command.type, (UINT)_command.start, (UINT)_command.size))) return false;

	return true;
}
bool rendering_D3D9::execute(const end_scene &_command)
{
	if (FAILED(m_D3DDevice9_p->EndScene())) return false;
	return true;
}
bool rendering_D3D9::execute(const present_schain &_command)
{
	uint_ID l_command_ID(_command.ID);

	if (l_command_ID.index >= m_resources.size()) return false;

	resource &l_resource = m_resources[l_command_ID.index];

	if (l_resource.is_nothing() || l_resource.get_<_resource>().ID != _command.ID) return false;
	if (l_resource.type() != resource_types::type_<schain>::index) return false;

	schain l_schain = l_resource.get_<schain>();

	if (FAILED(l_schain.D3DSChain9_p->Present(0, 0, 0, 0, 0))) return false;

	return true;
}

video::rendering* new_rendering_D3D9(video &_video)
{
	return new rendering_D3D9(_video);
}

} /* namespace bk -------------------------------------------------------------------------------*/
