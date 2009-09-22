/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

static const D3DVERTEXELEMENT9 sg_vformat[] = 
{
	{ 0, 0, D3DDECLTYPE_SHORT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0xff, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 }
};

renderer::renderer(video &_video)
:
	m_video(_video), m_viewport_ID(bad_ID)
{
	m_vo_vformat_info.data = sg_vformat;
}
renderer::~renderer()
{
}
bool renderer::create()
{
	m_vo_vformat_ID = m_video.spawn(m_vo_vformat_info);
	return true;
}
void renderer::destroy()
{
	m_video.kill(m_vo_vformat_ID);
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
