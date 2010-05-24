/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dx11")
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
	IDXGIFactory *m_pDXGIFactory;
	ID3D11Buffer *m_pD3D11BufferVS, *m_pD3D11BufferPS;

	ID3D11Device& get_device() const;
	IDXGIFactory& get_factory() const;

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

	struct schain : _resource { IDXGISwapChain *pDXGISChain; ID3D11RenderTargetView *pD3D11RenderTargetView; };
	struct viewport : _resource { D3D11_VIEWPORT D3D11Viewport; };
	struct vformat : _resource { ID3D11InputLayout *pD3D11InputLayout; };
	struct vbuffer : _resource { ID3D11Buffer *pD3D11Buffer; uint size, used; };
	struct vshader : _resource { ID3D11VertexShader *pD3D11VertexShader; };
	struct pshader : _resource { ID3D11PixelShader *pD3D11PixelShader; };
	struct vbufset : _resource { uint vformat_ID, vbuffer_IDs[8], offsets[8], strides[8]; };
	struct states : _resource { ID3D11RasterizerState *pD3D11RasterizerState; ID3D11DepthStencilState *pD3D11DepthStencilState; };
	struct consts : _resource { byte_array data; };
	struct texture : _resource { ID3D11Texture2D *pD3D11Texture2D; ID3D11ShaderResourceView *pD3D11ShaderResourceView; };
	struct texset : _resource { uint texture_IDs[8]; };

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

rendering_D3D11::rendering_D3D11(video &_video)
:
	video::rendering(_video),
	m_pD3D11Device(0), m_pD3D11DeviceContext(0),
	m_pDXGIFactory(0)
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

	IDXGIDevice *l_pDXGIDevice;
	if (FAILED(m_pD3D11Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&l_pDXGIDevice)))
	{
		m_pD3D11Device->Release(); m_pD3D11Device = 0;
		return false;
	}

	IDXGIAdapter *l_pDXGIAdapter;
	if (FAILED(l_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&l_pDXGIAdapter)))
	{
		l_pDXGIDevice->Release();
		m_pD3D11Device->Release(); m_pD3D11Device = 0;
		return false;
	}

	if (FAILED(l_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory)))
	{
		l_pDXGIAdapter->Release();
		l_pDXGIDevice->Release();
		m_pD3D11Device->Release(); m_pD3D11Device = 0;
		return false;
	}

	l_pDXGIAdapter->Release();
	l_pDXGIDevice->Release();

	{
		D3D11_BUFFER_DESC l_desc;
		l_desc.ByteWidth = 512 * sizeof(float4);
		l_desc.Usage = D3D11_USAGE_DYNAMIC;
		l_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		l_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		l_desc.MiscFlags = 0;
		l_desc.StructureByteStride = 0;

		if (FAILED(m_pD3D11Device->CreateBuffer(&l_desc, NULL, &m_pD3D11BufferVS)))
		{
			m_pDXGIFactory->Release(); m_pDXGIFactory = 0;
			m_pD3D11Device->Release(); m_pD3D11Device = 0;
			return false;
		}

		m_pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &m_pD3D11BufferVS);
	}
	{
		D3D11_BUFFER_DESC l_desc;
		l_desc.ByteWidth = 512 * sizeof(float4);
		l_desc.Usage = D3D11_USAGE_DYNAMIC;
		l_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		l_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		l_desc.MiscFlags = 0;
		l_desc.StructureByteStride = 0;

		if (FAILED(m_pD3D11Device->CreateBuffer(&l_desc, NULL, &m_pD3D11BufferPS)))
		{
			m_pDXGIFactory->Release(); m_pDXGIFactory = 0;
			m_pD3D11Device->Release(); m_pD3D11Device = 0;
			return false;
		}

		m_pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &m_pD3D11BufferPS);
	}

	return true;
}
void rendering_D3D11::finalize()
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

	if (m_pD3D11BufferVS != 0) m_pD3D11BufferVS->Release();
	if (m_pD3D11BufferPS != 0) m_pD3D11BufferPS->Release();
	if (m_pDXGIFactory != 0) m_pDXGIFactory->Release();
	if (m_pD3D11DeviceContext != 0) m_pD3D11DeviceContext->Release();
	if (m_pD3D11Device != 0) m_pD3D11Device->Release();
}
ID3D11Device& rendering_D3D11::get_device() const
{
	return *m_pD3D11Device;
}
IDXGIFactory& rendering_D3D11::get_factory() const
{
	return *m_pDXGIFactory;
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
					l_schain.pD3D11RenderTargetView->Release();
					l_schain.pDXGISChain->Release();
					break;
				}
				case resource_types::type_<viewport>::index :
				{
					break;
				}
				case resource_types::type_<vformat>::index :
				{
					vformat &l_vformat = l_resource.get_<vformat>();
					l_vformat.pD3D11InputLayout->Release();
					break;
				}
				case resource_types::type_<vbuffer>::index :
				{
					vbuffer &l_vbuffer = l_resource.get_<vbuffer>();
					l_vbuffer.pD3D11Buffer->Release();
					break;
				}
				case resource_types::type_<vshader>::index :
				{
					vshader &l_vshader = l_resource.get_<vshader>();
					l_vshader.pD3D11VertexShader->Release();
					break;
				}
				case resource_types::type_<pshader>::index :
				{
					pshader &l_pshader = l_resource.get_<pshader>();
					l_pshader.pD3D11PixelShader->Release();
					break;
				}
				case resource_types::type_<vbufset>::index :
				{
					break;
				}
				case resource_types::type_<states>::index :
				{
					states &l_states = l_resource.get_<states>();
					l_states.pD3D11RasterizerState->Release();
					l_states.pD3D11DepthStencilState->Release();
					break;
				}
				case resource_types::type_<consts>::index :
				{
					break;
				}
				case resource_types::type_<texture>::index :
				{
					texture &l_texture = l_resource.get_<texture>();
					l_texture.pD3D11ShaderResourceView->Release();
					l_texture.pD3D11Texture2D->Release();
					break;
				}
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
					ID3D11RenderTargetView *l_rtarget_p = l_schain.pD3D11RenderTargetView;
					m_pD3D11DeviceContext->OMSetRenderTargets(1, &l_rtarget_p, NULL);
					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D11::m_set_viewport(uint _ID)
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
					m_pD3D11DeviceContext->RSSetViewports(1, &l_viewport.D3D11Viewport);
					break;
				}
			}
		}
	}
	return true;
}
bool rendering_D3D11::m_set_vformat(uint _ID)
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
					m_pD3D11DeviceContext->IASetInputLayout(l_vformat.pD3D11InputLayout);
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D11::m_set_vbuffer(uint _i, uint _ID, uint _offset, uint _stride)
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
					m_pD3D11DeviceContext->IASetVertexBuffers((UINT)_i, 1, &l_vbuffer.pD3D11Buffer, (UINT*)&_stride, (UINT*)&_offset);
					break;
				}
			}
			return true;
		}

		m_pD3D11DeviceContext->IASetVertexBuffers((UINT)_i, 1, NULL, NULL, NULL);
	}
	return true;
}
bool rendering_D3D11::m_set_vbuffers(uint _ID)
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
bool rendering_D3D11::m_set_vshader(uint _ID)
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
					m_pD3D11DeviceContext->VSSetShader(l_vshader.pD3D11VertexShader, NULL, 0);
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D11::m_set_pshader(uint _ID)
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
					m_pD3D11DeviceContext->PSSetShader(l_pshader.pD3D11PixelShader, NULL, 0);
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D11::m_set_states(uint _ID)
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
					m_pD3D11DeviceContext->OMSetDepthStencilState(l_states.pD3D11DepthStencilState, 0);
					m_pD3D11DeviceContext->RSSetState(l_states.pD3D11RasterizerState);
					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D11::m_set_consts(uint _ID)
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

						D3D11_MAPPED_SUBRESOURCE l_resource1, l_resource2;
						if (FAILED(m_pD3D11DeviceContext->Map(m_pD3D11BufferVS, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_resource1))) return false;
						if (FAILED(m_pD3D11DeviceContext->Map(m_pD3D11BufferPS, 0, D3D11_MAP_WRITE_DISCARD, 0, &l_resource2))) return false;

						while (l_current - l_begin < l_length)
						{
							uint l_type = *(uint*)l_current; l_current += sizeof(uint);
							uint l_offset = *(uint*)l_current; l_current += sizeof(uint);
							uint l_size = *(uint*)l_current; l_current += sizeof(uint);

							if (l_type & 1)
								memcpy((float4*)l_resource1.pData + l_offset, l_current, l_size);

							if (l_type & 2)
								memcpy((float4*)l_resource2.pData + l_offset, l_current, l_size);

							l_current += l_size;
						}

						m_pD3D11DeviceContext->Unmap(m_pD3D11BufferVS, 0);
						m_pD3D11DeviceContext->Unmap(m_pD3D11BufferPS, 0);
					}

					break;
				}
			}
			return true;
		}
	}
	return true;
}
bool rendering_D3D11::m_set_texture(uint _i, uint _ID)
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
					ID3D11ShaderResourceView *l_pD3D11ShaderResourceView = l_texture.pD3D11ShaderResourceView;
					m_pD3D11DeviceContext->PSGetShaderResources((UINT)_i, 1, &l_pD3D11ShaderResourceView);
					break;
				}
			}
			return true;
		}

		m_pD3D11DeviceContext->PSGetShaderResources((UINT)_i, 1, NULL);
	}
	return true;
}
bool rendering_D3D11::m_set_textures(uint _ID)
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
bool rendering_D3D11::execute(const command &_command)
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
bool rendering_D3D11::execute(const create_schain &_command)
{
	schain l_schain;
	l_schain.ID = _command.ID;

	DXGI_SWAP_CHAIN_DESC l_desc = {0};
	l_desc.OutputWindow = (HWND)_command.window;
	l_desc.Windowed = TRUE;
	l_desc.BufferCount = 1;
	l_desc.BufferDesc.Width = 0;
	l_desc.BufferDesc.Height = 0;
	l_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	l_desc.BufferDesc.RefreshRate.Numerator = 60;
	l_desc.BufferDesc.RefreshRate.Denominator = 1;
	l_desc.SampleDesc.Count = 8;
	l_desc.SampleDesc.Quality = 0;
	l_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	if (FAILED(get_factory().CreateSwapChain(m_pD3D11Device, &l_desc, &l_schain.pDXGISChain))) return false;

	ID3D11Texture2D *l_pD3D11Texture2D;
	if (FAILED(l_schain.pDXGISChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&l_pD3D11Texture2D))))
	{
		l_schain.pDXGISChain->Release();
		return false;
	}

	if (FAILED(m_pD3D11Device->CreateRenderTargetView(l_pD3D11Texture2D, NULL, &l_schain.pD3D11RenderTargetView)))
	{
		l_pD3D11Texture2D->Release();
		l_schain.pDXGISChain->Release();
		return false;
	}

	l_pD3D11Texture2D->Release();

	m_create_resource(l_schain);

	return true;
}
bool rendering_D3D11::execute(const create_viewport &_command)
{
	viewport l_viewport;
	l_viewport.ID = _command.ID;

	D3D11_VIEWPORT l_D3D11Viewport =
	{
		(FLOAT)_command.area.min().x, (FLOAT)_command.area.min().y,
		(FLOAT)_command.area.size().x, (FLOAT)_command.area.size().y,
		(FLOAT)_command.depth.x, (FLOAT)_command.depth.y
	};
	l_viewport.D3D11Viewport = l_D3D11Viewport;

	m_create_resource(l_viewport);

	return true;
}
static DXGI_FORMAT get_DXGI_format(video::vf::element_type _type)
{
	switch (_type)
	{
		case video::vf::short2 : return DXGI_FORMAT_R16G16_SINT;
	}

	return DXGI_FORMAT_UNKNOWN;
}
static const achar* get_HLSL_type(video::vf::element_type _type)
{
	switch (_type)
	{
		case video::vf::short2 : return "int2";
	}

	return "float4";
}
bool rendering_D3D11::execute(const create_vformat &_command)
{
	vformat l_vformat;
	l_vformat.ID = _command.ID;

	astring l_code;

	l_code =
		"struct input\n"
		"{\n"
	;
	
	uint l_element_count = 0;
	D3D11_INPUT_ELEMENT_DESC l_DX11_elements[64];
	video::vf::element* l_elements = (video::vf::element*)_command.data;

	while (true)
	{
		video::vf::element &l_element = l_elements[l_element_count];
		if (l_element.semantic == 0) break;

		D3D11_INPUT_ELEMENT_DESC &l_DX11_element = l_DX11_elements[l_element_count];
		l_DX11_element.SemanticName = l_element.semantic;
		l_DX11_element.SemanticIndex = l_element.index;
		l_DX11_element.Format = get_DXGI_format(l_element.type);
		l_DX11_element.InputSlot = l_element.slot;
		l_DX11_element.AlignedByteOffset = l_element.offset;
		l_DX11_element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		l_DX11_element.InstanceDataStepRate = 0;

		achar l_line[64];
		if (sprintf(l_line, "	%s p%d : %s;\n", get_HLSL_type(l_element.type), l_element_count, l_element.semantic) == -1) return false;
		l_code += l_line;

		++l_element_count;
	}

	l_code +=
		"};\n"
		"float4 main(input _in) : SV_POSITION\n"
		"{\n"
		"	return float4(0, 0, 0, 0);\n"
		"}\n"
	;

	ID3D10Blob *l_shader_p = 0;
	ID3D10Blob *l_error_p = 0;
	if (FAILED(D3DX11CompileFromMemory
	(
		l_code.c_str(),
		l_code.size(),
		"vformat_fake_shader",
		NULL, NULL,
		"main",
		"vs_5_0",
		D3D10_SHADER_OPTIMIZATION_LEVEL2,
		0,
		NULL,
		&l_shader_p,
		&l_error_p,
		0
	)))
	{
		l_error_p->Release();
		return false;
	}

	if (FAILED(m_pD3D11Device->CreateInputLayout(l_DX11_elements, l_element_count, l_shader_p->GetBufferPointer(), l_shader_p->GetBufferSize(), &l_vformat.pD3D11InputLayout))) return false;

	l_shader_p->Release();

	m_create_resource(l_vformat);

	return true;
}
bool rendering_D3D11::execute(const create_vbuffer &_command)
{
	vbuffer l_vbuffer;
	l_vbuffer.ID = _command.ID;
	l_vbuffer.size = _command.size;
	l_vbuffer.used = 0;

	D3D11_BUFFER_DESC l_desc = {0};
	l_desc.ByteWidth = l_vbuffer.size;
	l_desc.Usage = D3D11_USAGE_DYNAMIC;
	l_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	l_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(m_pD3D11Device->CreateBuffer(&l_desc, NULL, &l_vbuffer.pD3D11Buffer))) return false;

	m_create_resource(l_vbuffer);

	return true;
}
bool rendering_D3D11::execute(const write_vbuffer &_command)
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
				D3D11_MAPPED_SUBRESOURCE l_resource;
				if (FAILED(m_pD3D11DeviceContext->Map(l_vbuffer.pD3D11Buffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &l_resource))) return false;

				get_data((u8*)l_resource.pData + l_vbuffer.used, _command.extra);

				m_pD3D11DeviceContext->Unmap(l_vbuffer.pD3D11Buffer, 0);

				l_vbuffer.used += _command.extra;

				return true;
			}
		}
	}

	throw_data(_command.extra);

	return true;
}
bool rendering_D3D11::execute(const create_vshader &_command)
{
	vshader l_vshader;
	l_vshader.ID = _command.ID;

	if (FAILED(m_pD3D11Device->CreateVertexShader(_command.data, _command.size, NULL, &l_vshader.pD3D11VertexShader))) return false;

	m_create_resource(l_vshader);

	return true;
}
bool rendering_D3D11::execute(const create_pshader &_command)
{
	pshader l_pshader;
	l_pshader.ID = _command.ID;

	if (FAILED(m_pD3D11Device->CreatePixelShader(_command.data, _command.size, NULL, &l_pshader.pD3D11PixelShader))) return false;

	m_create_resource(l_pshader);

	return true;
}
bool rendering_D3D11::execute(const create_vbufset &_command)
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
bool rendering_D3D11::execute(const create_states &_command)
{
	states l_states;
	l_states.ID = _command.ID;

	{
		D3D11_RASTERIZER_DESC l_desc =
		{
			D3D11_FILL_SOLID,		// D3D11_FILL_MODE FillMode;
			D3D11_CULL_NONE,		// D3D11_CULL_MODE CullMode;
			TRUE,					// BOOL FrontCounterClockwise;
			0,						// INT DepthBias;
			0,						// FLOAT DepthBiasClamp;
			0,						// FLOAT SlopeScaledDepthBias;
			FALSE,					// BOOL DepthClipEnable;
			FALSE,					// BOOL ScissorEnable;
			FALSE,					// BOOL MultisampleEnable;
			TRUE					// BOOL AntialiasedLineEnable;
		};

		if (FAILED(m_pD3D11Device->CreateRasterizerState(&l_desc, &l_states.pD3D11RasterizerState))) return false;
	}
	{
		D3D11_DEPTH_STENCIL_DESC l_desc = {0};
		l_desc.DepthEnable = FALSE;

		if (FAILED(m_pD3D11Device->CreateDepthStencilState(&l_desc, &l_states.pD3D11DepthStencilState))) return false;
	}

	m_create_resource(l_states);

	return true;
}
bool rendering_D3D11::execute(const create_consts &_command)
{
	consts l_consts;
	l_consts.ID = _command.ID;

	m_create_resource(l_consts);

	return true;
}
bool rendering_D3D11::execute(const write_consts &_command)
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
bool rendering_D3D11::execute(const create_texture &_command)
{
	texture l_texture;
	l_texture.ID = _command.ID;

	{
		D3D11_TEXTURE2D_DESC l_desc = {0};
		l_desc.Width = (UINT)_command.size.x;
		l_desc.Height = (UINT)_command.size.y;
		l_desc.MipLevels = 0;
		l_desc.ArraySize = 1;
		switch (_command.format)
		{
			case video::tf::a8 : l_desc.Format = DXGI_FORMAT_A8_UNORM; break;
			case video::tf::b8g8r8 : l_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
			case video::tf::a8b8g8r8 : l_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
			case video::tf::a8r8g8b8 : l_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
		}
		l_desc.SampleDesc.Count = 1;
		l_desc.SampleDesc.Quality = 0;
		l_desc.Usage = D3D11_USAGE_DEFAULT;
		l_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		l_desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE;
		l_desc.MiscFlags = 0;

		if (FAILED(m_pD3D11Device->CreateTexture2D(&l_desc, NULL, &l_texture.pD3D11Texture2D))) return false;
	}
	{
		if (FAILED(m_pD3D11Device->CreateShaderResourceView(l_texture.pD3D11Texture2D, NULL, &l_texture.pD3D11ShaderResourceView)))
		{
			l_texture.pD3D11Texture2D->Release();
			return false;
		}
	}

	//D3DFORMAT l_format;
	//switch (_command.format)
	//{
	//	case video::tf::a8 : l_format = D3DFMT_A8; break;
	//	case video::tf::b8g8r8 : l_format = D3DFMT_A8R8G8B8; break;
	//	case video::tf::a8b8g8r8 : l_format = D3DFMT_A8R8G8B8; break;
	//	case video::tf::a8r8g8b8 : l_format = D3DFMT_A8R8G8B8; break;
	//}

	//if (FAILED(m_D3DDevice9_p->CreateTexture((UINT)_command.size.x, (UINT)_command.size.y, 0, 0, l_format, D3DPOOL_DEFAULT, &l_texture.D3DTexture9_p, 0))) return false;

	m_create_resource(l_texture);

	return true;
}
bool rendering_D3D11::execute(const write_texture &_command)
{
	uint_ID l_ID(_command.ID);

	resource &l_resource = m_resources[l_ID.index];
	if (!l_resource.is_nothing() && l_resource.get_<_resource>().ID == _command.ID)
	{
		if (l_resource.type() == resource_types::type_<texture>::index)
		{
			texture &l_texture = l_resource.get_<texture>();

			//uint l_format; get_data(&l_format, sizeof(l_format));
			//sint2 l_size; get_data(&l_size, sizeof(l_size));
			//uint l_pitch; get_data(&l_pitch, sizeof(l_pitch));

			//D3DFORMAT l_D3DFormat;
			//switch (l_format)
			//{
			//	case video::tf::a8 : l_D3DFormat = D3DFMT_A8; break;
			//	case video::tf::b8g8r8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
			//	case video::tf::a8b8g8r8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
			//	case video::tf::a8r8g8b8 : l_D3DFormat = D3DFMT_A8R8G8B8; break;
			//}

			//IDirect3DTexture9 *l_D3DTex9_p;
			//if (FAILED(m_D3DDevice9_p->CreateTexture((UINT)l_size.x, (UINT)l_size.y, 1, 0, l_D3DFormat, D3DPOOL_SYSTEMMEM, &l_D3DTex9_p, 0)))
			//{
			//	throw_data(l_size.y * l_pitch);
			//	return false;
			//}

			//D3DLOCKED_RECT l_rect;
			//l_D3DTex9_p->LockRect(0, &l_rect, 0, 0);
			//if (l_format == video::tf::b8g8r8 || l_format == video::tf::a8b8g8r8)
			//{
			//	assert((uint)l_rect.Pitch >= l_pitch);
			//	uint l_width = l_size.x, l_height = l_size.y;

			//	for (uint y = 0; y < l_height; ++y)
			//	{
			//		byte* l_row = (byte*)l_rect.pBits + y * l_rect.Pitch;
			//		get_data(l_row, l_pitch);

			//		switch (l_format)
			//		{
			//			case video::tf::b8g8r8 :
			//			{
			//				for (uint x = 0; x < l_width; ++x)
			//				{
			//					uint l_pixel = l_width - 1 - x;

			//					uint l_pixel_3 = l_pixel * 3;
			//					byte l_r = l_row[l_pixel_3 + 2];
			//					byte l_g = l_row[l_pixel_3 + 1];
			//					byte l_b = l_row[l_pixel_3 + 0];
			//					byte l_a = 0xff;

			//					uint l_pixel_4 = l_pixel * 4;
			//					l_row[l_pixel_4 + 0] = l_r;
			//					l_row[l_pixel_4 + 1] = l_g;
			//					l_row[l_pixel_4 + 2] = l_b;
			//					l_row[l_pixel_4 + 3] = l_a;
			//				}
			//				break;
			//			}
			//			case video::tf::a8b8g8r8 :
			//			{
			//				for (uint x = 0; x < l_width; ++x)
			//				{
			//					uint l_pixel = (l_width - 1 - x) * 4;

			//					byte l_r = l_row[l_pixel + 2];
			//					byte l_g = l_row[l_pixel + 1];
			//					byte l_b = l_row[l_pixel + 0];
			//					byte l_a = l_row[l_pixel + 3];

			//					l_row[l_pixel + 0] = l_r;
			//					l_row[l_pixel + 1] = l_g;
			//					l_row[l_pixel + 2] = l_b;
			//					l_row[l_pixel + 3] = l_a;
			//				}
			//				break;
			//			}
			//		}
			//	}
			//}
			//else
			//{
			//	get_data(l_rect.pBits, l_size.y * l_pitch);
			//}
			//l_D3DTex9_p->UnlockRect(0);

			//l_texture.D3DTexture9_p->Release();

			//DWORD l_usage = 0;
			//if (l_size.x * l_size.y > 1) l_usage |= D3DUSAGE_AUTOGENMIPMAP;

			//m_D3DDevice9_p->CreateTexture((UINT)l_size.x, (UINT)l_size.y, 0, l_usage, l_D3DFormat, D3DPOOL_DEFAULT, &l_texture.D3DTexture9_p, 0);

			//if (l_usage & D3DUSAGE_AUTOGENMIPMAP) l_texture.D3DTexture9_p->SetAutoGenFilterType(D3DTEXF_ANISOTROPIC);
			//
			//IDirect3DSurface9 *l_D3DSrcSurf9_p; l_D3DTex9_p->GetSurfaceLevel(0, &l_D3DSrcSurf9_p);
			//IDirect3DSurface9 *l_D3DDstSurf9_p; l_texture.D3DTexture9_p->GetSurfaceLevel(0, &l_D3DDstSurf9_p);
			//m_D3DDevice9_p->UpdateSurface(l_D3DSrcSurf9_p, 0, l_D3DDstSurf9_p, 0);
			//l_D3DDstSurf9_p->Release();
			//l_D3DSrcSurf9_p->Release();

			//l_D3DTex9_p->Release();

			//return true;
		}
	}

	throw_data(_command.extra);

	return true;
}
bool rendering_D3D11::execute(const create_texset &_command)
{
	texset l_texset;
	l_texset.ID = _command.ID;

	memcpy(l_texset.texture_IDs, _command.texture_IDs, sizeof(l_texset.texture_IDs));

	m_create_resource(l_texset);

	return true;
}
bool rendering_D3D11::execute(const destroy_resource &_command)
{
	m_destroy_resource(_command.ID);

	return true;
}
bool rendering_D3D11::execute(const begin_scene &_command)
{
	return true;
}
bool rendering_D3D11::execute(const clear_viewport &_command)
{
	if (!m_set_target(_command.target_ID)) return false;
	if (!m_set_viewport(_command.viewport_ID)) return false;

	if (_command.clear.f & cf::color)
	{
		FLOAT l_c[] = { _command.clear.c.r, _command.clear.c.g, _command.clear.c.b, _command.clear.c.a };
		ID3D11RenderTargetView *l_pD3D11RenderTargetView;
		m_pD3D11DeviceContext->OMGetRenderTargets(1, &l_pD3D11RenderTargetView, NULL);
		m_pD3D11DeviceContext->ClearRenderTargetView(l_pD3D11RenderTargetView, l_c);
		l_pD3D11RenderTargetView->Release();
	}
	//if (_command.clear.f & (cf::depth | cf::stencil))
	//{
	//	//float l_z = (float)_command.clear.z;
	//	//DWORD l_stencil = (DWORD)_command.clear.s;
	//	ID3D11RenderTargetView *l_rtarget_p;
	//	m_pD3D11DeviceContext->OMGetRenderTargets(1, &l_rtarget_p, NULL);
	//	FLOAT l_c[] = { _command.clear.c.r, _command.clear.c.g, _command.clear.c.b, _command.clear.c.a };
	//	m_pD3D11DeviceContext->ClearDepthStencilView(l_rtarget_p, l_c);
	//	l_rtarget_p->Release();
	//}

	return true;
}
bool rendering_D3D11::execute(const draw_primitive &_command)
{
	if (!m_set_target(_command.target_ID)) return false;
	if (!m_set_viewport(_command.viewport_ID)) return false;
	if (!m_set_vbuffers(_command.vbufset_ID)) return false;
	if (!m_set_vshader(_command.vshader_ID)) return false;
	if (!m_set_pshader(_command.pshader_ID)) return false;
	if (!m_set_states(_command.states_ID)) return false;
	if (!m_set_consts(_command.consts_ID)) return false;
	if (!m_set_textures(_command.texset_ID)) return false;

	D3D11_PRIMITIVE_TOPOLOGY l_topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	switch (_command.type)
	{
		case D3DPT_TRIANGLELIST : l_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; break;
		case D3DPT_TRIANGLESTRIP : l_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
	}
	m_pD3D11DeviceContext->IASetPrimitiveTopology(l_topology);

	UINT l_vcount = 0;
	switch (_command.type)
	{
		case D3DPT_TRIANGLELIST : l_vcount = _command.size * 3; break;
		case D3DPT_TRIANGLESTRIP : l_vcount = _command.size + 2; break;
	}
	m_pD3D11DeviceContext->Draw(l_vcount, (UINT)_command.start);

	return true;
}
bool rendering_D3D11::execute(const end_scene &_command)
{
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
