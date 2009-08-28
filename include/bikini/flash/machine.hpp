/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

struct machine {
	machine();
	~machine();
	bool do_ABC(pointer _data, uint _size, bool _run = true);
private:
	//
	struct ns {
		struct nsk { enum namespace_kind {
			Namespace			= 0x08,
			PackageNamespace	= 0x16,
			PackageInternalNs	= 0x17,
			ProtectedNamespace	= 0x18,
			ExplicitNamespace	= 0x19,
			StaticProtectedNs	= 0x1A,
			PrivateNs			= 0x05,
		};};
		nsk::namespace_kind kind;
		uint string;
	};
	friend ns NAMESPACE(const byte*&);
	typedef array_<ns> namespaces;
	//
	struct ns_set {
		uint_array nss;
	};
	friend ns_set NSSET(const byte*&);
	typedef array_<ns_set> ns_sets;
	//
	struct multiname {
		struct mnk { enum multiname_kind {
			QName		= 0x07,
			QNameA		= 0x0D,
			RTQName		= 0x0F,
			RTQNameA	= 0x10,
			RTQNameL	= 0x11,
			RTQNameLA	= 0x12,
			Multiname	= 0x09,
			MultinameA	= 0x0E,
			MultinameL	= 0x1B,
			MultinameLA	= 0x1C,
		};};
		mnk::multiname_kind kind;
		uint ns, name, ns_set;
	};
	friend multiname MULTINAME(const byte*&);
	typedef array_<multiname> multinames;
	//
	struct method {
		uint return_type;
		uint_array param_types;
		uint name, body;
		struct mf { enum flags {
			NEED_ARGUMENTS		= 0x01,
			NEED_ACTIVATION		= 0x02,
			NEED_REST			= 0x04,
			HAS_OPTIONAL		= 0x08,
			SET_DXNS			= 0x40,
			HAS_PARAM_NAMES		= 0x80,
		};};
		uint flags;
		struct option {
			struct mok { enum kind {
				Int					= 0x03,
				UInt				= 0x04,
				Double				= 0x06,
				Utf8				= 0x01,
				True				= 0x0B,
				False				= 0x0A,
				Null				= 0x0C,
				Undefined			= 0x00,
				Namespace			= 0x08,
				PackageNamespace	= 0x16,
				PackageInternalNs	= 0x17,
				ProtectedNamespace	= 0x18,
				ExplicitNamespace	= 0x19,
				StaticProtectedNs	= 0x1A,
				PrivateNs			= 0x05,
			};};
			mok::kind kind;
			uint val;
		};
		array_<option> options;
		uint_array param_names;
	};
	friend method METHOD(const byte*&);
	typedef array_<method> methods;
	//
	struct metadata {
		uint name;
		struct item {
			uint key, value;
		};
		array_<item> items;
	};
	friend metadata METADATA(const byte*&);
	typedef array_<metadata> metadatas;
	//
	struct trait {
		struct itt { enum types {
			Slot		= 0,
			Method		= 1,
			Getter		= 2,
			Setter		= 3,
			Class		= 4,
			Function	= 5,
			Const		= 6,
		};};
		struct ita { enum attributes {
			Final		= 0x1,
			Override	= 0x2,
			Metadata	= 0x4,
		};};
		uint name, kind;
		uint slot_id, type_name, vindex, vkind, classi, function, disp_id, method;
		uint_array metadata;
	};
	//
	struct instance {
		uint name, super_name;
		struct oif { enum flags {
			ClassSealed			= 0x01,
			ClassFinal			= 0x02,
			ClassInterface		= 0x04,
			ClassProtectedNs	= 0x08,
		};};
		uint flags;
		uint protected_ns;
		uint_array interfaces;
		uint iinit;
		array_<trait> traits;
	};
	friend trait TRAIT(const byte*&);
	friend instance INSTANCE(const byte*&);
	typedef array_<instance> instances;
	//
	struct classinfo {
		uint cinit;
		array_<trait> traits;
	};
	friend classinfo CLASS(const byte*&);
	typedef array_<classinfo> classinfos;
	//
	struct script {
		uint init;
		array_<trait> traits;
	};
	friend script SCRIPT(const byte*&);
	typedef array_<script> scripts;
	//
	struct methodbody {
		uint method, max_stack, local_count, init_scope_depth, max_scope_depth;
		byte_array code;
		struct exception { uint from, to, target, exc_type, var_name; };
		array_<exception> exceptions;
		array_<trait> traits;
	};
	friend methodbody METHODBODY(const byte*&);
	typedef array_<methodbody> methodbodys;
	//
	struct sytring_ref { uint ID; };
	struct object_ref { uint ID; };
	typedef make_typelist_<bool, uint, sint, rbig, sytring_ref, object_ref>::type types;
	typedef variant_<types, false> value;
	typedef array_<value> values;
	//
	struct segment {
		struct env { values locals, stack, scope; };
		//inline sint get_int(uint _i) const { return m_ints[_i]; }
		//inline uint get_uint(uint _i) const { return m_uints[_i]; }
		//inline rbig get_double(uint _i) const { return m_doubles[_i]; }
		//inline const wstring& get_string(uint _i) const { return m_strings[_i]; }
		//inline const wstring& get_namespace(uint _i) const { return m_strings[m_namespaces[_i].string]; }

		segment(machine &_machine, pointer _data, uint _size);
		void run_script(uint _index = bad_ID) const;
		void run(uint _methodbody, env &_env) const;
	private:
		machine &m_machine;
		sint_array m_ints; uint_array m_uints; rbig_array m_doubles; wstring_array m_strings;
		namespaces m_namespaces; ns_sets m_ns_sets; multinames m_multinames;
		methods m_methods; instances m_instances; classinfos m_classinfos;
		scripts m_scripts; methodbodys m_methodbodys;
	};
	typedef array_<segment*> segments;
	//
	struct object {
		struct prop { value v; uint f; wstring n; };
		inline uint ID() const { return m_ID; }
		inline void set_ID(uint _ID) { m_ID = _ID; }
		void set(const wstring &_name, const value &_value, uint _slot = bad_ID);
		const value& get(uint _slot);
		const value& get(const wstring &_name);
	private:
		uint m_ID; array_<prop> m_props;
	};
	typedef array_<object> objects;
	uint new_object();
	void set_object_prop(uint _ID, const wstring &_name, const value &_value, uint _slot = bad_ID);
	const value& get_object_prop(uint _ID, uint _slot);
	const value& get_object_prop(uint _ID, const wstring &_name);
	//
	sint_array m_ints;
	uint_array m_uints;
	rbig_array m_doubles;
	wstring_array m_strings;
	segments m_segments;
	objects m_objects;
};
