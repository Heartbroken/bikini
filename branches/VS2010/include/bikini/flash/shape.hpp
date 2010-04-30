/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct shape : _placed {
	typedef real2 point;
	typedef array_<point> points;
	struct edge { uint s, c, e; }; typedef array_<edge> edges;
	struct fillstyle { color c; }; typedef array_<fillstyle> fillstyles;
	typedef array_<edges> filledges;
	//struct linestyle : fillstyle { uint w; };
	//struct path { uint style; std::vector<edge> edges; };
	struct info : _placed::info {
		typedef shape object;
		info(swfstream &_s, tag::type _type);
		inline uint point_count() const { return m_points.size(); }
		inline const point& get_point(uint _i) const { return m_points[_i]; }
		inline uint fillstyle_count() const { return m_fillstyles.size(); }
		inline const fillstyle& get_fillstyle(uint _i) const { return m_fillstyles[_i]; }
		inline const edges& get_fillstyle_edges(uint _i) const { return m_filledges[_i]; }
		//inline uint line_style_count() const { return m_line_styles.size(); }
		//inline const line_style& get_line_style(uint _i) const { return m_line_styles[_i]; }
		//inline uint line_path_count() const { return m_line_paths.size(); }
		//inline const path& get_line_path(uint _i) const { return m_line_paths[_i]; }
	private:
		rect m_rect, m_edge_rect;
		void m_read_fill_styles(swfstream &_s, tag::type _type);
		void m_read_line_styles(swfstream &_s, tag::type _type);
		uint m_add_point(const point &_p);
		void m_read_shape_records(swfstream &_s, tag::type _type);
		points m_points;
		fillstyles m_fillstyles;
		filledges m_filledges;
		//std::vector<line_style> m_line_styles;
		//std::vector<path> m_line_paths;
	};
	shape(const info &_info, player &_player);
	~shape();
	bool render() const;
};
