/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// gui

uint gui::screen_ID() const {
	return m_screen_ID;
}

// gui::rect

inline gui::rect::rect()
{}
inline gui::rect::rect(sint _l, sint _t, uint _w, uint _h) :
	m_lt(_l, _t), m_rb(_l + _w, _t + _h)
{}
inline sint gui::rect::left() const {
	return m_lt.x();
}
inline sint gui::rect::top() const {
	return m_lt.y();
}
inline sint gui::rect::right() const {
	return m_rb.x();
}
inline sint gui::rect::bottom() const {
	return m_rb.y();
}
inline uint gui::rect::width() const {
	return right() - left();
}
inline uint gui::rect::height() const {
	return bottom() - top();
}
inline const gui::rect::point& gui::rect::lefttop() const {
	return m_lt;
}
inline const gui::rect::point& gui::rect::rightbottom() const {
	return m_rb;
}
inline const gui::rect::point gui::rect::size() const {
	return rightbottom() - lefttop();
}
inline gui::rect& gui::rect::operator = (const rect &_r) {
	m_lt = _r.lefttop(); m_rb = _r.rightbottom(); return *this;
}
inline bool gui::rect::operator == (const rect &_r) const {
	return m_lt == _r.lefttop() && m_rb == _r.rightbottom();
}
inline const gui::rect gui::rect::operator + (const point &_p) const {
	return rect(m_lt.x() + _p.x(), m_lt.y() + _p.y(), m_rb.x() - m_lt.x() + _p.x(), m_rb.y() - m_lt.y() + _p.y());
}
inline const gui::rect gui::rect::operator & (const rect &_r) const {
	return rect(max(left(), _r.left()), max(top(), _r.top()), min(right(), _r.right()), min(bottom(), _r.bottom()));
}

// gui::element

inline gui& gui::element::get_gui() const {
	return static_cast<gui&>(get_manager());
}
inline const gui::rect& gui::element::get_rect() const {
	return m_rect;
}
inline void gui::element::set_rect(const rect &_r) {
	m_rect = _r;
}
inline const color& gui::element::get_color() const {
	return m_color;
}
inline void gui::element::set_color(const color &_c) {
	m_color = _c;
}
inline bool gui::element::clip() const {
	return m_clip || (has_parent() && get_parent().clip());
}
inline void gui::element::set_clip(bool _yes) {
	m_clip = _yes;
}
inline uint gui::element::parent_ID() const {
	return dependency(m_parent_dependency);
}
inline bool gui::element::has_parent() const {
	return get_gui().exists(parent_ID());
}
inline gui::element& gui::element::get_parent() const {
	assert(has_parent());
	return get_gui().get<gui::element>(parent_ID());
}
inline const gui::rect gui::element::abs_rect() const {
	return has_parent() ? get_rect() + get_parent().abs_rect().lefttop() : get_rect();
}
inline const gui::rect gui::element::clip_rect() const {
	rect l_r = abs_rect();
	if(has_parent() && get_parent().clip()) l_r = l_r & get_parent().clip_rect();
	//const element *l_e_p = this;
	//while(l_e_p->has_parent()) {
	//	l_e_p = &l_e_p->get_parent();
	//	if(l_e_p->clip()) l_r = l_r & l_e_p->abs_rect();
	//}
	return l_r;
}
inline void gui::element::add_kid(uint _ID) {
	m_kids.push_back(_ID);
}
inline uint gui::element::kid_count() const {
	return m_kids.size();
}
inline uint gui::element::kid_ID(uint _i) const {
	assert(_i < m_kids.size());
	return m_kids[_i];
}

// gui::element::info
