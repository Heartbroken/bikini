/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace as { /*--------------------------------------------------------------------------------*/

//
static inline uint U8(const byte* &_d) {
	u8 l_v = *(u8*)_d; _d += sizeof(u8);
	return uint(l_v);
}
static inline uint U16(const byte* &_d) {
	u16 l_v = *(u16*)_d; _d += sizeof(u16);
	return uint(l_v);
}
static inline sint S16(const byte* &_d) {
	byte l_b0 = *(_d++), l_b1 = *(_d++), l_b2 = *(_d++);
	return sint(l_b0) | sint(l_b1 << 8) | sint(l_b2 << 16) | ((l_b2 & 0x80) ? sint(0xff << 24) : sint(0x00 << 24));
}
static inline uint U30(const byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint U32(const byte* &_d) {
	uint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) return l_v;
	}
	return l_v;
}
static inline uint S32(const byte* &_d) {
	sint l_v = 0; byte l_b = *(_d++); uint l_c = 5;
	while(l_c--) {
		uint l_s = (4 - l_c) * 7;
		l_v |= (l_b & 0x7f) << l_s;
		if((l_b & 0x80) == 0) {
			if((l_b & 0x40) != 0) l_v |= 0xffffff80 << l_s;
			return l_v;
		}
	}
	return l_v;
}
static inline rbig F64(const byte* &_d) {
	f64 l_v = *(f64*)_d; _d += sizeof(f64);
	return rbig(l_v);
}
static inline wstring STRING(const byte* &_d) {
	uint l_s0 = U30(_d);
	uint l_s1 = MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, 0, 0);
	wchar* l_w = (wchar*)_malloca(l_s1 * sizeof(wchar*));
	MultiByteToWideChar(CP_UTF8, 0, (achar*)_d, (int)l_s0, l_w, (int)l_s1); _d += l_s0;
	return wstring(l_w, l_s1);
}
static inline machine::ns NAMESPACE(const byte* &_d) {
	machine::ns l_ns;
	l_ns.kind = (machine::ns::nsk::namespace_kind)U8(_d);
	l_ns.string = U30(_d);
	return l_ns;
}
static inline machine::ns_set NSSET(const byte* &_d) {
	machine::ns_set l_ns_set;
	uint l_count = U30(_d); l_ns_set.nss.resize(l_count);
	for(uint i = 0; i < l_count; ++i) l_ns_set.nss[i] = U32(_d);
	return l_ns_set;
}
static inline machine::multiname MULTINAME(const byte* &_d) {
	machine::multiname l_multiname;
	l_multiname.kind = (machine::multiname::mnk::multiname_kind)U8(_d);
	l_multiname.ns = l_multiname.name = l_multiname.ns_set = 0;
	switch(l_multiname.kind) {
		case machine::multiname::mnk::QName :
		case machine::multiname::mnk::QNameA :
			l_multiname.ns = U30(_d); l_multiname.name = U30(_d);
			break;
		case machine::multiname::mnk::RTQName :
		case machine::multiname::mnk::RTQNameA :
			l_multiname.name = U30(_d);
			break;
		case machine::multiname::mnk::RTQNameL :
		case machine::multiname::mnk::RTQNameLA :
			break;
		case machine::multiname::mnk::Multiname :
		case machine::multiname::mnk::MultinameA :
			l_multiname.name = U30(_d); l_multiname.ns_set = U30(_d);
			break;
		case machine::multiname::mnk::MultinameL :
		case machine::multiname::mnk::MultinameLA :
			l_multiname.ns_set = U30(_d);
			break;
	};
	return l_multiname;
}
static inline machine::method METHOD(const byte* &_d) {
	machine::method l_method;
	uint l_param_count = U30(_d);
	l_method.return_type = U30(_d);
	l_method.param_types.resize(l_param_count);
	for(uint i = 0; i < l_param_count; ++i) l_method.param_types[i] = U30(_d);
	l_method.name = U30(_d);
	l_method.flags = U8(_d);
	if(l_method.flags & machine::method::mf::HAS_OPTIONAL) {
		uint l_option_count = U30(_d); l_method.options.resize(l_option_count);
		for(uint i = 0; i < l_option_count; ++i) {
			l_method.options[i].val = U30(_d);
			l_method.options[i].kind = (machine::method::option::mok::kind)U8(_d);
		}
	}
	if(l_method.flags & machine::method::mf::HAS_PARAM_NAMES) {
		l_method.param_names.resize(l_param_count);
		for(uint i = 0; i < l_param_count; ++i) l_method.param_names[i] = U30(_d);
	}
	l_method.body = bad_ID;
	return l_method;
}
static inline machine::metadata METADATA(const byte* &_d) {
	machine::metadata l_metadata;
	l_metadata.name = U30(_d);
	uint l_item_count = U30(_d); l_metadata.items.resize(l_item_count);
	for(uint i = 0; i < l_item_count; ++i) {
		l_metadata.items[i].key = U30(_d);
		l_metadata.items[i].value = U30(_d);
	}
	return l_metadata;
}
static inline machine::trait TRAIT(const byte* &_d) {
	machine::trait l_trait;
	l_trait.name = U30(_d);
	l_trait.kind = U8(_d);
	switch(l_trait.kind & 0xf) {
		case machine::trait::itt::Slot :
		case machine::trait::itt::Const :
			l_trait.slot_id = U30(_d);
			l_trait.type_name = U30(_d);
			l_trait.vindex = U30(_d);
			if(l_trait.vindex != 0) l_trait.vkind = U8(_d);
			break;
		case machine::trait::itt::Class :
			l_trait.slot_id = U30(_d);
			l_trait.classi = U30(_d);
			break;
		case machine::trait::itt::Function :
			l_trait.slot_id = U30(_d);
			l_trait.function = U30(_d);
			break;
		case machine::trait::itt::Method :
		case machine::trait::itt::Getter :
		case machine::trait::itt::Setter :
			l_trait.disp_id = l_trait.slot_id = U30(_d);
			l_trait.method = U30(_d);
			break;
	}
	if((l_trait.kind >> 4) & machine::trait::ita::Metadata) {
		uint l_metadata_count = U30(_d); machine::metadatas l_metadatas; l_metadatas.resize(l_metadata_count);
		for(uint i = 0; i < l_metadata_count; ++i) l_metadatas[i] = METADATA(_d);
	}
	return l_trait;
}
static inline machine::instance INSTANCE(const byte* &_d) {
	machine::instance l_instance;
	l_instance.name = U30(_d);
	l_instance.super_name = U30(_d);
	l_instance.flags = U8(_d);
	l_instance.protected_ns = (l_instance.flags & machine::instance::oif::ClassProtectedNs) ? U30(_d) : 0;
	uint l_intrf_count = U30(_d); l_instance.interfaces.resize(l_intrf_count);
	for(uint i = 0; i < l_intrf_count; ++i) l_instance.interfaces[i] = U30(_d);
	l_instance.iinit = U30(_d);
	uint l_trait_count = U30(_d); l_instance.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_instance.traits[i] = TRAIT(_d);
	return l_instance;
}
static inline machine::classinfo CLASS(const byte* &_d) {
	machine::classinfo l_classinfo;
	l_classinfo.cinit = U30(_d);
	uint l_trait_count = U30(_d); l_classinfo.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_classinfo.traits[i] = TRAIT(_d);
	return l_classinfo;
}
static inline machine::script SCRIPT(const byte* &_d) {
	machine::script l_script;
	l_script.init = U30(_d);
	uint l_trait_count = U30(_d); l_script.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_script.traits[i] = TRAIT(_d);
	return l_script;
}
static inline machine::methodbody METHODBODY(const byte* &_d) {
	machine::methodbody l_methodbody;
	l_methodbody.method = U30(_d);
	l_methodbody.max_stack = U30(_d);
	l_methodbody.local_count = U30(_d);
	l_methodbody.init_scope_depth = U30(_d);
	l_methodbody.max_scope_depth = U30(_d);
	uint l_code_length = U30(_d); l_methodbody.code.resize(l_code_length);
	for(uint i = 0; i < l_code_length; ++i) l_methodbody.code[i] = (byte)U8(_d);
	uint l_exception_count = U30(_d); l_methodbody.exceptions.resize(l_exception_count);
	for(uint i = 0; i < l_exception_count; ++i) {
		machine::methodbody::exception &l_exception = l_methodbody.exceptions[i];
		l_exception.from = U30(_d);
		l_exception.to = U30(_d);
		l_exception.target = U30(_d);
		l_exception.exc_type = U30(_d);
		l_exception.var_name = U30(_d);
	}
	uint l_trait_count = U30(_d); l_methodbody.traits.resize(l_trait_count);
	for(uint i = 0; i < l_trait_count; ++i) l_methodbody.traits[i] = TRAIT(_d);
	return l_methodbody;
}
//

// machine

machine::machine() {
	// @@@
	new_object();
	set_object_prop(0, L"", 0, 10);
	object_ref l_object;
	l_object.ID = new_object();
	set_object_prop(0, L"Object", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"EventDispatcher", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"DisplayObject", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"InteractiveObject", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"DisplayObjectContainer", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"Sprite", l_object);
	l_object.ID = new_object();
	set_object_prop(0, L"MovieClip", l_object);
}
machine::~machine() {
	while(!m_segments.empty()) {
		delete m_segments.back();
		m_segments.pop_back();
	}
}
bool machine::do_ABC(pointer _data, uint _size, bool _run/* = true*/) {
	segment &l_segment = * new segment(*this, _data, _size);
	m_segments.push_back(&l_segment);
	if(_run) {
		l_segment.run_script();
		//assert(0);
	}
	return true;
}
uint machine::new_object() {
	m_objects.push_back(object());
	m_objects.back().set_ID(m_objects.size() - 1);
	return m_objects.back().ID();
}
void machine::set_object_prop(uint _ID, const wstring &_name, const value &_value, uint _slot) {
	m_objects[_ID].set(_name, _value, _slot);
}
const machine::value& machine::get_object_prop(uint _ID, uint _slot) {
	return m_objects[_ID].get(_slot);
}
const machine::value& machine::get_object_prop(uint _ID, const wstring &_name) {
	return m_objects[_ID].get(_name);
}

// machine::object

void machine::object::set(const wstring &_name, const value &_value, uint _slot) {
	if(_slot != bad_ID) {
		if(_slot >= m_props.size()) m_props.resize(_slot + 1);
		prop &l_p = m_props[_slot];
		l_p.n = _name; l_p.v = _value;
		return;
	}
	for(uint i = 0, s = m_props.size(); i < s; ++i) {
		prop &l_p = m_props[i];
		if(l_p.n == _name) {
			l_p.v = _value;
			return;
		}
	}
	prop l_p; l_p.n = _name; l_p.v = _value;
	m_props.push_back(l_p);
}
const machine::value& machine::object::get(uint _slot) {
	if(_slot < m_props.size()) {
		return m_props[_slot].v;
	}
	static value sl_bad_value;
	return sl_bad_value;
}
const machine::value& machine::object::get(const wstring &_name) {
	for(uint i = 0, s = m_props.size(); i < s; ++i) {
		if(m_props[i].n == _name) return m_props[i].v;
	}
	static value sl_bad_value;
	return sl_bad_value;
}

// machine::segment

machine::segment::segment(machine &_machine, pointer _data, uint _size) : m_machine(_machine) {
	const byte* l_data = (byte*)_data;
	uint l_minor = U16(l_data);
	uint l_major = U16(l_data);
	if(l_major > 46) {
		std::cerr << "ERROR: Wrong ActionScript 3.0 Byte Code version. Version 46.16 is expected\n";
		return;
	}
	// int constants
	uint l_int_count = U30(l_data); m_ints.resize(l_int_count);
	for(uint i = 1; i < l_int_count; ++i) m_ints[i] = S32(l_data);
	// uint constants
	uint l_uint_count = U30(l_data); m_uints.resize(l_uint_count);
	for(uint i = 1; i < l_uint_count; ++i) m_uints[i] = U32(l_data);
	// double constants
	uint l_double_count = U30(l_data); m_doubles.resize(l_double_count);
	for(uint i = 1; i < l_double_count; ++i) m_doubles[i] = F64(l_data);
	// string constants
	uint l_string_count = U30(l_data); m_strings.resize(l_string_count);
	for(uint i = 1; i < l_string_count; ++i) m_strings[i] = STRING(l_data);
	// namespace constants
	uint l_namespace_count = U30(l_data); m_namespaces.resize(l_namespace_count);
	for(uint i = 1; i < l_namespace_count; ++i) m_namespaces[i] = NAMESPACE(l_data);
	// ns_set constants
	uint l_ns_set_count = U30(l_data); m_ns_sets.resize(l_ns_set_count);
	for(uint i = 1; i < l_ns_set_count; ++i) m_ns_sets[i] = NSSET(l_data);
	// multiname constants
	uint l_multiname_count = U30(l_data); m_multinames.resize(l_multiname_count);
	for(uint i = 1; i < l_multiname_count; ++i) m_multinames[i] = MULTINAME(l_data);
	// methods
	uint l_method_count = U30(l_data); m_methods.resize(l_method_count);
	for(uint i = 0; i < l_method_count; ++i) m_methods[i] = METHOD(l_data);
	// metadata
	uint l_metadata_count = U30(l_data); metadatas l_metadatas; l_metadatas.resize(l_metadata_count);
	for(uint i = 0; i < l_metadata_count; ++i) l_metadatas[i] = METADATA(l_data);
	// classes
	uint l_class_count = U30(l_data);
	m_instances.resize(l_class_count); m_classinfos.resize(l_class_count);
	for(uint i = 0; i < l_class_count; ++i) m_instances[i] = INSTANCE(l_data);
	for(uint i = 0; i < l_class_count; ++i) m_classinfos[i] = CLASS(l_data);
	// scripts
	uint l_script_count = U30(l_data); m_scripts.resize(l_script_count);
	for(uint i = 0; i < l_script_count; ++i) m_scripts[i] = SCRIPT(l_data);
	// methods bodies
	uint l_methodbody_count = U30(l_data); m_methodbodys.resize(l_methodbody_count);
	for(uint i = 0; i < l_methodbody_count; ++i) {
		methodbody &l_methodbody = m_methodbodys[i]; l_methodbody = METHODBODY(l_data);
		m_methods[l_methodbody.method].body = i;
	}
	//
	int a=0;
}
void machine::segment::run_script(uint _index) const {
	assert(!m_scripts.empty());
	uint l_index = _index < m_scripts.size() ? _index : m_scripts.size() - 1;
	const script &l_script = m_scripts[l_index];
	for(uint i = 0, s = l_script.traits.size(); i < s; ++i) {
		const trait &l_t = l_script.traits[i];
		if(l_t.slot_id > 0) {
			value l_v = m_machine.get_object_prop(0, l_t.slot_id);
			if(l_v.type() == bad_ID) {
				const multiname &l_mn = m_multinames[l_t.name];
				const wstring &l_name = m_strings[l_mn.name];
				const ns &l_ns = m_namespaces[l_mn.ns];
				const wstring &l_namespace = m_strings[l_ns.string];
				m_machine.set_object_prop(0, l_name, 0, l_t.slot_id);
			}
		}
	}
	const method &l_method = m_methods[l_script.init];
	env l_env;
	object_ref l_global; l_global.ID = 0;
	l_env.locals.push_back(l_global);
	run(l_method.body, l_env);
}
void machine::segment::run(uint _methodbody, env &_env) const {
	const byte* l_code = &m_methodbodys[_methodbody].code[0];
	value l_result;
	bool l_run = true;
	while(l_run) {
		opcode::opcodes l_op = (opcode::opcodes)U8(l_code);
		switch(l_op) {
			case opcode::add : {
			} continue;
			case opcode::add_i : {
			} continue;
			case opcode::astype : {
			} continue;
			case opcode::astypelate : {
			} continue;
			case opcode::bitand : {
			} continue;
			case opcode::bitnot : {
			} continue;
			case opcode::bitor : {
			} continue;
			case opcode::bitxor : {
			} continue;
			case opcode::call : {
			} continue;
			case opcode::callmethod : {
			} continue;
			case opcode::callproperty : {
			} continue;
			case opcode::callproplex : {
			} continue;
			case opcode::callpropvoid : {
			} continue;
			case opcode::callstatic : {
			} continue;
			case opcode::callsuper : {
			} continue;
			case opcode::callsupervoid : {
			} continue;
			case opcode::checkfilter : {
			} continue;
			case opcode::coerce : {
			} continue;
			case opcode::coerce_a : {
			} continue;
			case opcode::coerce_s : {
			} continue;
			case opcode::construct : {
			} continue;
			case opcode::constructprop : {
			} continue;
			case opcode::constructsuper : {
			} continue;
			case opcode::convert_b : {
			} continue;
			case opcode::convert_i : {
			} continue;
			case opcode::convert_d : {
			} continue;
			case opcode::convert_o : {
			} continue;
			case opcode::convert_u : {
			} continue;
			case opcode::convert_s : {
			} continue;
			case opcode::debug : {
			} continue;
			case opcode::debugfile : {
			} continue;
			case opcode::debugline : {
			} continue;
			case opcode::declocal : {
			} continue;
			case opcode::declocal_i : {
			} continue;
			case opcode::decrement : {
			} continue;
			case opcode::decrement_i : {
			} continue;
			case opcode::deleteproperty : {
			} continue;
			case opcode::divide : {
			} continue;
			case opcode::dup : {
				_env.stack.push_back(_env.stack.back());
			} continue;
			case opcode::dxns : {
			} continue;
			case opcode::dxnslate : {
			} continue;
			case opcode::equals : {
			} continue;
			case opcode::esc_xattr : {
			} continue;
			case opcode::esc_xelem : {
			} continue;
			case opcode::findproperty : {
				uint l_index = U30(l_code);
				const multiname &l_mn = m_multinames[l_index];
				const wstring &l_name = m_strings[l_mn.name];
				const ns &l_ns = m_namespaces[l_mn.ns];
				const wstring &l_namespace = m_strings[l_ns.string];
				value l_v;
			} continue;
			case opcode::findpropstrict : {
			} continue;
			case opcode::getdescendants : {
			} continue;
			case opcode::getglobalscope : {
				_env.stack.push_back(_env.scope[0]);
			} continue;
			case opcode::getglobalslot : {
			} continue;
			case opcode::getlex : {
				uint l_index = U30(l_code);
				const multiname &l_mn = m_multinames[l_index];
				const wstring &l_name = m_strings[l_mn.name];
				const ns &l_ns = m_namespaces[l_mn.ns];
				const wstring &l_namespace = m_strings[l_ns.string];
				value l_v;
				for(uint i = _env.scope.size(); i-- > 0;) {
					assert(_env.scope[i].type() == types::type_<object_ref>::index);
					l_v = m_machine.get_object_prop(_env.scope[i].get<object_ref>().ID, l_name);
					if(l_v.type() != bad_ID) break;
				}
				_env.stack.push_back(l_v);
				int a=0;
			} continue;
			case opcode::getlocal : {
			} continue;
			case opcode::getlocal_0 : {
				_env.stack.push_back(_env.locals[0]);
			} continue;
			case opcode::getlocal_1 : {
				_env.stack.push_back(_env.locals[1]);
			} continue;
			case opcode::getlocal_2 : {
				_env.stack.push_back(_env.locals[2]);
			} continue;
			case opcode::getlocal_3 : {
				_env.stack.push_back(_env.locals[3]);
			} continue;
			case opcode::getproperty : {
			} continue;
			case opcode::getscopeobject : {
				uint l_index = U8(l_code);
				_env.stack.push_back(_env.scope[l_index]);
			} continue;
			case opcode::getslot : {
				uint l_index = U8(l_code);
				value l_o = _env.stack.back(); _env.stack.pop_back();
				assert(l_o.type() == types::type_<object_ref>::index);
				value l_v = m_machine.get_object_prop(l_o.get<object_ref>().ID, l_index);
				_env.stack.push_back(l_v);
				int a=0;
			} continue;
			case opcode::getsuper : {
			} continue;
			case opcode::greaterequals : {
			} continue;
			case opcode::greaterthan : {
			} continue;
			case opcode::hasnext : {
			} continue;
			case opcode::hasnext2 : {
			} continue;
			case opcode::ifeq : {
			} continue;
			case opcode::iffalse : {
			} continue;
			case opcode::ifge : {
			} continue;
			case opcode::ifgt : {
			} continue;
			case opcode::ifle : {
			} continue;
			case opcode::iflt : {
			} continue;
			case opcode::ifnge : {
			} continue;
			case opcode::ifngt : {
			} continue;
			case opcode::ifnle : {
			} continue;
			case opcode::ifnlt : {
			} continue;
			case opcode::ifne : {
			} continue;
			case opcode::ifstricteq : {
			} continue;
			case opcode::ifstrictne : {
			} continue;
			case opcode::iftrue : {
			} continue;
			case opcode::in : {
			} continue;
			case opcode::inclocal : {
			} continue;
			case opcode::inclocal_i : {
			} continue;
			case opcode::increment : {
			} continue;
			case opcode::increment_i : {
			} continue;
			case opcode::initproperty : {
				uint l_index = U30(l_code);
				const multiname &l_mn = m_multinames[l_index];
				const wstring &l_name = m_strings[l_mn.name];
				const ns &l_ns = m_namespaces[l_mn.ns];
				const wstring &l_namespace = m_strings[l_ns.string];
				value l_v = _env.stack.back(); _env.stack.pop_back();
				value l_o = _env.stack.back(); _env.stack.pop_back();
				assert(l_o.type() == types::type_<object_ref>::index);
				m_machine.set_object_prop(l_o.get<object_ref>().ID, l_name, l_v);
				int a=0;
			} continue;
			case opcode::instanceof : {
			} continue;
			case opcode::istype : {
			} continue;
			case opcode::istypelate : {
			} continue;
			case opcode::jump : {
			} continue;
			case opcode::kill : {
				uint l_index = U30(l_code);
				_env.locals[l_index] = value();
			} continue;
			case opcode::label : {
			} continue;
			case opcode::lessequals : {
			} continue;
			case opcode::lessthan : {
			} continue;
			case opcode::lookupswitch : {
			} continue;
			case opcode::lshift : {
			} continue;
			case opcode::modulo : {
			} continue;
			case opcode::multiply : {
			} continue;
			case opcode::multiply_i : {
			} continue;
			case opcode::negate : {
			} continue;
			case opcode::negate_i : {
			} continue;
			case opcode::newactivation : {
			} continue;
			case opcode::newarray : {
			} continue;
			case opcode::newcatch : {
			} continue;
			case opcode::newclass : {
				uint l_index = U30(l_code);
				const classinfo& l_ci = m_classinfos[l_index];
				value l_base = _env.stack.back(); _env.stack.pop_back();
				object_ref l_class; l_class.ID = m_machine.new_object();
				for(uint i = 0, s = l_ci.traits.size(); i < s; ++i) {
					const trait &l_t = l_ci.traits[i];
					if(l_t.slot_id > 0) {
						value l_v = m_machine.get_object_prop(l_class.ID, l_t.slot_id);
						if(l_v.type() == bad_ID) {
							const multiname &l_mn = m_multinames[l_t.name];
							const wstring &l_name = m_strings[l_mn.name];
							const ns &l_ns = m_namespaces[l_mn.ns];
							const wstring &l_namespace = m_strings[l_ns.string];
							m_machine.set_object_prop(l_class.ID, l_name, 0, l_t.slot_id);
						}
					}
				}
				_env.stack.push_back(l_class);
				//
				const method &l_method = m_methods[l_ci.cinit];
				env l_env;
				l_env.locals.push_back(l_class);
				run(l_method.body, l_env);
				//
				int a=0;
			} continue;
			case opcode::newfunction : {
			} continue;
			case opcode::newobject : {
			} continue;
			case opcode::nextname : {
			} continue;
			case opcode::nextvalue : {
			} continue;
			case opcode::nop : {
			} continue;
			case opcode::not : {
			} continue;
			case opcode::pop : {
			} continue;
			case opcode::popscope : {
				_env.scope.pop_back();
			} continue;
			case opcode::pushbyte : {
				uint l_byte = U8(l_code);
				_env.stack.push_back(l_byte);
			} continue;
			case opcode::pushdouble : {
			} continue;
			case opcode::pushfalse : {
			} continue;
			case opcode::pushint : {
			} continue;
			case opcode::pushnamespace : {
			} continue;
			case opcode::pushnan : {
			} continue;
			case opcode::pushnull : {
			} continue;
			case opcode::pushscope : {
				_env.scope.push_back(_env.stack.back());
				_env.stack.pop_back();
			} continue;
			case opcode::pushshort : {
			} continue;
			case opcode::pushstring : {
			} continue;
			case opcode::pushtrue : {
			} continue;
			case opcode::pushuint : {
			} continue;
			case opcode::pushundefined : {
			} continue;
			case opcode::pushwith : {
			} continue;
			case opcode::returnvalue : {
				l_result = _env.stack.back(); _env.stack.pop_back();
				l_run = false;
			} continue;
			case opcode::returnvoid : {
				l_run = false;
			} continue;
			case opcode::rshift : {
			} continue;
			case opcode::setlocal : {
			} continue;
			case opcode::setlocal_0 : {
				if(_env.locals.size() <= 0) _env.locals.resize(0 + 1);
				_env.locals[0] = _env.stack.back(); _env.stack.pop_back();
			} continue;
			case opcode::setlocal_1 : {
				if(_env.locals.size() <= 1) _env.locals.resize(1 + 1);
				_env.locals[1] = _env.stack.back(); _env.stack.pop_back();
			} continue;
			case opcode::setlocal_2 : {
				if(_env.locals.size() <= 2) _env.locals.resize(2 + 1);
				_env.locals[2] = _env.stack.back(); _env.stack.pop_back();
			} continue;
			case opcode::setlocal_3 : {
				if(_env.locals.size() <= 3) _env.locals.resize(3 + 1);
				_env.locals[3] = _env.stack.back(); _env.stack.pop_back();
			} continue;
			case opcode::setglobalslot : {
			} continue;
			case opcode::setproperty : {
				uint l_index = U30(l_code);
				const multiname &l_mn = m_multinames[l_index];
				const wstring &l_name = m_strings[l_mn.name];
				const ns &l_ns = m_namespaces[l_mn.ns];
				const wstring &l_namespace = m_strings[l_ns.string];
				value l_v = _env.stack.back(); _env.stack.pop_back();
				value l_o = _env.stack.back(); _env.stack.pop_back();
				assert(l_o.type() == types::type_<object_ref>::index);
				m_machine.set_object_prop(l_o.get<object_ref>().ID, l_name, l_v);
				int a=0;
			} continue;
			case opcode::setslot : {
			} continue;
			case opcode::setsuper : {
			} continue;
			case opcode::strictequals : {
			} continue;
			case opcode::subtract : {
			} continue;
			case opcode::subtract_i : {
			} continue;
			case opcode::swap : {
			} continue;
			case opcode::throw_ : {
			} continue;
			case opcode::typeof : {
			} continue;
			case opcode::urshift : {
			} continue;
			default : {
				assert(0);
				l_run = false;
			}
		}
	}
}

} /* namespace as -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/
