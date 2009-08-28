/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

template<typename _Owner, typename _Proxy = _Owner> struct fsm_ {
	typedef _Owner owner;
	typedef _Proxy proxy;
	struct state {
		typedef void (_Proxy::*begin_fn)(owner &_owner);
		typedef void (proxy::*update_fn)(owner &_owner, real);
		typedef void (proxy::*end_fn)(owner &_owner);
		inline state(const begin_fn &_begin, const update_fn &_update, const end_fn &_end) : m_begin(_begin), m_update(_update), m_end(_end) {}
	private:
		friend fsm_;
		inline void begin(owner &_owner, proxy &_proxy) { (_proxy.*m_begin)(_owner); }
		inline void update(owner &_owner, proxy &_proxy, real _dt) { (_proxy.*m_update)(_owner, _dt); }
		inline void end(owner &_owner, proxy &_proxy) { (_proxy.*m_end)(_owner); }
		begin_fn m_begin; update_fn m_update; end_fn m_end;
	};
	inline fsm_(owner &_owner, proxy &_proxy, state &_def_state);
	inline ~fsm_();
	inline void update(real _dt);
	inline void set_state(state &_state);
	inline bool state_is(const state &_state) const;
private:
	owner &m_owner;
	proxy &m_proxy;
	state *m_curr_state_p, *m_next_state_p;
	bool m_lock_state;
};

template<typename _Owner> struct fsm_<_Owner, _Owner> {
	typedef _Owner owner;
	struct state {
		typedef void (owner::*begin_fn)();
		typedef void (owner::*update_fn)(real);
		typedef void (owner::*end_fn)();
		inline state(const begin_fn &_begin, const update_fn &_update, const end_fn &_end) : m_begin(_begin), m_update(_update), m_end(_end) {}
	private:
		friend fsm_;
		inline void begin(owner &_owner) { (_owner.*m_begin)(); }
		inline void update(owner &_owner, real _dt) { (_owner.*m_update)(_dt); }
		inline void end(owner &_owner) { (_owner.*m_end)(); }
		begin_fn m_begin; update_fn m_update; end_fn m_end;
	};
	inline fsm_(owner &_owner, state &_def_state);
	inline ~fsm_();
	inline void update(real _dt);
	inline void set_state(state &_state);
	inline bool state_is(const state &_state) const;

private:
	owner &m_owner;
	state *m_curr_state_p, *m_next_state_p;
	bool m_lock_state;
};

#include "fsm.inl"