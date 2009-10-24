/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// fsm_

template<typename _O, typename _P>
inline fsm_<_O, _P>::fsm_(owner &_owner, proxy &_proxy, state &_def_state) :
	m_owner(_owner), m_proxy(_proxy), m_curr_state_p(0), m_next_state_p(&_def_state), m_lock_state(false)
{}
template<typename _O, typename _P>
inline fsm_<_O, _P>::~fsm_() {
	if(m_curr_state_p) {
		m_curr_state_p->end(m_owner, m_proxy);
		m_curr_state_p = 0;
	}
}
template<typename _O, typename _P>
inline void fsm_<_O, _P>::update(real _dt) {
	if(m_next_state_p) {
		m_lock_state = true;
		if(m_curr_state_p) m_curr_state_p->end(m_owner, m_proxy);
		m_curr_state_p = m_next_state_p; m_next_state_p = 0;
		m_curr_state_p->begin(m_owner, m_proxy);
		m_lock_state = false;
	}
	if(m_curr_state_p) {
		m_curr_state_p->update(m_owner, m_proxy, _dt);
	}
}
template<typename _O, typename _P>
inline void fsm_<_O, _P>::set_state(state &_state) {
	assert(!m_lock_state);
	if(!m_lock_state) m_next_state_p = &_state;
}
template<typename _O, typename _P>
inline bool fsm_<_O, _P>::state_is(const state &_state) const {
	return m_curr_state_p == &_state;
}

// fsm_<_O, _O>

template<typename _O>
inline fsm_<_O, _O>::fsm_(owner &_owner, state &_def_state) :
	m_owner(_owner), m_curr_state_p(0), m_next_state_p(&_def_state), m_lock_state(false)
{}
template<typename _O>
inline fsm_<_O, _O>::~fsm_() {
	if(m_curr_state_p) {
		m_curr_state_p->end(m_owner);
		m_curr_state_p = 0;
	}
}
template<typename _O>
inline void fsm_<_O, _O>::update(real _dt) {
	if(m_next_state_p) {
		m_lock_state = true;
		if(m_curr_state_p) m_curr_state_p->end(m_owner);
		m_curr_state_p = m_next_state_p; m_next_state_p = 0;
		m_curr_state_p->begin(m_owner);
		m_lock_state = false;
	}
	if(m_curr_state_p) {
		m_curr_state_p->update(m_owner, _dt);
	}
}
template<typename _O>
inline void fsm_<_O, _O>::set_state(state &_state) {
	assert(!m_lock_state);
	if(!m_lock_state) m_next_state_p = &_state;
}
template<typename _O>
inline bool fsm_<_O, _O>::state_is(const state &_state) const {
	return m_curr_state_p == &_state;
}


