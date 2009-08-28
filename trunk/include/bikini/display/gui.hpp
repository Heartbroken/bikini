/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct gui : manager {
	struct et { enum panel_type {
		screen, panel,
		count
	};};
	struct rect {
		typedef sint2 point;
		inline rect();
		inline rect(sint _l, sint _t, uint _w, uint _h);
		inline sint left() const;
		inline sint top() const;
		inline sint right() const;
		inline sint bottom() const;
		inline uint width() const;
		inline uint height() const;
		inline const point& lefttop() const;
		inline const point& rightbottom() const;
		inline const point size() const;
		inline rect& operator = (const rect &_r);
		inline bool operator == (const rect &_r) const;
		inline const rect operator + (const point &_p) const;
		inline const rect operator & (const rect &_r) const;
	private:
		point m_lt, m_rb;
	};
	struct exposer {
		virtual uint create_bitmap(pointer _data);
		virtual uint create_bitmap(const astring &_path);
	};
	struct element : manager::object {
		struct info : manager::object::info {
			typedef gui manager;
			info(uint _type);
		};
		element(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID);
		inline gui& get_gui() const;
		inline const rect& get_rect() const;
		inline void set_rect(const rect &_r);
		inline const color& get_color() const;
		inline void set_color(const color &_c);
		inline bool clip() const;
		inline void set_clip(bool _yes = true);
		inline uint parent_ID() const;
		inline bool has_parent() const;
		inline element& get_parent() const;
		inline const rect abs_rect() const;
		inline const rect clip_rect() const;
		inline void add_kid(uint _ID);
		inline uint kid_count() const;
		inline uint kid_ID(uint _i) const;

		struct polyline {
			typedef real2 point;
			typedef array_<point> points;
			typedef array_<uint> line;
			typedef array_<line> lines;
			inline polyline() : m_lines(1) {}
			inline void add_point(const point &_point) {
				points::iterator l_it = std::find_if(m_points.begin(), m_points.end(), _equal_to(_point));
				if(l_it == m_points.end()) m_lines.back().push_back(m_points.size()), m_points.push_back(_point);
				else m_lines.back().push_back(l_it - m_points.begin());
			}
			inline void new_line() { m_lines.resize(m_lines.size() + 1); }
			inline polyline& operator << (const point &_p) { add_point(_p); return *this; }
		private:
			struct _equal_to {
				const point &p; const real eps;
				inline _equal_to(const point &_p, real _eps = bk::eps) : p(_p), eps(_eps * _eps) {}
				inline bool operator () (const point &_p) { point l_diff = p - _p; return (l_diff | l_diff) < eps; }
			};
			points m_points;
			lines m_lines;
		};
		struct polygon {
			typedef real2 point;
			typedef array_<point> points;
			typedef array_<uint> poly;
			typedef array_<poly> polys;
			inline polygon() : m_polys(1) {}
		private:
			points m_points;
			polys m_polys;
		};
		void draw_polyline(const polyline &_polyline);
		void draw_polygon(const polygon &_polygon);
		virtual bool expose(exposer &_exposer) const;
		virtual bool render(window &_window) const;
	private:
		uint m_parent_dependency;
		rect m_rect; color m_color; bool m_clip;
		array_<uint> m_kids;
	};
	inline uint screen_ID() const;
	gui();
	~gui();
	bool create(const astring &_name);
	void destroy();
	bool expose(exposer &_exposer) const;
	bool render(window &_window) const;
	void resize(window &_window) const;
private:
	uint m_screen_ID;
};

namespace ge { /*--------------------------------------------------------------------------------*/

/// screen
struct screen : gui::element {
	struct info : gui::element::info {
		typedef screen object;
		info();
	};
	screen(const info &_info, gui &_gui);
};

/// panel
struct panel : gui::element {
	struct info : gui::element::info {
		typedef panel object;
		typedef sint a0;
		typedef sint a1;
		typedef uint a2;
		typedef uint a3;
		typedef uint a4;
		info();
	};
	panel(const info &_info, gui &_gui, sint _x, sint _y, uint _w, uint _h, uint _parent_ID);
	bool render(window &_window) const;
};

} /* namespace ge -------------------------------------------------------------------------------*/

#include "gui.inl"