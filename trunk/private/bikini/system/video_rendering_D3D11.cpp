/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")

namespace bk { /*--------------------------------------------------------------------------------*/

// rendering_D3D11

struct rendering_D3D11 : video::rendering
{
	rendering_D3D11(video &_video);
	~rendering_D3D11();
	bool initialize();
	void finalize();
	bool execute(const command &_command);

private:
	ID3D11Device *m_pD3D11Device;
	ID3D11DeviceContext *m_pD3D11DeviceContext;

	ID3D11Device& get_device() const;
	IDXGIFactory& get_factory() const;

	bool execute(const create_schain &_command);
	//bool execute(const create_viewport &_command);
	//bool execute(const create_vformat &_command);
	//bool execute(const create_vbuffer &_command);
	//bool execute(const write_vbuffer &_command);
	//bool execute(const create_vshader &_command);
	//bool execute(const create_pshader &_command);
	//bool execute(const create_vbufset &_command);
	//bool execute(const create_states &_command);
	//bool execute(const create_consts &_command);s
	//bool execute(const write_consts &_command);
	//bool execute(const create_texture &_command);
	//bool execute(const write_texture &_command);
	//bool execute(const create_texset &_command);
	//bool execute(const destroy_resource &_command);
	bool execute(const begin_scene &_command);
	bool execute(const clear_viewport &_command);
	//bool execute(const draw_primitive &_command);
	bool execute(const end_scene &_command);
	bool execute(const present_schain &_command);

	struct _resource { uint ID; };

	struct schain : _resource { IDXGISwapChain *pDXGISChain; };

	typedef make_typelist_<
		schain//, viewport, vformat, vbuffer, vshader, pshader, vbufset, states, consts, texture, texset
	>::type resource_types;

	typedef variant_<resource_types, false> resource;
	typedef array_<resource> resources;

	resources m_resources;

	void m_create_resource(const resource &_r);
	void m_destroy_resource(uint _ID);
	bool m_set_target(uint _ID);
};

rendering_D3D11::rendering_D3D11(video &_video)
:
	video::rendering(_video),
	m_pD3D11Device(0), m_pD3D11DeviceContext(0)
{}
rendering_D3D11::~rendering_D3D11()
{
}
bool rendering_D3D11::initialize()
{
	if (FAILED(D3D11CreateDevice
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_SINGLETHREADED|D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&m_pD3D11Device,
		NULL,
		&m_pD3D11DeviceContext
	)))
	{
		return false;
	}
	
	return true;
}
void rendering_D3D11::finalize()
{
	if (m_pD3D11Device != 0)
	{
		m_pD3D11Device->Release();
	}
}
ID3D11Device& rendering_D3D11::get_device() const
{
	return *m_pD3D11Device;
}
IDXGIFactory& rendering_D3D11::get_factory() const
{
	IDXGIDevice *l_pDXGIDevice;
	if (SUCCEEDED(m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&l_pDXGIDevice)))
	{
		IDXGIAdapter *l_pDXGIAdapter;
		if (SUCCEEDED(l_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&l_pDXGIAdapter)))
		{
			IDXGIFactory *l_pIDXGIFactory;
			l_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&l_pIDXGIFactory);

			return *l_pIDXGIFactory;
		}
	}
	      
	return *(IDXGIFactory*)0;
}
void rendering_D3D11::m_create_resource(const resource &_r)
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
void rendering_D3D11::m_destroy_resource(uint _ID)
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
					l_schain.pDXGISChain->Release();
					break;
				}
				//case resource_types::type_<viewport>::index :
				//{
				//	break;
				//}
				//case resource_types::type_<vformat>::index :
				//{
				//	vformat &l_vformat = l_resource.get_<vformat>();
				//	l_vformat.D3DVDecl9_p->Release();
				//	break;
				//}
				//case resource_types::type_<vbuffer>::index :
				//{
				//	vbuffer &l_vbuffer = l_resource.get_<vbuffer>();
				//	l_vbuffer.D3DVBuffer9_p->Release();
				//	break;
				//}
				//case resource_types::type_<vshader>::index :
				//{
				//	vshader &l_vshader = l_resource.get_<vshader>();
				//	l_vshader.D3DVShader9_p->Release();
				//	break;
				//}
				//case resource_types::type_<pshader>::index :
				//{
				//	pshader &l_pshader = l_resource.get_<pshader>();
				//	l_pshader.D3DPShader9_p->Release();
				//	break;
				//}
				//case resource_types::type_<vbufset>::index :
				//{
				//	break;
				//}
				//case resource_types::type_<states>::index :
				//{
				//	states &l_states = l_resource.get_<states>();
				//	l_states.D3DSBlock9_p->Release();
				//	break;
				//}
				//case resource_types::type_<consts>::index :
				//{
				//	break;
				//}
				//case resource_types::type_<texture>::index :
				//{
				//	texture &l_texture = l_resource.get_<texture>();
				//	l_texture.D3DTexture9_p->Release();
				//	break;
				//}
			}
			l_resource.destruct();
			set_invalid(_ID);
		}
	}
}
bool rendering_D3D11::m_set_target(uint _ID)
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
					ID3D11Texture2D *l_surface_p;
					l_schain.pDXGISChain->GetBuffer(0, __uuidof(l_surface_p), reinterpret_cast<void**>(&l_surface_p));

					ID3D11RenderTargetView *l_rtarget_p = 0;
					m_pD3D11Device->CreateRenderTargetView(l_surface_p, NULL, &l_rtarget_p);
					m_pD3D11DeviceContext->OMSetRenderTargets(1, &l_rtarget_p, NULL);
					l_surface_p->Release();

					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D11::execute(const command &_command)
{
	switch (_command.type())
	{
		case command_types::type_<create_schain>::index : return execute(_command.get_<create_schain>());
		//case command_types::type_<create_viewport>::index : return execute(_command.get_<create_viewport>());
		//case command_types::type_<create_vformat>::index : return execute(_command.get_<create_vformat>());
		//case command_types::type_<create_vbuffer>::index : return execute(_command.get_<create_vbuffer>());
		//case command_types::type_<write_vbuffer>::index : return execute(_command.get_<write_vbuffer>());
		//case command_types::type_<create_vshader>::index : return execute(_command.get_<create_vshader>());
		//case command_types::type_<create_pshader>::index : return execute(_command.get_<create_pshader>());
		//case command_types::type_<create_vbufset>::index : return execute(_command.get_<create_vbufset>());
		//case command_types::type_<create_states>::index : return execute(_command.get_<create_states>());
		//case command_types::type_<create_consts>::index : return execute(_command.get_<create_consts>());
		//case command_types::type_<write_consts>::index : return execute(_command.get_<write_consts>());
		//case command_types::type_<create_texture>::index : return execute(_command.get_<create_texture>());
		//case command_types::type_<write_texture>::index : return execute(_command.get_<write_texture>());
		//case command_types::type_<create_texset>::index : return execute(_command.get_<create_texset>());
		//case command_types::type_<destroy_resource>::index : return execute(_command.get_<destroy_resource>());
		case command_types::type_<begin_scene>::index : return execute(_command.get_<begin_scene>());
		case command_types::type_<clear_viewport>::index : return execute(_command.get_<clear_viewport>());
		//case command_types::type_<draw_primitive>::index : return execute(_command.get_<draw_primitive>());
		case command_types::type_<end_scene>::index : return execute(_command.get_<end_scene>());
		case command_types::type_<present_schain>::index : return execute(_command.get_<present_schain>());
	}
	return false;
}
bool rendering_D3D11::execute(const create_schain &_command)
{
	schain l_schain;
	l_schain.ID = _command.ID;

	//D3DPRESENT_PARAMETERS l_D3DPP = {0};
	//l_D3DPP.hDeviceWindow = (HWND)_command.window;
	//l_D3DPP.Windowed = TRUE;
	//l_D3DPP.BackBufferCount = 1;
	//l_D3DPP.BackBufferWidth = 0;
	//l_D3DPP.BackBufferHeight = 0;
	//l_D3DPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	//l_D3DPP.FullScreen_RefreshRateInHz = 0;
	//l_D3DPP.MultiSampleType = (D3DMULTISAMPLE_TYPE)4;
	//l_D3DPP.MultiSampleQuality = 0;
	//l_D3DPP.EnableAutoDepthStencil = FALSE;
	//l_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//l_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//if (FAILED(m_D3DDevice9_p->CreateAdditionalSwapChain(&l_D3DPP, &l_schain.D3DSChain9_p))) return false;

	DXGI_SWAP_CHAIN_DESC l_desc = {0};
	l_desc.OutputWindow = (HWND)_command.window;
	l_desc.Windowed = TRUE;
	l_desc.BufferCount = 1;
	l_desc.BufferDesc.Width = 0;
	l_desc.BufferDesc.Height = 0;
	l_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	l_desc.BufferDesc.RefreshRate.Numerator = 60;
	l_desc.BufferDesc.RefreshRate.Denominator = 1;
	l_desc.SampleDesc.Count = 1;
	l_desc.SampleDesc.Quality = 0;

	if (FAILED(get_factory().CreateSwapChain(m_pD3D11Device, &l_desc, &l_schain.pDXGISChain))) return false;

	m_create_resource(l_schain);

	return true;
}
bool rendering_D3D11::execute(const begin_scene &_command)
{
	//if (FAILED(m_D3DDevice9_p->BeginScene())) return false;
	return true;
}
bool rendering_D3D11::execute(const clear_viewport &_command)
{
	if (!m_set_target(_command.target_ID)) return false;
	//if (!m_set_viewport(_command.viewport_ID)) return false;

	DWORD l_flags = 0;
	if (_command.clear.f & cf::color) l_flags |= D3DCLEAR_TARGET;
	if (_command.clear.f & cf::depth) l_flags |= D3DCLEAR_ZBUFFER;
	if (_command.clear.f & cf::stencil) l_flags |= D3DCLEAR_STENCIL;

	if (l_flags != 0)
	{
		D3DCOLOR l_color = (D3DCOLOR)_command.clear.c;
		float l_z = (float)_command.clear.z;
		DWORD l_stencil = (DWORD)_command.clear.s;

		ID3D11RenderTargetView *l_rtarget_p;
		m_pD3D11DeviceContext->OMGetRenderTargets(1, &l_rtarget_p, NULL);
		FLOAT l_c[] = { 1.f, 0, 0, 1.f };
		m_pD3D11DeviceContext->ClearRenderTargetView(l_rtarget_p, l_c);
		l_rtarget_p->Release();

		//if (FAILED(m_D3DDevice9_p->Clear(0, 0, l_flags, l_color, l_z, l_stencil))) return false;
	}

	return true;
}
bool rendering_D3D11::execute(const end_scene &_command)
{
	//if (FAILED(m_pD3D11Device->EndScene())) return false;
	return true;
}
bool rendering_D3D11::execute(const present_schain &_command)
{
	uint_ID l_command_ID(_command.ID);

	if (l_command_ID.index >= m_resources.size()) return false;

	resource &l_resource = m_resources[l_command_ID.index];

	if (l_resource.is_nothing() || l_resource.get_<_resource>().ID != _command.ID) return false;
	if (l_resource.type() != resource_types::type_<schain>::index) return false;

	schain l_schain = l_resource.get_<schain>();

	if (FAILED(l_schain.pDXGISChain->Present(0, 0))) return false;

	return true;
}

video::rendering* new_rendering_D3D11(video &_video)
{
	//return 0;
	return new rendering_D3D11(_video);
}

} /* namespace bk -------------------------------------------------------------------------------*/
