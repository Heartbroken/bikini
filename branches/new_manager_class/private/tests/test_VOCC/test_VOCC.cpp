// test_VOCC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//

bool intersection(double x1, double y1, double x2, double y2, double x3, double y3, double x4,double y4, bk::real2 &_p) {
  double d = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
  if (d == 0) return false;
  
  double xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/d;
  double yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/d;
  
  if (xi < bk::min(x1, x2) || xi > bk::max(x1, x2)) return false;
  if (xi < bk::min(x3, x4) || xi > bk::max(x3, x4)) return false;
  _p = bk::real2(xi, yi);

  return true;
}

const bk::real4 interpolate(const bk::real4 &_a, const bk::real4 &_b, bk::real _k)
{
	bk::real4 l_v = _a + (_b - _a) * _k;
	bk::real l_a_w = 1.0 / _a.w(), l_b_w = 1.0 / _b.w();
	l_v.w() = 1.0 / (l_a_w + (l_b_w - l_a_w) * _k);
	return l_v;
}

// occluder

struct occluder
{
	bk::array_<bk::real3> points;
	bk::array_<bk::real4> proj;
	bk::real score;
};
typedef bk::array_<occluder> occluders;

// voccluder

struct voccluder
{
	bk::real4 left, right;
	bk::real score;
};
typedef bk::array_<voccluder> voccluders;

// task0

namespace at { enum application_tasks {
	task0
};}

struct task0 : bk::application::task
{
	// window
	struct window : bk::window
	{
		inline window(task0 &_task, bk::video &_video) :
			bk::window(_video), m_task(_task)
		{}
		void on_mouse_down(const bk::sint2 &_position, bk::uint _button) { m_task.on_mouse_down(_position, _button); }
		void on_mouse_up(const bk::sint2 &_position, bk::uint _button) { m_task.on_mouse_up(_position, _button); }
		void on_mouse_move(const bk::sint2 &_position) { m_task.on_mouse_move(_position); }
	private:
		task0 &m_task;
	};

	struct info : bk::application::task::info
	{
		typedef task0 object;
		inline info() : bk::application::task::info(at::task0) {}
	};

	inline task0(const info &_info, bk::application &_application) :
		bk::application::task(_info, _application)
	{}

	void draw_camera(bk::window &_window) const
	{
		_window.draw_line(400, 585, 400 - 1000, 585 - 1000, bk::color(.5, .5, .5, .5));
		_window.draw_line(400, 585, 400 + 1000, 585 - 1000, bk::color(.5, .5, .5, .5));
		const bk::rect r1(380, 585, 40, 12), r2(390, 575, 20, 10);
		_window.draw_rect(r1.min().x(), r1.min().y(), r1.max().x(), r1.max().y(), bk::black);
		_window.draw_rect(r2.min().x(), r2.min().y(), r2.max().x(), r2.max().y(), bk::black);
	}
	void draw_occluder(bk::window &_window, const occluder &_o) const
	{
		_window.draw_rect((bk::sint)_o.points[0].x(), (bk::sint)_o.points[0].y(), (bk::sint)_o.points[2].x(), (bk::sint)_o.points[2].y(), bk::color(0.7, 0.7, 0.7, 0.5));
	}
	void draw_voccluder(bk::window &_window, const voccluder &_o) const
	{
		bk::color l_color(1.0, 0.0, 0.0, _o.score * 0.9 + 0.1);
		_window.draw_line((bk::sint)_o.left.x(), (bk::sint)_o.left.y(), (bk::sint)_o.right.x(), (bk::sint)_o.right.y(), l_color, 4);
		bk::real2 l_cam(400.0, 585.0);
		bk::real2 l_left(_o.left.x(), _o.left.y()), l_right(_o.right.x(), _o.right.y()), l_p2;
		l_p2 = l_left + bk::normalized(l_left - l_cam) * 1000.0;
		_window.draw_line((bk::sint)l_left.x(), (bk::sint)l_left.y(), (bk::sint)l_p2.x(), (bk::sint)l_p2.y(), l_color);
		l_p2 = l_right + bk::normalized(l_right - l_cam) * 1000.0;
		_window.draw_line((bk::sint)l_right.x(), (bk::sint)l_right.y(), (bk::sint)l_p2.x(), (bk::sint)l_p2.y(), l_color);
	}
	void draw_sizers(bk::window &_window, const occluder &_o) const
	{
		for (bk::uint i = 0, s = _o.points.size(); i < s; ++i)
		{
			const bk::real3 &l_p = _o.points[i];
			bk::rect l_r(bk::sint(l_p.x()) - 3, bk::sint(l_p.y()) - 3, 6, 6);
			_window.draw_rect(l_r.min().x(), l_r.min().y(), l_r.max().x(), l_r.max().y(), bk::green);
		}
	}
	bk::uint add_occluder(bk::sint _x, bk::sint _y, bk::uint _w, bk::uint _h)
	{
		occluder l_o; bk::real l_w05 = _w * 0.5, l_h05 = _h * 0.5;
		l_o.points.push_back(bk::real3(bk::real(_x - l_w05), bk::real(_y - l_h05), bk::real(100)));
		l_o.points.push_back(bk::real3(bk::real(_x - l_w05), bk::real(_y + l_h05), bk::real(100)));
		l_o.points.push_back(bk::real3(bk::real(_x + l_w05), bk::real(_y + l_h05), bk::real(100)));
		l_o.points.push_back(bk::real3(bk::real(_x + l_w05), bk::real(_y - l_h05), bk::real(100)));
		m_occluders.push_back(l_o);
		return m_occluders.size() - 1;
	}
	void on_mouse_down(const bk::sint2 &_position, bk::uint _button)
	{
		if (_button != 0) return;

		const bk::sint2 &l_p = _position;
		if (m_curr_occluder < m_occluders.size())
		{
			const occluder &l_o = m_occluders[m_curr_occluder];
			for (bk::uint i = 0, s = l_o.points.size(); i < s; ++i)
			{
				const bk::real3 &l_p0 = l_o.points[i];
				bk::rect l_r(bk::sint(l_p0.x()) - 3, bk::sint(l_p0.y()) - 3, 6, 6);
				if (l_p.x() > l_r.min().x() && l_p.x() < l_r.max().x() && l_p.y() > l_r.min().y() && l_p.y() < l_r.max().y())
				{
					m_drag_type = 2 + i;
					m_drag_point = l_p;
					return;
				}
			}
		}
		for (bk::uint i = 0, s = m_occluders.size(); i < s; ++i)
		{
			const occluder &l_o = m_occluders[i];
			bk::sint l_x = bk::sint(l_o.points[0].x());
			bk::sint l_y = bk::sint(l_o.points[0].y());
			bk::sint l_w = bk::sint(l_o.points[2].x() - l_o.points[0].x());
			bk::sint l_h = bk::sint(l_o.points[2].y() - l_o.points[0].y());
			bk::rect l_r(l_x, l_y, l_w, l_h);
			if (l_p.x() > l_r.min().x() && l_p.x() < l_r.max().x() && l_p.y() > l_r.min().y() && l_p.y() < l_r.max().y())
			{
				m_curr_occluder = i;
				m_drag_type = 1;
				m_drag_point = l_p;
				return;
			}
		}
		m_curr_occluder = bk::bad_ID;
		m_drag_type = 0;
	}
	void on_mouse_up(const bk::sint2 &_position, bk::uint _button)
	{
		if (_button == 0)
		{
			m_drag_type = 0;
		}
		else if (_button == 1)
		{
			HMENU l_popup = GetSubMenu(m_menu, 0);
			RECT l_wrect; GetWindowRect(m_wnd, &l_wrect);
			bk::sint l_command = TrackPopupMenu(l_popup, TPM_RETURNCMD, l_wrect.left + _position.x(), l_wrect.top + _position.y(), 0, m_wnd, 0);
			switch (l_command)
			{
				case ID_POPUP_OPTIONS : {
				} break;
				case ID_OCCLUDERS_ADD : {
					m_curr_occluder = add_occluder(_position.x(), _position.y(), 40, 40);
				} break;
				case ID_OCCLUDERS_REMOVE : {
					if (m_curr_occluder < m_occluders.size())
					{
						m_occluders.erase(m_occluders.begin() + m_curr_occluder);
						m_curr_occluder = bk::bad_ID;
					}
				} break;
			}
		}
	}
	void on_mouse_move(const bk::sint2 &_position)
	{
		const bk::real l_min = 10.0;
		bk::real3 l_shift(_position.x() - m_drag_point.x(), _position.y() - m_drag_point.y(), 0);
		if (m_curr_occluder < m_occluders.size())
		{
			occluder &l_o = m_occluders[m_curr_occluder];
			switch (m_drag_type)
			{
				case 1 : {
					l_o.points[0] += l_shift;
					l_o.points[1] += l_shift;
					l_o.points[2] += l_shift;
					l_o.points[3] += l_shift;
				} break;
				case 2 : {
					bk::real3 l_res = l_o.points[0] + l_shift;
					if(l_res.x() > l_o.points[2].x() - l_min) l_shift.x() = l_o.points[2].x() - l_o.points[0].x() - l_min;
					if(l_res.y() > l_o.points[2].y() - l_min) l_shift.y() = l_o.points[2].y() - l_o.points[0].y() - l_min;
					l_o.points[0] += l_shift;
					l_o.points[1].x() += l_shift.x();
					l_o.points[3].y() += l_shift.y();
				} break;
				case 3 : {
					bk::real3 l_res = l_o.points[1] + l_shift;
					if(l_res.x() > l_o.points[3].x() - l_min) l_shift.x() = l_o.points[3].x() - l_o.points[1].x() - l_min;
					if(l_res.y() < l_o.points[3].y() + l_min) l_shift.y() = l_o.points[3].y() - l_o.points[1].y() + l_min;
					l_o.points[1] += l_shift;
					l_o.points[0].x() += l_shift.x();
					l_o.points[2].y() += l_shift.y();
				} break;
				case 4 : {
					bk::real3 l_res = l_o.points[2] + l_shift;
					if(l_res.x() < l_o.points[0].x() + l_min) l_shift.x() = l_o.points[0].x() - l_o.points[2].x() + l_min;
					if(l_res.y() < l_o.points[0].y() + l_min) l_shift.y() = l_o.points[0].y() - l_o.points[2].y() + l_min;
					l_o.points[2] += l_shift;
					l_o.points[3].x() += l_shift.x();
					l_o.points[1].y() += l_shift.y();
				} break;
				case 5 : {
					bk::real3 l_res = l_o.points[3] + l_shift;
					if(l_res.x() < l_o.points[1].x() + l_min) l_shift.x() = l_o.points[1].x() - l_o.points[3].x() + l_min;
					if(l_res.y() > l_o.points[1].y() - l_min) l_shift.y() = l_o.points[1].y() - l_o.points[3].y() - l_min;
					l_o.points[3] += l_shift;
					l_o.points[2].x() += l_shift.x();
					l_o.points[0].y() += l_shift.y();
				} break;
			}
		}
		m_drag_point += bk::sint2((bk::sint)l_shift.x(), (bk::sint)l_shift.y());
	}
	bool point_occluded(const bk::real4 &_p, const voccluder &_o)
	{
		if (_p.x() < _o.left.x() - bk::eps || _p.x() > _o.right.x() + bk::eps) return false;
		bk::real l_k = (_p.x() - _o.left.x()) / (_o.right.x() - _o.left.x());
		bk::real l_z = _o.left.z() + (_o.right.z() - _o.left.z()) * l_k;
		return _p.z() > l_z - bk::eps;
	}
	bool create_voccluder(const occluder &_o, voccluder &_v)
	{
		bool l_skip = true;
		_v.left.x() = bk::infinity; _v.right.x() = -bk::infinity;
		for (bk::uint i = 0, s = _o.proj.size(); i < s; ++i)
		{
			const bk::real4 &l_p = _o.proj[i];
			if (l_p.z() < 0 || l_p.z() > 1.0) continue;
			if (l_p.x() < _v.left.x()) _v.left = l_p;
			if (l_p.x() > _v.right.x()) _v.right = l_p;
			l_skip = false;
		}
		if (!l_skip && _v.left.x() < -1.0)
		{
			if (_v.right.x() < -1.0) l_skip = true;
			else _v.left = interpolate(_v.right, _v.left, (_v.right.x() + 1.0) / (_v.right.x() - _v.left.x()));
		}
		if (!l_skip && _v.right.x() > 1.0)
		{
			if (_v.left.x() > 1.0) l_skip = true;
			else _v.right = interpolate(_v.left, _v.right, (1.0 - _v.left.x()) / (_v.right.x() - _v.left.x()));
		}
		_v.score = (_v.right.x() - _v.left.x()) * 0.5 * (_v.left.y() + _v.right.y()) * (1.0 - 0.5 * (_v.left.z() + _v.right.z()));
		return !l_skip;
	}
	bool merge_voccluders(voccluder &_o0, voccluder &_o1, voccluder &_v)
	{
		if (_o0.score == 0 || _o1.score == 0) return false;
		bool l_skip = true;
		if (_o0.left.x() < _o1.left.x() - bk::eps)
		{
			if (_o0.right.x() < _o1.right.x() - bk::eps)
			{
				_v.left = _o0.left; _v.right = _o1.right;
				l_skip = false;
			}
			else if (_o0.right.x() > _o1.right.x() + bk::eps)
			{
				bk::real4 l_left = interpolate(_o0.right, _o0.left, (_o0.right.x() - _o1.left.x()) / (_o0.right.x() - _o0.left.x()));
				bk::real4 l_right = interpolate(_o0.right, _o0.left, (_o0.right.x() - _o1.right.x()) / (_o0.right.x() - _o0.left.x()));
				if (l_left.z() < _o1.left.z() + bk::eps && l_right.z() < _o1.right.z() + bk::eps) _o1.score = 0;
			}
			else
			{
				bk::real4 l_left = interpolate(_o0.right, _o0.left, (_o0.right.x() - _o1.left.x()) / (_o0.right.x() - _o0.left.x()));
				if (l_left.z() < _o1.left.z() + bk::eps && _o0.right.z() < _o1.right.z() + bk::eps) _o1.score = 0;
			}
		}
		else if (_o0.left.x() > _o1.left.x() + bk::eps)
		{
			if (_o0.right.x() > _o1.right.x() + bk::eps)
			{
				_v.left = _o1.left; _v.right = _o0.right;
				l_skip = false;
			}
			else if (_o0.right.x() < _o1.right.x() - bk::eps)
			{
				bk::real4 l_left = interpolate(_o1.right, _o1.left, (_o1.right.x() - _o0.left.x()) / (_o1.right.x() - _o1.left.x()));
				bk::real4 l_right = interpolate(_o1.right, _o1.left, (_o1.right.x() - _o0.right.x()) / (_o1.right.x() - _o1.left.x()));
				if (l_left.z() < _o0.left.z() + bk::eps && l_right.z() < _o0.right.z() + bk::eps) _o0.score = 0;
			}
			else
			{
				bk::real4 l_left = interpolate(_o1.right, _o1.left, (_o1.right.x() - _o0.left.x()) / (_o1.right.x() - _o1.left.x()));
				if (l_left.z() < _o0.left.z() + bk::eps && _o1.right.z() < _o0.right.z() + bk::eps) _o0.score = 0;
			}
		}
		else
		{
			if (_o0.right.x() < _o1.right.x() - bk::eps)
			{
				bk::real4 l_right = interpolate(_o1.right, _o1.left, (_o1.right.x() - _o0.right.x()) / (_o1.right.x() - _o1.left.x()));
				if (_o1.left.z() < _o0.left.z() + bk::eps && l_right.z() < _o0.right.z() + bk::eps) _o0.score = 0;
			}
			else if (_o0.right.x() > _o1.right.x() + bk::eps)
			{
				bk::real4 l_right = interpolate(_o0.right, _o0.left, (_o0.right.x() - _o1.right.x()) / (_o0.right.x() - _o0.left.x()));
				if (_o0.left.z() < _o1.left.z() + bk::eps && l_right.z() < _o1.right.z() + bk::eps) _o1.score = 0;
			}
			else
			{
				if (_o0.left.z() < _o1.left.z() + bk::eps && _o0.right.z() < _o1.right.z() + bk::eps) _o1.score = 0;
				else if (_o1.left.z() < _o0.left.z() + bk::eps && _o1.right.z() < _o0.right.z() + bk::eps) _o0.score = 0;
			}
		}
		if (!l_skip)
		{
			bk::real l_max_z = _o0.left.z(), l_max_w = _o0.left.w();
			if (l_max_z < _o0.right.z()) { l_max_z = _o0.right.z(); l_max_w = _o0.right.w(); }
			if (l_max_z < _o1.left.z()) { l_max_z = _o1.left.z(); l_max_w = _o1.left.w(); }
			if (l_max_z < _o1.right.z()) { l_max_z = _o1.right.z(); l_max_w = _o1.right.w(); }
			_v.left.z() = _v.right.z() = l_max_z;
			_v.left.w() = _v.right.w() = l_max_w;
			_v.score = (_v.right.x() - _v.left.x()) * 0.5 * (_v.left.y() + _v.right.y()) * (1.0 - 0.5 * (_v.left.z() + _v.right.z()));
		}
		return !l_skip;
	}
	void add_voccluder(const voccluder &_o)
	{
		for (bk::uint i = 0, s = m_voccluders.size(); i < s; ++i)
		{
			const voccluder &l_o = m_voccluders[i];
			if (l_o.score <= 0) continue;
			if (_o.right.x() < l_o.left.x() - bk::eps || l_o.right.x() < _o.left.x() - bk::eps) continue;
			//if ((_o.left.x() < l_o.left.x() - bk::eps && _o.right.x() < l_o.right.x() - bk::eps) ||
			//	(l_o.left.x() < _o.left.x() - bk::eps && l_o.right.x() < _o.right.x() - bk::eps))
			//{
			//	bk::uint l_i0 = s, l_i1 = i;
			//	bk::uint l_pair = (s << 16) | i;
			//	m_mergequeue.push_back(l_pair);
			//}
			bk::uint l_i0 = s, l_i1 = i;
			bk::uint l_pair = (s << 16) | i;
			m_mergequeue.push_back(l_pair);
		}
		m_voccluders.push_back(_o);
	}
	void add_voccluder(const occluder &_o)
	{
		voccluders l_new;
		bool l_skip = true;
		bk::real4 l_left, l_right;
		l_left.x() = bk::infinity; l_right.x() = -bk::infinity;
		for (bk::uint i = 0, s = _o.proj.size(); i < s; ++i)
		{
			const bk::real4 &l_p = _o.proj[i];
			if (l_p.z() < 0 || l_p.z() > 1.0) continue;
			if (l_p.x() < l_left.x()) l_left = l_p;
			if (l_p.x() > l_right.x()) l_right = l_p;
			l_skip = false;
		}
		//if (!l_skip)
		//{
		//	if (l_left.z() > l_right.z())
		//	{
		//		l_right.z() = l_left.z();
		//		l_right.w() = l_left.w();
		//	}
		//	if (l_right.z() > l_left.z())
		//	{
		//		l_left.z() = l_right.z();
		//		l_left.w() = l_right.w();
		//	}
		//}
		if (!l_skip && l_left.x() < -1.0)
		{
			if (l_right.x() < -1.0) l_skip = true;
			else l_left = interpolate(l_right, l_left, (l_right.x() + 1.0) / (l_right.x() - l_left.x()));
		}
		if (!l_skip && l_right.x() > 1.0)
		{
			if (l_left.x() > 1.0) l_skip = true;
			else l_right = interpolate(l_left, l_right, (1.0 - l_left.x()) / (l_right.x() - l_left.x()));
		}
		for (bk::uint i = 0, s = m_voccluders.size(); i < s; ++i)
		{
			const voccluder &l_o = m_voccluders[i];
			bool l_left_occluded = point_occluded(l_left, l_o);
			bool l_right_occluded = point_occluded(l_right, l_o);
			if (l_left_occluded && l_right_occluded)
			{
				l_skip = true; break;
			}
			else if(l_left_occluded)
			{
				for (bk::uint i = 0, s = _o.proj.size(); i < s; ++i)
				{
					const bk::real4 &l_p = _o.proj[i];
					if (l_p.z() < 0 || l_p.z() > 1.0) continue;
					if (point_occluded(l_p, l_o) && l_p.z() < l_left.z())
					{
						l_left = l_p;
					}
				}
				if (l_left.z() > l_right.z())
				{
					bk::real4 l_middle = interpolate(l_right, l_left, (l_o.right.x() - l_right.x()) / (l_left.x() - l_right.x()));
					l_left = l_o.left;
					l_left.z() = l_right.z() = l_middle.z();
					l_left.w() = l_right.w() = l_middle.w();
				}
				else
				{
					l_left = interpolate(l_right, l_left, (l_o.left.x() - l_right.x()) / (l_left.x() - l_right.x()));
					if (l_left.z() < l_o.left.z())
					{
						l_left.z() = l_o.left.z();
						l_left.w() = l_o.left.w();
					}
				}
				//bk::real4 l_new_middle = interpolate(l_right, l_left, (l_o.right.x() - l_right.x()) / (l_left.x() - l_right.x()));
				//l_left = l_o.left;
				//if (l_left.z() > l_new_middle.z())
				//{
				//	l_new_middle.z() = l_left.z();
				//	l_new_middle.w() = l_left.w();
				//}
				//if (l_right.z() > l_new_middle.z())
				//{
				//	l_new_middle.z() = l_right.z();
				//	l_new_middle.w() = l_right.w();
				//}
				//l_left.z() = l_right.z() = l_new_middle.z();
				//l_left.w() = l_right.w() = l_new_middle.w();
			}
			else if(l_right_occluded)
			{
				for (bk::uint i = 0, s = _o.proj.size(); i < s; ++i)
				{
					const bk::real4 &l_p = _o.proj[i];
					if (l_p.z() < 0 || l_p.z() > 1.0) continue;
					if (point_occluded(l_p, l_o) && l_p.z() < l_right.z())
					{
						l_right = l_p;
					}
				}
				if (l_right.z() > l_left.z())
				{
					bk::real4 l_middle = interpolate(l_left, l_right, (l_o.left.x() - l_left.x()) / (l_right.x() - l_left.x()));
					l_right = l_o.right;
					l_left.z() = l_right.z() = l_middle.z();
					l_left.w() = l_right.w() = l_middle.w();
				}
				else
				{
					l_right = interpolate(l_left, l_right, (l_o.right.x() - l_left.x()) / (l_right.x() - l_left.x()));
					if (l_right.z() < l_o.right.z())
					{
						l_right.z() = l_o.right.z();
						l_right.w() = l_o.right.w();
					}
				}
				//bk::real4 l_new_middle = interpolate(l_left, l_right, (l_o.left.x() - l_left.x()) / (l_right.x() - l_left.x()));
				//l_right = l_o.right;
				//if (l_left.z() > l_new_middle.z())
				//{
				//	l_new_middle.z() = l_left.z();
				//	l_new_middle.w() = l_left.w();
				//}
				//if (l_right.z() > l_new_middle.z())
				//{
				//	l_new_middle.z() = l_right.z();
				//	l_new_middle.w() = l_right.w();
				//}
				//l_left.z() = l_right.z() = l_new_middle.z();
				//l_left.w() = l_right.w() = l_new_middle.w();
			}
		}
		if (!l_skip)
		{
			voccluder l_o;
			l_o.left = l_left; l_o.right = l_right;
			l_o.score = (l_o.right.x() - l_o.left.x()) * 0.5 * (l_o.right.y() + l_o.left.y() + 2.0) * (1.0 - 0.5 * (l_o.right.z() + l_o.left.z()));
			//l_o.score = 0.5 * (l_o.right.z() + l_o.left.z());//(l_o.right.x() - l_o.left.x()) * (1.0 - 0.5 * (l_o.right.z() + l_o.left.z()));
			//l_o.score = bk::min(l_o.right.z(), l_o.left.z());//(l_o.right.x() - l_o.left.x()) * (1.0 - 0.5 * (l_o.right.z() + l_o.left.z()));
			l_new.push_back(l_o);
		}
		while (!l_new.empty())
		{
			voccluders::iterator l_insert = m_voccluders.begin();
			for (bk::uint i = 0, s = m_voccluders.size(); i < s; ++i)
			{
				if (m_voccluders[i].score > l_new.back().score) break;
				++l_insert;
			}
			m_voccluders.insert(l_insert, l_new.back());
			l_new.pop_back();
		}
	}
	void project_occluder(occluder &_o, const bk::r4x4 &_m)
	{
		_o.proj.resize(0);
		_o.score = bk::infinity;
		for (bk::uint i = 0, s = _o.points.size(); i < s; ++i)
		{
			const bk::real3 &l_p3 = _o.points[i];
			bk::real4 l_p4(l_p3.x(), l_p3.y(), l_p3.z(), 1.0);
			l_p4 = l_p4 * _m;
			bk::real l_w = 1.0 / l_p4.w();
			l_p4.x() *= l_w;
			l_p4.y() *= l_w;
			l_p4.z() *= l_w;
			_o.proj.push_back(l_p4);
			if (l_p4.z() > 0 && l_p4.z() < 1.0)
			{
				if (_o.score > l_p4.z()) _o.score = l_p4.z();
			}
		}
	}
	void unproject_voccluder(voccluder &_o, const bk::r4x4 &_m)
	{
		_o.left.x() *= _o.left.w();
		_o.left.y() *= _o.left.w();
		_o.left.z() *= _o.left.w();
		_o.left = _o.left * _m;
		_o.right.x() *= _o.right.w();
		_o.right.y() *= _o.right.w();
		_o.right.z() *= _o.right.w();
		_o.right = _o.right * _m;
	}
	void sort_occluders()
	{
		occluders l_new;
		for (bk::uint i = 0, s = m_occluders.size(); i < s; ++i)
		{
			occluders::iterator l_insert = l_new.begin();
			const occluder &l_o = m_occluders[i];
			for (bk::uint i = 0, s = l_new.size(); i < s; ++i)
			{
				if (l_new[i].score >= l_o.score) break;
				++l_insert;
			}
			l_new.insert(l_insert, l_o);
		}
		m_occluders = l_new;
	}

	void main()
	{
		bk::video l_video;
		l_video.create();
		window l_window(*this, l_video);
		l_window.create(800, 600, false);
		l_window.set_caption("Virtual Occluder Demo ");
		l_window.show();
		l_window.clear();
		//
		m_wnd = l_window.get_handle();
		m_menu = LoadMenu(GetModuleHandleA(0), MAKEINTRESOURCE(IDR_MENU1));
		//
		bk::r4x4 l_view
		(
			bk::real4(1.0,   0.0,  0.0, 0.0),
			bk::real4(0.0,   0.0,  1.0, 0.0),
			bk::real4(0.0,  -1.0,  0.0, 0.0),
			bk::real4(400.0, 585.0, 50.0, 1.0)
		);
		l_view = bk::inverse(l_view);
		bk::real zn = 10.0, zf = 585.0, w = 20.0, h = 20.0;
		bk::r4x4 l_proj
		(
			bk::real4(2.0*zn/w,      0.0,           0.0, 0.0),
			bk::real4(	   0.0, 2.0*zn/h,           0.0, 0.0),
			bk::real4(     0.0,      0.0,    zf/(zf-zn), 1.0),
			bk::real4(     0.0,      0.0,-zn*zf/(zf-zn), 0.0)
		);
		m_viewproj = l_view * l_proj;
		m_iviewproj = bk::inverse(m_viewproj);
		//
		m_drag_type = 0;
		m_curr_occluder = add_occluder(400, 300, 40, 40);
		m_curr_occluder = add_occluder(700, 300, 40, 40);
		//
		bk::ticker l_ticker(bk::real(1.0/30.0));
		bk::rbig l_time = bk::sys_time();
		while (true)
		{
			bk::real l_dt = bk::real(bk::sys_time() - l_time); l_time = bk::sys_time();
			l_dt = bk::min(l_dt, bk::real(0.3));
			l_video.update(l_dt);
			if(!l_window.update(l_dt)) break;
			// do something useful
			l_window.clear(bk::cf::all, bk::white);
			l_window.begin();

			bk::rbig l_time = bk::sys_time();

			for (bk::uint i = 0, s = m_occluders.size(); i < s; ++i)
			{
				project_occluder(m_occluders[i], m_viewproj);
			}

			occluders l_old = m_occluders;
			sort_occluders();

			m_voccluders.resize(0);
			//m_mergequeue.resize(0);
			for (bk::uint i = 0, s = m_occluders.size(); i < s; ++i)
			{
				const occluder &l_o = m_occluders[i];
				add_voccluder(l_o);
				//voccluder l_o;
				//if (create_voccluder(m_occluders[i], l_o))
				//{
				//	add_voccluder(l_o);
				//}
			}
////			for (bk::uint i = 0; i < m_mergequeue.size(); ++i)
//			while (!m_mergequeue.empty())
//			{
//				bk::uint l_pair = m_mergequeue.back();
//				m_mergequeue.pop_back();
//				bk::uint l_i0 = l_pair&0xffff, l_i1 = l_pair>>16;
//				voccluder &l_o0 = m_voccluders[l_i0];
//				voccluder &l_o1 = m_voccluders[l_i1];
//				if (l_o0.score == 0 || l_o1.score == 0) continue;
//				voccluder l_o;
//				if (merge_voccluders(l_o0, l_o1, l_o))
//				{
//					//add_voccluder(l_o);
//					bk::uint l_pair0 = (m_voccluders.size() << 16) | l_i0;
//					m_mergequeue.push_back(l_pair0);
//					bk::uint l_pair1 = (m_voccluders.size() << 16) | l_i1;
//					m_mergequeue.push_back(l_pair1);
//					m_voccluders.push_back(l_o);
//				}
//			}

			m_occluders = l_old;

			bk::uint l_vocc_count = 0;
			bk::real l_max_vocc_score = 0;

			for (bk::uint i = 0, s = m_voccluders.size(); i < s; ++i)
			{
				voccluder &l_o = m_voccluders[i];
				if (l_o.score == 0) continue;
				unproject_voccluder(l_o, m_iviewproj);

				++l_vocc_count;
				if (l_max_vocc_score < l_o.score) l_max_vocc_score = l_o.score;
			}

			l_time = bk::sys_time() - l_time;

			std::cout << "OCC: " << m_occluders.size() << " VOCC: " << l_vocc_count << " ";
			std::cout << "Time: " << l_time * 1000.0 << " msec\n";

			draw_camera(l_window);
			for (bk::uint i = 0, s = m_occluders.size(); i < s; ++i)
			{
				draw_occluder(l_window, m_occluders[i]);
			}
			for (bk::uint i = 0, s = m_voccluders.size(); i < s; ++i)
			{
				if (m_voccluders[i].score == 0) continue;
				m_voccluders[i].score /= l_max_vocc_score;
				draw_voccluder(l_window, m_voccluders[i]);
			}
			if (m_curr_occluder < m_occluders.size())
			{
				draw_sizers(l_window, m_occluders[m_curr_occluder]);
			}

			l_window.flush_drawings();
			l_window.end();
			l_window.present();
			//
			l_ticker.sync();
		}
		//
		DestroyMenu(m_menu);
		//
		l_window.destroy();
		l_video.destroy();
	}

private:
	bk::r4x4 m_viewproj, m_iviewproj;
	occluders m_occluders;
	bk::uint m_curr_occluder;
	voccluders m_voccluders;
	bk::uint_array m_mergequeue;
	//
	bk::uint m_drag_type;
	bk::sint2 m_drag_point;
	HMENU m_menu;
	HWND m_wnd;
};

int _tmain(int argc, _TCHAR* argv[])
{
	bk::application l_app;
	task0::info l_task0;
	l_app.spawn(l_task0);
	l_app.run();
	return 0;
}

