/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

/// _placed
struct _placed : player::object {
	inline _placed(const info &_info, player &_player) : player::object(_info, _player), m_position(r3x3_1), m_moved(true) {}
	inline const r3x3& position() const { return m_position; }
	inline void set_position(const r3x3 &_p) { m_moved = !(m_position == _p); m_position = _p; }
	inline bool moved() const { return m_moved; }
	inline void set_moved(bool _yes = true) { m_moved = _yes; }
private:
	r3x3 m_position; bool m_moved;
};

/// clip
struct clip : _placed {
	typedef array_<byte> bytecode;
	struct frame {
		struct object {
			uint ID; r3x3 position; cxform tinge; real ratio; wstring name; uint clipdepth;
			inline object() : ID(bad_ID) {}
		};
		typedef array_<object> objects;
		typedef array_<bytecode> actions;
		inline void set_objects(const objects &_objects) { m_objects = _objects; }
		inline uint object_count() const { return m_objects.size(); }
		inline const object& get_object(uint _i) const { return m_objects[_i]; }
		inline void add_action(const bytecode &_bytecode) { m_actions.push_back(_bytecode); }
		inline uint action_count() const { return m_actions.size(); }
		inline const bytecode& get_action(uint _i) const { return m_actions[_i]; }
	private:
		objects m_objects;
		actions m_actions;
	};
	struct info : _placed::info {
		typedef clip object;
		typedef uint a0;
		info(movie::info &_movie, swfstream &_s);
		inline uint frame_count() const { return m_timeline.size(); }
		inline const frame& get_frame(uint _i) const { return m_timeline[_i]; }
		inline const byte_array& get_ABC() const { return m_abc; }
	private:
		array_<frame> m_timeline;
		void m_edit_objects(swfstream &_s, tag::type _tag, frame::objects &_objects);
		void m_read_actions(swfstream &_s, bytecode &_bytecode);
		byte_array m_abc;
	};
	clip(const info &_info, player &_player, uint _movie_ID);
	~clip();
	bool update(real _dt);
	bool render() const;
private:
	uint m_movie_ID;
	real m_time;
	uint m_curr_frame;
	array_<uint> m_objects;
};
