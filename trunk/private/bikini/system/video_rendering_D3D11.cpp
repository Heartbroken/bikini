/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

//#pragma comment(lib, "d3d9")

namespace bk { /*--------------------------------------------------------------------------------*/

// rendering_D3D11

struct rendering_D3D11 : video::rendering
{
	rendering_D3D11(video &_video);
	~rendering_D3D11();
	bool initialize();
	void finalize();
	bool execute(const command &_command);

};

rendering_D3D11::rendering_D3D11(video &_video)
:
	video::rendering(_video)
{}
rendering_D3D11::~rendering_D3D11()
{
}
bool rendering_D3D11::initialize()
{
	return true;
}
void rendering_D3D11::finalize()
{
}
bool rendering_D3D11::execute(const command &_command)
{
	//switch (_command.type())
	//{
	//	case command_types::type_<create_schain>::index : return execute(_command.get_<create_schain>());
	//	case command_types::type_<create_viewport>::index : return execute(_command.get_<create_viewport>());
	//	case command_types::type_<create_vformat>::index : return execute(_command.get_<create_vformat>());
	//	case command_types::type_<create_vbuffer>::index : return execute(_command.get_<create_vbuffer>());
	//	case command_types::type_<write_vbuffer>::index : return execute(_command.get_<write_vbuffer>());
	//	case command_types::type_<create_vshader>::index : return execute(_command.get_<create_vshader>());
	//	case command_types::type_<create_pshader>::index : return execute(_command.get_<create_pshader>());
	//	case command_types::type_<create_vbufset>::index : return execute(_command.get_<create_vbufset>());
	//	case command_types::type_<create_states>::index : return execute(_command.get_<create_states>());
	//	case command_types::type_<create_consts>::index : return execute(_command.get_<create_consts>());
	//	case command_types::type_<write_consts>::index : return execute(_command.get_<write_consts>());
	//	case command_types::type_<create_texture>::index : return execute(_command.get_<create_texture>());
	//	case command_types::type_<write_texture>::index : return execute(_command.get_<write_texture>());
	//	case command_types::type_<create_texset>::index : return execute(_command.get_<create_texset>());
	//	case command_types::type_<destroy_resource>::index : return execute(_command.get_<destroy_resource>());
	//	case command_types::type_<begin_scene>::index : return execute(_command.get_<begin_scene>());
	//	case command_types::type_<clear_viewport>::index : return execute(_command.get_<clear_viewport>());
	//	case command_types::type_<draw_primitive>::index : return execute(_command.get_<draw_primitive>());
	//	case command_types::type_<end_scene>::index : return execute(_command.get_<end_scene>());
	//	case command_types::type_<present_schain>::index : return execute(_command.get_<present_schain>());
	//}
	return false;
}

video::rendering* new_rendering_D3D11(video &_video)
{
	return 0;//new rendering_D3D11(_video);
}

} /* namespace bk -------------------------------------------------------------------------------*/
