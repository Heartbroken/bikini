/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
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

	inline IDirect3DDevice9& get_device() { return *m_D3DDevice9_p; }

private:
	static IDirect3D9 *sm_D3D9_p;
	IDirect3DDevice9 *m_D3DDevice9_p;
	D3DPRESENT_PARAMETERS m_D3DPP;

	bool execute(const create_schain &_command);
	bool execute(const create_viewport &_command);
	bool execute(const create_vformat &_command);
	bool execute(const create_vbuffer &_command);
	bool execute(const destroy_resource &_command);
	bool execute(const begin_scene &_command);
	bool execute(const clear_viewport &_command);
	bool execute(const end_scene &_command);
	bool execute(const present_schain &_command);

	struct _resource { uint ID; };

	struct schain : _resource { IDirect3DSwapChain9 *D3DSChain9_p; };
	struct viewport : _resource { D3DVIEWPORT9 D3DViewport9; };
	struct vformat : _resource { IDirect3DVertexDeclaration9 *D3DVDecl9_p; };
	struct vbuffer : _resource { IDirect3DVertexBuffer9 *D3DVBuffer9_p; };
	struct ibuffer : _resource {};
	struct texture : _resource {};
	struct vshader : _resource {};
	struct pshader : _resource {};
	struct consts : _resource {};
	struct states : _resource {};
	struct rtarget : _resource {};
	struct material : _resource {};
	struct primitive : _resource {};

	typedef make_typelist_<
		schain, viewport, vformat, vbuffer
	>::type resource_types;

	typedef variant_<resource_types, false> resource;
	typedef array_<resource> resources;

	resources m_resources;

	void m_create_resource(const resource &_r);
	void m_destroy_resource(uint _ID);
	bool m_set_target(uint _ID);
	bool m_set_viewport(uint _ID);
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

	if (m_D3DDevice9_p->Release() == 0) m_D3DDevice9_p = 0;
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
					schain l_schain = l_resource.get_<schain>();
					l_schain.D3DSChain9_p->Release();
					break;
				}
				case resource_types::type_<viewport>::index :
				{
					break;
				}
				case resource_types::type_<vformat>::index :
				{
					vformat l_vformat = l_resource.get_<vformat>();
					l_vformat.D3DVDecl9_p->Release();
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
					schain l_schain = l_resource.get_<schain>();
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
					viewport l_viewport = l_resource.get_<viewport>();
					if (FAILED(m_D3DDevice9_p->SetViewport(&l_viewport.D3DViewport9))) return false;
					break;
				}
			}
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
		case command_types::type_<destroy_resource>::index : return execute(_command.get_<destroy_resource>());
		case command_types::type_<begin_scene>::index : return execute(_command.get_<begin_scene>());
		case command_types::type_<clear_viewport>::index : return execute(_command.get_<clear_viewport>());
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

	if (FAILED(get_device().CreateAdditionalSwapChain(&l_D3DPP, &l_schain.D3DSChain9_p))) return false;

	m_create_resource(l_schain);

	return true;
}
bool rendering_D3D9::execute(const create_viewport &_command)
{
	viewport l_viewport;
	l_viewport.ID = _command.ID;

	D3DVIEWPORT9 l_D3DViewport9 =
	{
		(DWORD)_command.area.min().x(), (DWORD)_command.area.min().y(),
		(DWORD)_command.area.size().x(), (DWORD)_command.area.size().y(),
		(float)_command.depth.x(), (float)_command.depth.y()
	};
	l_viewport.D3DViewport9 = l_D3DViewport9;

	m_create_resource(l_viewport);

	return true;
}
bool rendering_D3D9::execute(const create_vformat &_command)
{
	vformat l_vformat;
	l_vformat.ID = _command.ID;

	if (FAILED(get_device().CreateVertexDeclaration((CONST D3DVERTEXELEMENT9*)_command.data, &l_vformat.D3DVDecl9_p))) return false;

	m_create_resource(l_vformat);

	return true;
}
bool rendering_D3D9::execute(const create_vbuffer &_command)
{
	vbuffer l_vbuffer;
	l_vbuffer.ID = _command.ID;

	if (FAILED(get_device().CreateVertexBuffer(1024, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &l_vbuffer.D3DVBuffer9_p, 0))) return false;

	m_create_resource(l_vbuffer);

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

// video

video::rendering& video::new_rendering(video &_video)
{
	return * new rendering_D3D9(_video);
}


} /* namespace bk -------------------------------------------------------------------------------*/