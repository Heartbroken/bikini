/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace po { /*--------------------------------------------------------------------------------*/

// record

struct record {
	tag::type type; uint length;
};
static record RECORD(swfstream &_s) {
	record l_v;
	uint l_c = _s.UI16();
	l_v.type = (tag::type)((l_c & 0xffc0) >> 6);
	l_v.length = l_c & 0x3f;
	if(l_v.length == 0x3f) {
		sint l_l = _s.SI32();
		l_v.length = l_l;
	}
	return l_v;
}

// clip

clip::clip(const info &_info, player &_player, uint _movie_ID) :
	_placed(_info, _player), m_movie_ID(_movie_ID), m_time(0), m_curr_frame(bad_ID)
{
	//player &l_player = get_player();
	//movie &l_movie = l_player.get<movie>(m_movie_ID);
	//const array_<byte>& l_abc = _info.get_ABC();
	//if(!l_abc.empty()) l_movie.get_script().do_ABC(&l_abc[0], l_abc.size());
}
clip::~clip() {
	while(!m_objects.empty()) {
		if(get_player().exists(m_objects.back())) get_player().kill(m_objects.back());
		m_objects.pop_back();
	}
}
bool clip::update(real _dt) {
	m_time += _dt;
	player &l_player = get_player();
	movie &l_movie = l_player.get<movie>(m_movie_ID);
	uint l_curr_frame = uint(m_time * l_movie.frame_rate()) % get_info<info>().frame_count();
	if(m_curr_frame != l_curr_frame) {
		const frame &l_frame = get_info<info>().get_frame(l_curr_frame);
		if(m_objects.size() < l_frame.object_count()) m_objects.resize(l_frame.object_count(), bad_ID);
		for(uint i = 0, s = l_frame.object_count(); i < s; ++i) {
			const frame::object &l_o = l_frame.get_object(i);
			if(l_o.ID == bad_ID) {
				if(m_objects[i] != bad_ID) {
					l_player.kill(m_objects[i]);
					m_objects[i] = bad_ID;
				}
				continue;
			}
			if(m_objects[i] != bad_ID) {
				if(&l_player.get(m_objects[i]).get_info() != &l_movie.get_define<player::object>(l_o.ID)) {
					l_player.kill(m_objects[i]);
					m_objects[i] = bad_ID;
				}
			}
			if(m_objects[i] == bad_ID) {
				switch(l_movie.define_type(l_o.ID)) {
					case ot::shape : m_objects[i] = l_player.spawn(l_movie.get_define<shape>(l_o.ID)); break;
					case ot::clip : m_objects[i] = l_player.spawn(l_movie.get_define<clip>(l_o.ID), m_movie_ID); break;
				}
			}
			l_player.get<_placed>(m_objects[i]).set_position(l_o.position * position());
		}
		if(m_objects.size() > l_frame.object_count()) {
			if(l_player.exists(m_objects.back())) l_player.kill(m_objects.back());
			m_objects.pop_back();
		}
		//uint l_object_ID = bad_ID;
		//for(uint i = 0, s = l_frame.command_count(); i < s; ++i) {
		//	const frame::command &l_command = l_frame.get_command(i);
		//	switch(l_command.type()) {
		//		case frame::commands::type_<frame::add_object>::index : {
		//			frame::add_object l_c = l_command.get<frame::add_object>();
		//			if(l_c.depth >= m_objects.size()) m_objects.resize(l_c.depth + 1, bad_ID);
		//			if(l_player.exists(m_objects[l_c.depth])) l_player.kill(m_objects[l_c.depth]);
		//			switch(l_movie.define_type(l_c.ID)) {
		//				case ot::shape : m_objects[l_c.depth] = l_player.spawn(l_movie.get_define<shape>(l_c.ID)); break;
		//				case ot::clip : m_objects[l_c.depth] = l_player.spawn(l_movie.get_define<clip>(l_c.ID), m_movie_ID); break;
		//			}
		//			l_object_ID = m_objects[l_c.depth];
		//		} break;
		//		case frame::commands::type_<frame::select_object>::index : {
		//			frame::select_object l_c = l_command.get<frame::select_object>();
		//			assert(l_c.depth < m_objects.size());
		//			l_object_ID = m_objects[l_c.depth];
		//		} break;
		//		case frame::commands::type_<frame::move_object>::index : {
		//			frame::move_object l_c = l_command.get<frame::move_object>();
		//			if(l_player.exists(l_object_ID)) {
		//				switch(l_player.get(l_object_ID).type()) {
		//					case ot::shape : l_player.get<shape>(l_object_ID).set_position(position() * l_c.position); break;
		//					case ot::clip : l_player.get<clip>(l_object_ID).set_position(position() * l_c.position); break;
		//				}
		//			}
		//		} break;
		//		case frame::commands::type_<frame::tinge_object>::index : {
		//			frame::tinge_object l_c = l_command.get<frame::tinge_object>();
		//		} break;
		//		case frame::commands::type_<frame::morph_object>::index : {
		//			frame::morph_object l_c = l_command.get<frame::morph_object>();
		//		} break;
		//		case frame::commands::type_<frame::name_object>::index : {
		//			frame::name_object l_c = l_command.get<frame::name_object>();
		//		} break;
		//		case frame::commands::type_<frame::clipoff_object>::index : {
		//			frame::clipoff_object l_c = l_command.get<frame::clipoff_object>();
		//		} break;
		//		case frame::commands::type_<frame::remove_object>::index : {
		//			frame::remove_object l_c = l_command.get<frame::remove_object>();
		//			assert(l_c.depth < m_objects.size());
		//			if(l_player.exists(m_objects[l_c.depth])) l_player.kill(m_objects[l_c.depth]);
		//			m_objects[l_c.depth] = bad_ID;
		//		} break;
		//	}
		//}
		m_curr_frame = l_curr_frame;
	}
	if(moved()) {
		const frame &l_frame = get_info<info>().get_frame(l_curr_frame);
		for(uint i = 0, s = m_objects.size(); i < s; ++i) if(l_player.exists(m_objects[i])) {
			l_player.get<_placed>(m_objects[i]).set_position(l_frame.get_object(i).position * position());
		}
		set_moved(false);
	}
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		uint l_object_ID = m_objects[i];
		if(l_player.exists(l_object_ID) && l_player.get(l_object_ID).type() == ot::clip) {
			l_player.get<clip>(l_object_ID).update(_dt);
		}
	}
	return true;
}
bool clip::render() const {
	player &l_player = get_player();
	for(uint i = 0, s = m_objects.size(); i < s; ++i) {
		uint l_object_ID = m_objects[i];
		if(l_player.exists(l_object_ID)) {
			switch(l_player.get(l_object_ID).type()) {
				case ot::shape : l_player.get<shape>(l_object_ID).render(); break;
				case ot::clip : l_player.get<clip>(l_object_ID).render(); break;
			}
		}
	}
	return true;
}

// clip::info

clip::info::info(movie::info &_movie, swfstream &_s) : _placed::info(ot::clip) {
	uint l_frame_count = _s.UI16();
	m_timeline.resize(l_frame_count);
	uint l_curr_frame = 0;
	frame::objects l_objects;
	while(true) {
		record l_record = RECORD(_s);
		if(l_record.type == tag::End) break;
		uint l_position = _s.seek();
		assert(l_curr_frame < m_timeline.size());
		switch(l_record.type) {
			case tag::FileAttributes : {
				uint l_flags = _s.UI8();
				assert(l_flags & (1 << 3));
				if((l_flags & (1 << 3)) == 0) {
					std::cerr << "ERROR: Not Action Script 3.0 file\n";
				}
				_s.UB(24);
			} break;
			case tag::DefineShape :
			case tag::DefineShape2 :
			case tag::DefineShape3 :
			case tag::DefineShape4 : {
				_movie.define_shape(_s, l_record.type);
			} break;
			case tag::DefineSprite : {
				_movie.define_clip(_s);
			} break;
			//case tag::DefineButton : {
			//case tag::DefineButton2 : {
			//	_movie.define_button(_s);
			//} break;
			case tag::PlaceObject :
			case tag::PlaceObject2 :
			case tag::PlaceObject3 :
			case tag::RemoveObject :
			case tag::RemoveObject2 : {
				m_edit_objects(_s, l_record.type, l_objects);
			} break;
			case tag::SymbolClass : {
				uint l_count = _s.UI16();
				while(l_count--) {
					uint l_ID = _s.UI16();
					wstring l_name = _s.STRING();
					_movie.set_class(l_ID, l_name);
					int a=0;
				}
			} break;
			case tag::DoABC : {
				uint l_flags = _s.UI32();
				wstring l_name = _s.STRING();
				uint l_abc_length = l_record.length - (_s.seek() - l_position);
				if(l_abc_length > 0) {
					assert(m_abc.empty());
					m_abc.resize(l_abc_length);
					for(uint i = 0, s = l_abc_length; i < s; ++i) m_abc[i] = _s.BYTE();
					//l_movie.get_script().do_ABC(&l_abc[0], l_abc.size());
				}
			} break;
			//case tag::DoAction : {
			//	bytecode l_bytecode; m_read_actions(_s, l_bytecode);
			//	m_timeline[l_curr_frame].add_action(l_bytecode);
			//} break;
			//case tag::StartSound :
			//case tag::StartSound2 : {
			//	m_timeline[l_curr_frame].add_command(_s, l_record.type);
			//}
			case tag::ShowFrame : {
				m_timeline[l_curr_frame].set_objects(l_objects);
				++l_curr_frame;
			} break;
			default : {
				_s.seek(l_record.length);
			}
		}
		//_s.seek(l_position + l_record.length, 0);
		uint l_position2 = _s.seek();
		assert(l_position2 == l_position + l_record.length);
	}
}
void clip::info::m_edit_objects(swfstream &_s, tag::type _tag, frame::objects &_objects) {
	enum place_flags {
		move			= 1<<0,
		has_character	= 1<<1,
		has_matrix		= 1<<2,
		has_cxform		= 1<<3,
		has_ratio		= 1<<4,
		has_name		= 1<<5,
		has_clipdepth	= 1<<6,
		has_clipactions	= 1<<7,
	};
	switch(_tag) {
		case tag::PlaceObject : {
			assert(0 && "PlaceObject unsupported");
		} break;
		case tag::PlaceObject2 : {
			uint l_flags = _s.UI8();
			uint l_depth = _s.UI16();
			if(l_depth >= _objects.size()) _objects.resize(l_depth + 1);
			frame::object &l_object = _objects[l_depth];
			if(l_flags & has_character) l_object.ID = _s.UI16();
			if(l_flags & has_matrix) l_object.position = _s.MATRIX();
			if(l_flags & has_cxform) l_object.tinge = _s.CXFORM();
			if(l_flags & has_ratio) l_object.ratio = real(_s.UI16()) / real(65535);
			if(l_flags & has_name) l_object.name = _s.STRING();
			if(l_flags & has_clipdepth) l_object.clipdepth = _s.UI16();
			assert((l_flags & has_clipactions) == 0);
		} break;
		case tag::PlaceObject3 : {
			assert(0 && "PlaceObject3 not implemented");
		} break;
		case tag::RemoveObject : {
			uint l_define_ID = _s.UI16();
			uint l_depth = _s.UI16();
			assert(l_depth < _objects.size());
			_objects[l_depth].ID = bad_ID;
		} break;
		case tag::RemoveObject2 : {
			uint l_depth = _s.UI16();
			assert(l_depth < _objects.size());
			_objects[l_depth].ID = bad_ID;
		} break;
	}
}
void clip::info::m_read_actions(swfstream &_s, bytecode &_bytecode) {
	while(true) {
		uint l_code = _s.UI8();
		if(l_code == 0) break;
		_bytecode.push_back((u8)l_code);
		if(l_code & 0x80) {
			uint l_length = _s.UI16();
			_bytecode.push_back(u8(l_length & 0xff));
			_bytecode.push_back(u8((l_length >> 8) & 0xff));
			while(l_length--) _bytecode.push_back((u8)_s.UI8());
		}
	}
}

// clip::frame

//void clip::frame::add_command(swfstream &_s, tag::type _type) {
//	enum place_flags {
//		move			= 1<<0,
//		has_character	= 1<<1,
//		has_matrix		= 1<<2,
//		has_cxform		= 1<<3,
//		has_ratio		= 1<<4,
//		has_name		= 1<<5,
//		has_clipdepth	= 1<<6,
//		has_clipactions	= 1<<7,
//	};
//	switch(_type) {
//		case tag::PlaceObject : {
//			assert(0 && "PlaceObject unsupported");
//		} break;
//		case tag::PlaceObject2 : {
//			uint l_flags = _s.UB(8);
//			uint l_depth = _s.UI16();
//			if(l_flags & has_character) {
//				add_object l_c; l_c.ID = _s.UI16(); l_c.depth = l_depth;
//				m_commands.push_back(l_c);
//			} else {
//				select_object l_c; l_c.depth = l_depth;
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_matrix) {
//				move_object l_c; l_c.position = _s.MATRIX();
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_cxform) {
//				tinge_object l_c; l_c.cxf = _s.CXFORM();
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_ratio) {
//				morph_object l_c; l_c.ratio = real(_s.UI16()) / real(65535);
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_name) {
//				name_object l_c; l_c.name = _s.STRING();
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_clipdepth) {
//				clipoff_object l_c; l_c.clipdepth = _s.UI16();
//				m_commands.push_back(l_c);
//			}
//			if(l_flags & has_clipactions) {
//				assert(0 && "Clip actoins not implemented");
//			}
//		} break;
//		case tag::PlaceObject3 : {
//			assert(0 && "PlaceObject3 not implemented");
//		} break;
//		case tag::RemoveObject : {
//			uint l_define_ID = _s.UI16();
//			remove_object l_c; l_c.depth = _s.UI16();
//			m_commands.push_back(l_c);
//		} break;
//		case tag::RemoveObject2 : {
//			remove_object l_c; l_c.depth = _s.UI16();
//			m_commands.push_back(l_c);
//		} break;
//		case tag::DoAction : {
//			do_action l_c;
//			while(true) {
//				uint l_code = _s.UI8();
//				if(l_code == 0) break;
//				l_c.program.push_back((u8)l_code);
//				if(l_code & 0x80) {
//					uint l_length = _s.UI16();
//					l_c.program.push_back(u8(l_length & 0xff));
//					l_c.program.push_back(u8((l_length >> 8) & 0xff));
//					while(l_length--) l_c.program.push_back((u8)_s.UI8());
//				}
//			}
//			m_commands.push_back(l_c);
//		} break;
//	}
//}

} /* namespace po -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
