/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

// triangulator

struct triangulator {
	typedef real2 point;
	typedef array_<point> points;
	typedef array_<uint> poly;
	struct vertex { uint p, e0, e1; bool n; };
	typedef array_<vertex> vertices;
	typedef array_<uint> point_map;
	struct edge { uint v0, v1, ne, te; };
	typedef array_<edge> edges;
	typedef array_<uint> edge_list;
	struct trapezoid { uint v0, v0c, v1, v1c, e0, e1; };
	typedef array_<trapezoid> trapezoids;
	inline uint tri_count() const { return m_tris.size() / 3; }
	inline const uint* get_tris() const { return &m_tris[0]; }
	bool build(const points &_points, const poly &_poly) {
		if(_points.empty() || _poly.empty()) return false;
		lines.resize(0);
		m_create_edges(_points, _poly);
		m_split_monotone();
		m_triangulate_parts();
		return true;
	}
	array_<point> lines;
private:
	const point *m_points;
	vertices m_vertices; point_map m_point_map;
	edges m_edges; edge_list m_edge_list; trapezoids m_trapezoids;
	array_<uint> m_monotone, m_tris;
	void m_create_edges(const points &_points, const poly &_poly) {
		m_edges.resize(0); m_edge_list.resize(0); m_trapezoids.resize(0);
		m_monotone.resize(0); m_tris.resize(0);
		m_vertices.resize(0);
		m_points = &_points[0]; // @@@
		assert(_poly.size() > 1 && _poly.size() % 2 == 0);
		for(uint i = 1, s = _poly.size(); i < s; i += 2) {
			vertex l_v; l_v.p = _poly[i]; l_v.e0 = l_v.e1 = bad_ID; l_v.n = false;
			const real2 &l_p = _points[l_v.p];
			uint l_i = m_vertices.size();
			for(uint i = 0, s = m_vertices.size(); i < s; ++i) {
				const real2 &l_p0 = _points[m_vertices[i].p];
				if((l_p.x() < l_p0.x()) || (abs(l_p.x() - l_p0.x()) < eps && (l_p.y() < l_p0.y()))) {
					l_i = i; break;
				}
			}
			m_vertices.insert(m_vertices.begin() + l_i, l_v);
		}
		m_point_map.resize(_points.size());
		for(uint i = 0, s = m_vertices.size(); i < s; ++i) {
			m_point_map[m_vertices[i].p] = i;
		}
		for(uint i = 1, s = _poly.size(); i < s; i += 2) {
			uint l_i0 = _poly[i - 1], l_i1 = _poly[i];
			edge l_edge; l_edge.v0 = m_point_map[l_i0]; l_edge.v1 = m_point_map[l_i1]; l_edge.ne = l_edge.te = bad_ID;
			vertex &l_v0 = m_vertices[l_edge.v0], &l_v1 = m_vertices[l_edge.v1];
			assert(l_v0.e1 == bad_ID && l_v1.e0 == bad_ID);
			l_v0.e1 = l_v1.e0 = m_edges.size();
			if(l_v0.e0 != bad_ID) m_edges[l_v0.e0].ne = l_v0.e1;
			if(l_v1.e1 != bad_ID) l_edge.ne = l_v1.e1;
			m_edges.push_back(l_edge);
		}
	}
	void m_split_monotone() {
		for(uint i = 0, s = m_vertices.size(); i < s; ++i) {
			uint l_vs = i, l_ve = i;
			const real l_ps_x = m_points[m_vertices[l_vs].p].x();
			for(uint s = m_vertices.size(); l_ve + 1 < s; ++l_ve) {
				const real l_pe_x = m_points[m_vertices[l_ve + 1].p].x();
				if(abs(l_ps_x - l_pe_x) > eps) break;
			}
			m_close_trapezoids(l_vs, l_ve);
			m_remove_edges(l_vs, l_ve);
			m_add_edges(l_vs, l_ve);
			m_open_trapezoids(l_vs, l_ve);
			i = l_ve;
		}
	}
	void m_triangulate_parts() {
		for(uint i = 0, s = m_edges.size(); i < s; ++i) {
			edge &l_e = m_edges[i];
			if(l_e.ne == bad_ID) continue;
			m_monotone.resize(0);
			uint l_ei = l_e.ne; l_e.ne = bad_ID;
			while(l_ei != bad_ID) {
				edge &l_e = m_edges[l_ei];
				vertex &l_v0 = m_vertices[l_e.v0], &l_v1 = m_vertices[l_e.v1];
				l_v0.e1 = l_v1.e0 = l_ei;
				// @@@ // Optimize this. Do not do full sorting, but merge two monotone chains
				array_<uint>::iterator l_insert = m_monotone.end();
				for(uint i = 0, s = m_monotone.size(); i < s; ++i) {
					if(l_e.v0 < m_monotone[i]) {
						l_insert = m_monotone.begin() + i;
						break;
					}
				}
				m_monotone.insert(l_insert, l_e.v0);
				// @@@
				l_ei = l_e.ne; l_e.ne = bad_ID;
			}
			m_triangulate_monotone();
		}
		//// test
		//for(uint i = 0, s = m_edges.size(); i < s; ++i) {
		//	const edge &l_e = m_edges[i];
		//	const vertex &l_v0 = m_vertices[l_e.v0], &l_v1 = m_vertices[l_e.v1];
		//	lines.push_back(m_points[l_v0.p]);
		//	lines.push_back(m_points[l_v1.p]);
		//}
	}
	void m_triangulate_monotone() {
		assert(m_monotone.size() > 2);
		array_<uint> l_stack; l_stack.insert(l_stack.end(), m_monotone.begin(), m_monotone.begin() + 2);
		for(uint i = 2, s = m_monotone.size(); i < s; ++i) {
			uint l_vi = m_monotone[i];
			if(m_adjacent_vertices(l_vi, l_stack.front())) {
				const vertex &l_v0 = m_vertices[l_vi];
				bool l_reverse = (m_vertices[l_stack[0]].e0 == l_v0.e1);
				while(l_stack.size() > 1) {
					uint l_v1i = l_stack[0], l_v2i = l_stack[1];
					if(l_reverse) swap(l_v1i, l_v2i);
					const vertex &l_v1 = m_vertices[l_v1i];
					const vertex &l_v2 = m_vertices[l_v2i];
					m_tris.push_back(l_v0.p); m_tris.push_back(l_v1.p); m_tris.push_back(l_v2.p);
					l_stack.erase(l_stack.begin());
				}
				l_stack.push_back(l_vi);
			} else if(m_adjacent_vertices(l_vi, l_stack.back())) {
				const vertex &l_v0 = m_vertices[l_vi];
				const point &l_p0 = m_points[l_v0.p];
				bool l_reverse = (m_vertices[l_stack[l_stack.size() - 1]].e0 == l_v0.e1);
				while(l_stack.size() > 1) {
					uint l_v1i = l_stack[l_stack.size() - 1], l_v2i = l_stack[l_stack.size() - 2];
					if(l_reverse) swap(l_v1i, l_v2i);
					const vertex &l_v1 = m_vertices[l_v1i], &l_v2 = m_vertices[l_v2i];
					const point &l_p1 = m_points[l_v1.p], &l_p2 = m_points[l_v2.p];
					point l_d0 = l_p0 - l_p2, l_d1 = l_p1 - l_p2;
					real l_a0 = atan2(l_d0.y(), l_d0.x()), l_a1 = atan2(l_d1.y(), l_d1.x()), l_a = l_a1 - l_a0;
					while(l_a < 0) l_a += real(2) * pi;
					if(l_a > pi) break;
					m_tris.push_back(l_v0.p); m_tris.push_back(l_v1.p); m_tris.push_back(l_v2.p);
					l_stack.erase(l_stack.end() - 1);
				}
				l_stack.push_back(l_vi);
			} else {
				assert(0);
			}
		}
	}
	bool m_adjacent_vertices(uint _v0, uint _v1) {
		const vertex &l_v = m_vertices[_v0];
		const edge &l_e0 = m_edges[l_v.e0], &l_e1 = m_edges[l_v.e1];
		return l_e0.v0 == _v1 || l_e1.v1 == _v1;
	}
	bool m_vertical_edge(uint _e) {
		const edge &l_e = m_edges[_e];
		const vertex &l_v0 = m_vertices[l_e.v0], &l_v1 = m_vertices[l_e.v1];
		const point &l_p0 = m_points[l_v0.p], &l_p1 = m_points[l_v1.p];
		return abs(l_p0.x() - l_p1.x()) < eps;
	}
	void m_add_edges(uint _vs, uint _ve) {
		for(uint i = _vs; i <= _ve; ++i) {
			uint l_vi = i;
			const vertex &l_v = m_vertices[i];
			const edge &l_e0 = m_edges[l_v.e0];
			const edge &l_e1 = m_edges[l_v.e1];
			uint l_v0i = l_e0.v0, l_v1i = l_e1.v1;
			if(l_vi < l_v0i) m_add_edge(l_v.e0);
			if(l_vi < l_v1i) m_add_edge(l_v.e1);
		}
	}
	void m_add_edge(uint _e) {
		if(m_vertical_edge(_e)) return;
		for(uint i = 0, s = m_edge_list.size(); i < s; ++i) {
			if(m_edge_edge_compare(_e, m_edge_list[i]) < 0) {
				m_edge_list.insert(m_edge_list.begin() + i, _e);
				return;
			}
		}
		m_edge_list.push_back(_e);
	}
	void m_remove_edges(uint _vs, uint _ve) {
		for(uint i = _vs; i <= _ve; ++i) {
			uint l_vi = i;
			const vertex &l_v = m_vertices[i];
			const edge &l_e0 = m_edges[l_v.e0];
			const edge &l_e1 = m_edges[l_v.e1];
			uint l_v0i = l_e0.v0, l_v1i = l_e1.v1;
			if(l_vi > l_v0i) m_remove_edge(l_v.e0);
			if(l_vi > l_v1i) m_remove_edge(l_v.e1);
		}
	}
	void m_remove_edge(uint _e) {
		if(m_vertical_edge(_e)) return;
		for(uint i = 0, s = m_edge_list.size(); i < s; ++i) {
			if(m_edge_list[i] == _e) {
				m_edge_list.erase(m_edge_list.begin() + i);
				break;
			}
		}
	}
	void m_open_trapezoids(uint _vs, uint _ve) {
		for(uint i = _vs; i <= _ve; ++i) {
			uint l_v = i;
			for(uint i = 1, s = m_edge_list.size(); i < s; ++i) {
				uint l_e0 = m_edge_list[i - 1], l_e1 = m_edge_list[i];
				if(m_get_trapezoid(l_e0) != m_get_trapezoid(l_e1)) continue;
				sint l_c0 = m_vertex_edge_compare(l_v, l_e0), l_c1 = m_vertex_edge_compare(l_v, l_e1);
				if(l_c0 >= 0 && l_c1 <= 0) m_open_trapezoid(l_v, l_e0, l_e1);
				if(l_c0 < 0) break;
			}
		}
	}
	void m_open_trapezoid(uint _v, uint _e0, uint _e1) {
		uint l_i = m_get_trapezoid(_e0, _e1);
		if(l_i == bad_ID) {
			l_i = m_trapezoids.size(); m_trapezoids.resize(l_i + 1);
			trapezoid &l_t = m_trapezoids[l_i];
			l_t.v0 = l_t.v1 = bad_ID;
			l_t.v0c = l_t.v1c = 1;
			l_t.e0 = _e0; l_t.e1 = _e1;
		}
		trapezoid &l_t = m_trapezoids[l_i];
		assert(l_t.v0 == bad_ID || l_t.v0 + l_t.v0c == _v);
		if(l_t.v0 == bad_ID) l_t.v0 = _v;
		else l_t.v0c++;
		vertex &l_v = m_vertices[_v];
		const edge &l_e0 = m_edges[l_v.e0], &l_e1 = m_edges[l_v.e1];
		if(l_e0.v0 < _v && l_e1.v1 < _v) l_v.n = true;
	}
	void m_close_trapezoids(uint _vs, uint _ve) {
		for(uint i = _vs; i <= _ve; ++i) {
			uint l_v = i;
			for(uint i = 1, s = m_edge_list.size(); i < s; ++i) {
				uint l_e0 = m_edge_list[i - 1], l_e1 = m_edge_list[i];
				sint l_c0 = m_vertex_edge_compare(l_v, l_e0), l_c1 = m_vertex_edge_compare(l_v, l_e1);
				if(l_c0 >= 0 && l_c1 <= 0) m_close_trapezoid(l_v, l_e0, l_e1);
				if(l_c0 < 0) break;
			}
		}
		if(!m_trapezoids.empty()) {
			for(uint i = m_trapezoids.size() - 1; ; --i) {
				if(m_trapezoids[i].v1 != bad_ID) {
					m_split_trapezoid(i);
					m_trapezoids.erase(m_trapezoids.begin() + i);
				}
				if(i == 0) break;
			}
		}
	}
	void m_split_trapezoid(uint _t) {
		const trapezoid &l_t = m_trapezoids[_t];
		assert(l_t.v0 != bad_ID && l_t.v1 != bad_ID);
		for(uint i = 0; i < l_t.v0c; ++i) {
			uint l_v0i = l_t.v0 + i;
			vertex &l_v0 = m_vertices[l_v0i];
			if(!l_v0.n) continue;
			const real l_p0_y = m_points[l_v0.p].y();
			uint l_v1i = bad_ID; real l_diff = infinity;
			for(uint i = 0; i < l_t.v1c; ++i) {
				const vertex &l_v1 = m_vertices[l_t.v1 + i];
				const real l_p1_y = m_points[l_v1.p].y();
				real l_diff1 = abs(l_p1_y - l_p0_y);
				if(l_diff1 < l_diff) l_diff = l_diff1;
				else break;
				l_v1i = l_t.v1 + i;
			}
			assert(l_v1i != bad_ID);
			m_insert_edges(l_v0i, l_v1i);
		}
		for(uint i = 0; i < l_t.v1c; ++i) {
			uint l_v0i = l_t.v1 + i;
			vertex &l_v0 = m_vertices[l_v0i];
			if(!l_v0.n) continue;
			const real l_p0_y = m_points[l_v0.p].y();
			uint l_v1i = bad_ID; real l_diff = infinity;
			for(uint i = 0; i < l_t.v0c; ++i) {
				const vertex &l_v1 = m_vertices[l_t.v0 + i];
				const real l_p1_y = m_points[l_v1.p].y();
				real l_diff1 = abs(l_p1_y - l_p0_y);
				if(l_diff1 < l_diff) l_diff = l_diff1;
				else break;
				l_v1i = l_t.v0 + i;
			}
			assert(l_v1i != bad_ID);
			m_insert_edges(l_v0i, l_v1i);
		}
	}
	void m_insert_edges(uint _v0, uint _v1) {
		vertex &l_v0 = m_vertices[_v0];
		vertex &l_v1 = m_vertices[_v1];
		uint l_e00i, l_e01i; m_vertex_edges(_v0, _v1, l_e00i, l_e01i);
		uint l_e10i, l_e11i; m_vertex_edges(_v1, _v0, l_e10i, l_e11i);
		edge &l_e00 = m_edges[l_e00i], &l_e10 = m_edges[l_e10i], l_ne0, l_ne1;
		l_ne0.v0 = l_ne1.v1 = _v0; l_ne0.v1 = l_ne1.v0 = _v1;
		l_ne0.ne = l_e11i; l_ne1.ne = l_e01i;
		l_ne0.te = m_edges.size() + 1; l_ne1.te = m_edges.size();
		l_e00.ne = m_edges.size(); l_e10.ne = m_edges.size() + 1;
		m_edges.push_back(l_ne0); m_edges.push_back(l_ne1);
		l_v0.n = l_v1.n = false;
	}
	void m_vertex_edges(uint _v0, uint _v1, uint &_e0, uint &_e1) {
		const vertex &l_v0 = m_vertices[_v0];
		if(m_edges[l_v0.e0].ne == l_v0.e1) {
			_e0 = l_v0.e0; _e1 = l_v0.e1;
			return;
		}
		const point &l_p0 = m_points[l_v0.p];
		const vertex &l_v = m_vertices[_v1];
		const point &l_p = m_points[l_v.p];
		_e0 = l_v0.e0; _e1 = m_edges[_e0].ne;
		while(true) {
			const edge &l_e0 = m_edges[_e0], &l_e1 = m_edges[_e1];
			const vertex &l_v1 = m_vertices[l_e0.v0], &l_v2 = m_vertices[l_e1.v1];
			const point &l_p1 = m_points[l_v1.p], &l_p2 = m_points[l_v2.p];
			point l_d = l_p - l_p0, l_d1 = l_p1 - l_p0, l_d2 = l_p2 - l_p0;
			real l_a = atan2(l_d.y(), l_d.x()), l_a1 = atan2(l_d1.y(), l_d1.x()), l_a2 = atan2(l_d2.y(), l_d2.x());
			real l_a01 = l_a - l_a1, l_a21 = l_a2 - l_a1;
			while(l_a01 < 0) l_a01 += real(2) * pi;
			while(l_a21 < 0) l_a21 += real(2) * pi;
			if(l_a21 > l_a01) return;
			assert(l_e1.te != bad_ID);
			_e0 = l_e1.te; _e1 = m_edges[_e0].ne;
		}
	}
	void m_close_trapezoid(uint _v, uint _e0, uint _e1) {
		uint l_i = m_get_trapezoid(_e0, _e1);
		if(l_i != bad_ID) {
			trapezoid &l_t = m_trapezoids[l_i];
			assert(l_t.v1 == bad_ID || l_t.v1 + l_t.v1c == _v);
			if(l_t.v1 == bad_ID) l_t.v1 = _v;
			else l_t.v1c++;
			vertex &l_v = m_vertices[_v];
			const edge &l_e0 = m_edges[l_v.e0], &l_e1 = m_edges[l_v.e1];
			if(l_e0.v0 > _v && l_e1.v1 > _v) l_v.n = true;
		}
	}
	uint m_get_trapezoid(uint _e0, uint _e1) const {
		for(uint i = 0, s = m_trapezoids.size(); i < s; ++i) {
			const trapezoid &l_t = m_trapezoids[i];
			if(l_t.e0 == _e0 && l_t.e1 == _e1) return i;
		}
		return bad_ID;
	}
	uint m_get_trapezoid(uint _e) const {
		for(uint i = 0, s = m_trapezoids.size(); i < s; ++i) {
			const trapezoid &l_t = m_trapezoids[i];
			if(l_t.e0 == _e || l_t.e1 == _e) return i;
		}
		return bad_ID;
	}
	sint m_vertex_edge_compare(uint _v, uint _e) const {
		const vertex &l_v = m_vertices[_v];
		const point &l_p = m_points[l_v.p];
		const edge &l_e = m_edges[_e];
		const vertex &l_v0 = m_vertices[l_e.v0];
		const vertex &l_v1 = m_vertices[l_e.v1];
		const point &l_p0 = l_e.v0 < l_e.v1 ? m_points[l_v0.p] : m_points[l_v1.p];
		const point &l_p1 = l_e.v0 < l_e.v1 ? m_points[l_v1.p] : m_points[l_v0.p];
		real l_cross = cross(l_p1 - l_p0, l_p - l_p0);
		if(l_cross > eps) return 1;
		if(l_cross < -eps) return -1;
		return 0;
	}
	sint m_edge_edge_compare(uint _e0, uint _e1) const {
		const edge &l_e0 = m_edges[_e0];
		const edge &l_e1 = m_edges[_e1];
		sint l_c001 = m_vertex_edge_compare(l_e0.v0, _e1);
		sint l_c011 = m_vertex_edge_compare(l_e0.v1, _e1);
		if(l_c001 == 0 && l_c011 == 0) return 0;
		if(l_c001 <= 0 && l_c011 <= 0) return -1;
		if(l_c001 >= 0 && l_c011 >= 0) return 1;
		sint l_c100 = m_vertex_edge_compare(l_e1.v0, _e0);
		sint l_c110 = m_vertex_edge_compare(l_e1.v1, _e0);
		if(l_c100 == 0 && l_c110 == 0) return 0;
		if(l_c100 <= 0 && l_c110 <= 0) return 1;
		if(l_c100 >= 0 && l_c110 >= 0) return -1;
		return 0;
	}
};

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// shape

shape::shape(const info &_info, player &_player) :
	_placed(_info, _player)
{}
shape::~shape() {
}
bool shape::render() const {
	player &l_player = get_player();
	renderer &l_renderer = l_player.get_renderer();
	const info &l_info = get_info<info>();
	static array_<real2> l_points; l_points.resize(0);
	for(uint i = 0, s = l_info.point_count(); i < s; ++i) {
		const real2 &l_p = l_info.get_point(i);
//		l_points.push_back(l_p);
		l_points.push_back(real3(l_p.x(), l_p.y(), 1) * position() * real(0.05));
	}
	for(uint i = 0, s = l_info.fillstyle_count(); i < s; ++i) {
		const fillstyle &l_fillstyle = l_info.get_fillstyle(i);
		const edges &l_edges = l_info.get_fillstyle_edges(i);
		if(l_edges.empty()) continue;
		triangulator::poly l_poly;
		for(uint i = 0, s = l_edges.size(); i < s; ++i) {
			const edge &l_edge = l_edges[i];
			if(l_edge.c != bad_ID) {
				struct _l { static void tesselate(const real2 &_s, const real2 &_c, const real2 &_e, array_<real2> &_points) {
					const real l_tolerance = real(0.1);
					real2 l_p0 = (_s + _e) * real(0.5), l_p = (l_p0 + _c) * real(0.5);
					if(length2(l_p - l_p0) <= l_tolerance) { _points.push_back(_e); return; }
					tesselate(_s, (_s + _c) * real(0.5), l_p, _points);
					tesselate(l_p, (_c + _e) * real(0.5), _e, _points);
				}};
				const real2 &l_s = l_points[l_edge.s];
				const real2 &l_c = l_points[l_edge.c];
				const real2 &l_e = l_points[l_edge.e];
				static array_<real2> l_edge_points; l_edge_points.resize(0);
				_l::tesselate(l_s, l_c, l_e, l_edge_points);
				l_poly.push_back(l_edge.s);
				for(uint i = 0, s = l_edge_points.size() - 1; i < s; ++i) {
					l_poly.push_back(l_points.size()); l_poly.push_back(l_points.size());
					l_points.push_back(l_edge_points[i]);
				}
				l_poly.push_back(l_edge.e);
			} else {
				l_poly.push_back(l_edge.s); l_poly.push_back(l_edge.e);
			}
		}
		triangulator l_triangulator;
		l_triangulator.build(l_points, l_poly);
		if(l_triangulator.tri_count() > 0) {
			l_renderer.draw_tris(&l_points[0], l_triangulator.get_tris(), l_triangulator.tri_count(), l_fillstyle.c, r3x3_1 * real(1)/*real(0.05) * m_position*/);
		}
		//
		for(uint i = 1, s = l_triangulator.lines.size(); i < s; i += 2) {
			const real2 &l_s = l_triangulator.lines[i - 1], &l_e = l_triangulator.lines[i];
			l_renderer.draw_line(l_s, l_e, l_fillstyle.c, real(0.5));
		}
	}
	//for(uint i = 0, s = l_info.line_path_count(); i < s; ++i) {
	//	const path &l_path = l_info.get_line_path(i);
	//	const line_style &l_line_style = l_info.get_line_style(l_path.style);
	//	if(l_line_style.w == 0) continue;
	//	uint l_line_start = 0;
	//	std::vector<std::vector<uint> > l_polys;
	//	for(uint i = 0, s = l_path.edges.size(); i < s; ++i) {
	//		const edge &l_edge = l_path.edges[i];
	//		if(l_polys.empty() || l_polys.back().back() != l_edge.s) {
	//			l_polys.push_back(std::vector<uint>());
	//			l_polys.back().push_back(l_edge.s);
	//		}
	//		if(l_edge.c != bad_ID) {
	//			struct _l { static void tesselate(const real2 &_s, const real2 &_c, const real2 &_e, std::vector<real2> &_points) {
	//				const real l_tolerance = real(0.1);
	//				real2 l_p0 = (_s + _e) * real(0.5), l_p = (l_p0 + _c) * real(0.5);
	//				if(length2(l_p - l_p0) <= l_tolerance) { _points.push_back(_e); return; }
	//				tesselate(_s, (_s + _c) * real(0.5), l_p, _points);
	//				tesselate(l_p, (_c + _e) * real(0.5), _e, _points);
	//			}};
	//			const real2 &l_s = l_points[l_edge.s];
	//			const real2 &l_c = l_points[l_edge.c];
	//			const real2 &l_e = l_points[l_edge.e];
	//			static std::vector<real2> l_edge_points; l_edge_points.resize(0);
	//			_l::tesselate(l_s, l_c, l_e, l_edge_points);
	//			for(uint i = 0, s = l_edge_points.size() - 1; i < s; ++i) {
	//				l_polys.back().push_back(l_points.size());
	//				l_points.push_back(l_edge_points[i]);
	//			}
	//		}
	//		l_polys.back().push_back(l_edge.e);
	//	}
	//	triangulator l_triangulator;
	//	l_triangulator.build(l_points, l_polys);
	//	for(uint i = 0, s = l_polys.size(); i < s; ++i) {
	//		const std::vector<uint> &l_poly = l_polys[i];
	//		for(uint i = 1, s = l_poly.size(); i < s; ++i) {
	//			l_renderer.draw_line(l_points[l_poly[i - 1]], l_points[l_poly[i]], l_line_style.c, l_line_style.w * real(0.05));
	//		}
	//	}
	//}
	return true;
}

// shape::info

shape::info::info(swfstream &_s, tag::type _type) : _placed::info(ot::shape) {
	fillstyle l_fillstyle; l_fillstyle.c = 0;
	m_fillstyles.push_back(l_fillstyle);
	m_filledges.push_back(edges());
	//line_style l_line_style; l_line_style.c = 0; l_line_style.w = 0;
	//m_line_styles.push_back(l_line_style);
	m_rect = m_edge_rect = _s.RECT();
	if(_type == tag::DefineShape4) {
		m_edge_rect = _s.RECT();
		uint l_reserved = _s.UB(6);
		uint l_nonscalingstrokes = _s.UB(1);
		uint l_scalingstrokes = _s.UB(1);
	}
	m_read_shape_records(_s, _type);
}
void shape::info::m_read_fill_styles(swfstream &_s, tag::type _type) {
	uint l_count = _s.UI8();
	if(l_count == 0xff) l_count = _s.UI16();
	for(uint i = 0; i < l_count; ++i) {
		fillstyle l_style;
		uint l_type = _s.UI8();
		switch(l_type) {
			case 0x00 : {
				l_style.c = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
			} break;
		}
		m_fillstyles.push_back(l_style);
		m_filledges.push_back(edges());
		assert(m_fillstyles.size() == m_filledges.size());
		_s.align();
	}
}
void shape::info::m_read_line_styles(swfstream &_s, tag::type _type) {
	uint l_count = _s.UI8();
	if(l_count == 0xff) l_count = _s.UI16();
	for(uint i = 0; i < l_count; ++i) {
		uint l_width = _s.UI16();
		switch(_type) {
			case tag::DefineShape :
			case tag::DefineShape2 :
			case tag::DefineShape3 : {
				color l_color = (_type > tag::DefineShape2) ? _s.RGBA() : _s.RGB();
				//line_style l_line_style; l_line_style.c = l_color; l_line_style.w = l_width;
				//m_line_styles.push_back(l_line_style);
			} break;
			case tag::DefineShape4 : {
				uint l_startcapstyle = _s.UB(2);
				uint l_joinstyle = _s.UB(2);
				uint l_hasfillflag = _s.UB(1);
				uint l_nohscaleflag = _s.UB(1);
				uint l_novscaleflag = _s.UB(1);
				uint l_pixelhintingflag = _s.UB(1);
				uint l_reservedflag = _s.UB(5);
				uint l_noclose = _s.UB(1);
				uint l_endcapstyle = _s.UB(2);
				if(l_joinstyle == 2) {
					uint l_miterlimitfactor = _s.UI16();
				}
				color l_color = l_hasfillflag == 0 ? _s.RGBA() : 0;
				if(l_hasfillflag == 1) {
					//
				}
				//line_style l_line_style; l_line_style.c = l_color; l_line_style.w = l_width;
				//m_line_styles.push_back(l_line_style);
			} break;
		}
		_s.align();
	}
}
uint shape::info::m_add_point(const point &_p) {
	points::iterator l_it = std::find(m_points.begin(), m_points.end(), _p);
	if(l_it == m_points.end()) { m_points.push_back(_p); return m_points.size() - 1; }
	return l_it - m_points.begin();
}
void shape::info::m_read_shape_records(swfstream &_s, tag::type _type) {
	enum {
		new_styles		= 1<<4,
		line_style		= 1<<3,
		fill_style1		= 1<<2,
		fill_style0		= 1<<1,
		move_to			= 1<<0,
	};
	m_read_fill_styles(_s, _type);
	m_read_line_styles(_s, _type);
	uint l_fill_bits = _s.UB(4);
	uint l_line_bits = _s.UB(4);
	uint l_line = 0;
	uint l_fill0 = 0;
	uint l_fill1 = 0;
	uint l_curr_point;
	while(true) {
		uint l_type = _s.UB(1);
		if(l_type == 0) {
			uint l_flags = _s.UB(5);
			if(l_flags == 0) break;
			if(l_flags & move_to) {
				uint l_move_bits = _s.UB(5);
				real l_move_x = (real)_s.SB(l_move_bits);
				real l_move_y = (real)_s.SB(l_move_bits);
				l_curr_point = m_add_point(real2(l_move_x, l_move_y));
			}
			if(l_flags & fill_style0) {
				l_fill0 = _s.UB(l_fill_bits);
			}
			if(l_flags & fill_style1) {
				l_fill1 = _s.UB(l_fill_bits);
			}
			if(l_flags & line_style) {
				l_line = _s.UB(l_line_bits);
			}
			if(l_flags & new_styles) {
				m_read_fill_styles(_s, _type);
				m_read_line_styles(_s, _type);
				l_fill_bits = _s.UB(4);
				l_line_bits = _s.UB(4);
			}
		} else {
			uint l_straight = _s.UB(1);
			uint l_delta_bits = _s.UB(4) + 2;
			edge l_edge; l_edge.s = l_curr_point;
			if(l_straight) {
				l_edge.c = bad_ID;
				uint l_general_line = _s.UB(1);
				uint l_vert_line = (l_general_line == 0) ? _s.UB(1) : 0;
				real l_delta_x = (l_general_line == 1 || l_vert_line == 0) ? (real)_s.SB(l_delta_bits) : 0;
				real l_delta_y = (l_general_line == 1 || l_vert_line == 1) ? (real)_s.SB(l_delta_bits) : 0;
				l_curr_point = m_add_point(get_point(l_curr_point) + real2(l_delta_x, l_delta_y));
				l_edge.e = l_curr_point;
			} else {
				real l_control_delta_x = (real)_s.SB(l_delta_bits);
				real l_control_delta_y = (real)_s.SB(l_delta_bits);
				l_curr_point = m_add_point(get_point(l_curr_point) + real2(l_control_delta_x, l_control_delta_y));
				l_edge.c = l_curr_point;
				real l_anchor_delta_x = (real)_s.SB(l_delta_bits);
				real l_anchor_delta_y = (real)_s.SB(l_delta_bits);
				l_curr_point = m_add_point(get_point(l_curr_point) + real2(l_anchor_delta_x, l_anchor_delta_y));
				l_edge.e = l_curr_point;
			}
			assert(l_edge.s != l_edge.e);
			if(l_fill0) {
				m_filledges[l_fill0].push_back(l_edge);
			}
			if(l_fill1) {
				swap(l_edge.s, l_edge.e);
				m_filledges[l_fill1].push_back(l_edge);
			}
			//if(!m_line_paths.back().edges.empty()) {
			//	const real2 &l_s0 = m_points[m_line_paths.back().edges.front().s];
			//	const real2 &l_e0 = m_points.back();
			//	if(length2(l_e0 - l_s0) < eps) {
			//		l_edge.e = m_line_paths.back().edges.front().s;
			//		m_points.pop_back();
			//	}
			//}
			//m_line_paths.back().edges.push_back(l_edge);
		}
	}
}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
