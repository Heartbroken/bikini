/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// gui
gui::gui() :
	m_screen_ID(bad_ID)
{}
gui::~gui() {
	assert(m_screen_ID == bad_ID);
}
bool gui::create(const astring &_name) {
	static ge::screen::info sl_screen;
	m_screen_ID = spawn(sl_screen);
	//
	astring l_file = astring("data/gui/") + _name + ".swf";
	std::fstream l_stream(l_file.data()/*, std::ios_base::in|std::ios_base::binary*/);
	if(l_stream.good()) {
		swf::tagstream l_tags(l_stream);
		if(l_tags.good()) {
			swf::RECORDHEADER l_tag;
			while(true) {
				l_tags >> l_tag;
				if(l_tag.type == swf::tag::End) break;
				l_tags.skip(l_tag.length);
			}
			uint a = 0;
		}
	} else {
		std::cerr << "ERROR: Can't create GUI\n";
		return false;
	}
	//
	return true;
}
void gui::destroy() {
	if(exists(m_screen_ID)) {
		kill(m_screen_ID);
		m_screen_ID = bad_ID;
	}
}
bool gui::expose(exposer &_exposer) const {
	array_<uint> l_order;
	l_order.push_back(m_screen_ID);
	for(uint i = 0; i < l_order.size(); ++i) {
		uint l_element_ID = l_order[i];
		if(exists(l_element_ID)) {
			element &l_e = get<element>(l_element_ID);
			l_e.expose(_exposer);
			for(uint i = 0, s = l_e.kid_count(); i < s; ++i) {
				l_order.push_back(l_e.kid_ID(i));
			}
		}
	}
	return true;
}
bool gui::render(window &_window) const {
	bool l_save_active = _window.active();
	if(_window.active() || _window.begin()) {
		_window.clear(cf::all);
		array_<uint> l_order;
		l_order.push_back(m_screen_ID);
		for(uint i = 0; i < l_order.size(); ++i) {
			uint l_element_ID = l_order[i];
			if(exists(l_element_ID)) {
				element &l_e = get<element>(l_element_ID);
				l_e.render(_window);
				for(uint i = 0, s = l_e.kid_count(); i < s; ++i) {
					l_order.push_back(l_e.kid_ID(i));
				}
			}
		}
		_window.flush_drawings();
		_window.remove_scissor();
		if(!l_save_active) _window.end();
	}
	return true;
}
void gui::resize(window &_window) const {
	if(exists(m_screen_ID)) {
		ge::screen &l_screen = get<ge::screen>(m_screen_ID);
		l_screen.set_rect(rect(0, 0, _window.width(), _window.height()));
	}
}

// gui::element

gui::element::element(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID) :
	manager::object(_info, _gui),
	m_rect(_x, _y, _w, _h),
	m_parent_dependency(add_dependency(_parent_ID)),
	m_color(white),
	m_clip(true)
{
	if(get_gui().exists(parent_ID())) {
		element &l_parent = get_gui().get<element>(parent_ID());
		l_parent.add_kid(ID());
	}
}
bool gui::element::expose(exposer &_exposer) const {
	if(clip()) {
		rect l_r = clip_rect();
//		_exposer.set_scissor(l_r.left(), l_r.top(), l_r.right() + 1, l_r.bottom() + 1);
	} else {
//		_exposer.remove_scissor();
	}
	const color &l_c = get_color();
//	if(l_c.a() > 0) _exposer.draw_rect(abs_rect(), l_c);
	return false;
}
bool gui::element::render(window &_window) const {
	if(clip()) {
		rect l_r = clip_rect();
		_window.set_scissor(l_r.left(), l_r.top(), l_r.right() + 1, l_r.bottom() + 1);
	} else {
		_window.remove_scissor();
	}
	const color &l_c = get_color();
	if(l_c.a() > 0) {
		rect l_r = abs_rect();
		return _window.draw_rect(l_r.left(), l_r.top(), l_r.right(), l_r.bottom(), l_c);
	}
	return false;
}

// gui::element::info

gui::element::info::info(uint _type) :
	manager::object::info(_type)
{}

namespace ge { /*--------------------------------------------------------------------------------*/

// screen::info

screen::info::info() :
	gui::element::info(gui::et::screen)
{}

// screen

screen::screen(const info &_info, gui &_gui) :
	gui::element(_info, _gui, 0, 0, 0, 0, bad_ID)
{
	set_color(0);
}

// panel::info

panel::info::info() :
	gui::element::info(gui::et::panel)
{}

// panel

panel::panel(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID) :
	gui::element(_info, _gui, _x, _y, _w, _h, _parent_ID)
{
	set_clip();
}
bool panel::render(window &_window) const {
	super::render(_window);

	gui::rect l_r = abs_rect();

	_window.draw_line(l_r.left(), l_r.top(), l_r.right(), l_r.bottom(), red, 10);
	_window.draw_line(l_r.right(), l_r.top(), l_r.left(), l_r.bottom(), red, 10);

	_window.draw_line(l_r.left(), l_r.top(), l_r.right(), l_r.top(), red, 5);
	_window.draw_line(l_r.right(), l_r.top(), l_r.right(), l_r.bottom(), red, 5);
	_window.draw_line(l_r.right(), l_r.bottom(), l_r.left(), l_r.bottom(), red, 5);
	_window.draw_line(l_r.left(), l_r.bottom(), l_r.left(), l_r.top(), red, 5);
	return true;
}

} /* namespace ge -------------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
