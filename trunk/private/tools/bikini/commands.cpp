#include "stdafx.h"

namespace commands { /*--------------------------------------------------------------------------*/

typedef std::map<bk::astring, _command*> command_map;
command_map *g_command_map_p = 0;

void create()
{
	g_command_map_p = new command_map;
}
void destroy()
{
	struct _l { static void destroy(command_map::value_type &_v) { delete _v.second; }};
	std::for_each(g_command_map_p->begin(), g_command_map_p->end(), _l::destroy);
	delete g_command_map_p;
}

void add_command(const bk::achar* _name, _command &_c)
{
	remove(_name);
	(*g_command_map_p)[_name] = &_c;
}
void remove(const bk::achar* _name)
{
	command_map::iterator l_it = g_command_map_p->find(_name);
	if (l_it != g_command_map_p->end())
	{
		delete l_it->second;
		g_command_map_p->erase(l_it);
	}
}

// export interface

extern "C" __declspec(dllexport)
const bk::wchar* __stdcall request(const bk::wchar* _command)
{
	std::stringstream l_stream(bk::utf8(_command));
	pugi::xml_document l_document;
	l_document.load(l_stream, pugi::format_default|pugi::format_write_bom_utf8);
	pugi::xml_node l_command = l_document.child("command");
	if (l_command)
	{
		bk::astring l_name = l_command.attribute("name").value();
		command_map::iterator l_it = g_command_map_p->find(l_name);
		if (l_it != g_command_map_p->end())
		{
			pugi::xml_node l_args = l_command.child("arguments");
			pugi::xml_document l_document;
			pugi::xml_node l_result = l_document.append_child();
			l_result.set_name("result");
			l_it->second->execute(l_args, l_result);

			std::ostringstream l_stream;
			pugi::xml_writer_stream l_writer(l_stream);
			l_document.save(l_writer, "  ", pugi::format_no_declaration | pugi::format_indent);

			static bk::wstring l_xml;
			l_xml = bk::utf8(l_stream.str());

			return l_xml.c_str();
		}
	}
	return L"<error />";
}

} /* namespace commands -------------------------------------------------------------------------*/
