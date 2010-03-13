/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2010 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

#ifndef GWL_WNDPROC
#	define GWL_WNDPROC			(-4)
#endif // GWL_WNDPROC

// _private

static bool _null_hittest(const short2&)
{
	return true;
}

struct sensor::_private
{
	_private(sensor &_sensor)
	:
		m_hittest(&_null_hittest)
	{}
	virtual ~_private()
	{}

	void add_key_state(uint _code, bool _state)
	{
		key l_key = { _code, _state };
		m_keys.push_back(l_key); 
	}
	virtual uint key_count() const
	{
		return m_keys.size();
	}
	virtual void key_state(uint _i, uint &_code, bool &_state) const
	{
		_code = m_keys[_i].code;
		_state = m_keys[_i].state;
	}
	virtual void reset_keys()
	{
		m_keys.resize(0);
	}

	void set_mouse_state(const short2 &_point, bool _button)
	{
		m_mouse.point = _point;
		m_mouse.button = _button;
	}
	virtual void mouse_state(short2 &_point, bool &_button) const
	{
		_point = m_mouse.point;
		_button = m_mouse.button;
	}

	void set_hittest(const hittest &_hittest)
	{
		m_hittest = _hittest;
	}
	bool do_hittest(const short2 &_point)
	{
		return m_hittest(_point);
	}

private:
	struct key { uint code; bool state; };
	array_<key> m_keys;
	struct mouse { short2 point; bool button; };
	mouse m_mouse;
	hittest m_hittest;
};

// win_sensor

struct _win_sensor : sensor::_private
{
	_win_sensor(sensor &_sensor, HWND _window)
	:
		sensor::_private(_sensor), m_window(_window), next_p(0)
	{
		next_p = first_p;
		first_p = this;

		m_oldwndproc = (WNDPROC)SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)_wndproc);
	}
	virtual ~_win_sensor()
	{
		_win_sensor** l_it = &first_p;
		while (*l_it)
		{
			if ((*l_it) == this)
			{
				*l_it = next_p;
				break;
			}
			l_it = &((*l_it)->next_p);
		}

		SetWindowLongPtr(m_window, GWL_WNDPROC, (LONG_PTR)m_oldwndproc);
	}

	void mouse_state(short2 &_point, bool &_button) const
	{
		super::mouse_state(_point, _button);

		POINT l_p;
		if (GetCursorPos(&l_p))
		{
			ScreenToClient(m_window, &l_p);
			_point.x = (s16)l_p.x;
			_point.y = (s16)l_p.y;
		}
	}

private:
	HWND m_window;
	static _win_sensor *first_p; _win_sensor *next_p;
	WNDPROC m_oldwndproc;
	static long _stdcall _wndproc(HWND _window, uint _message, uint _wparam, uint _lparam)
	{
		_win_sensor* l_it = _win_sensor::first_p;
		while (l_it)
		{
			_win_sensor &l_win_sensor = *l_it;
			if (l_win_sensor.m_window == _window)
			{
				return l_win_sensor.m_wndproc(_message, _wparam, _lparam);
			}
			l_it = l_win_sensor.next_p;
		}

		return 1;
	}
	long m_wndproc(uint _message, uint _wparam, uint _lparam)
	{
		switch (_message)
		{
			case WM_LBUTTONDOWN :
			{
				short2 l_point(LOWORD(_lparam), HIWORD(_lparam));
				set_mouse_state(l_point, true);
				if (do_hittest(l_point)) return 0;
				break;
			}
			case WM_LBUTTONUP :
			{
				short2 l_point(LOWORD(_lparam), HIWORD(_lparam));
				set_mouse_state(l_point, false);
				if (do_hittest(l_point)) return 0;
				break;
			}
			case WM_MOUSEMOVE :
			{
				short2 l_point(LOWORD(_lparam), HIWORD(_lparam));
				set_mouse_state(l_point, _wparam & MK_LBUTTON);
				if (do_hittest(l_point)) return 0;
				break;
			}
		}

		return (long)CallWindowProc(m_oldwndproc, m_window, (UINT)_message, _wparam, _lparam);
	}
};

_win_sensor *_win_sensor::first_p = 0;

// sensor

sensor::sensor()
:
	m_private(0)
{
}

bool sensor::create(HWND _window)
{
	m_private = new _win_sensor(*this, _window);
	return true;
}
void sensor::destroy()
{
	delete m_private;
	m_private = 0;
}

uint sensor::key_count() const
{
	if (m_private == 0) return 0;
	return m_private->key_count();
}
void sensor::key_state(uint _i, uint &_code, bool &_state) const
{
	if (m_private == 0) return;
	return m_private->key_state(_i, _code, _state);
}
void sensor::reset_keys()
{
	if (m_private == 0) return;
	return m_private->reset_keys();
}
void sensor::mouse_state(short2 &_point, bool &_button) const
{
	if (m_private == 0) return;
	return m_private->mouse_state(_point, _button);
}
void sensor::set_hittest(const hittest &_hittest)
{
	if (m_private == 0) return;
	return m_private->set_hittest(_hittest);
}

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
