/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	viktor.reutskyy@gmail.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

// _functor_base

struct _functor_base {
	typedef notype arg0;
	typedef notype arg1;
	typedef notype arg2;
	typedef notype arg3;
	typedef notype arg4;
	typedef notype arg5;
	typedef notype arg6;
	typedef notype arg7;
	typedef notype arg8;
	typedef notype arg9;

	virtual ~_functor_base() {}
	virtual _functor_base& clone() const = 0;
};

// _functor_core_

template<typename _Rettype, typename _Arglist> struct _functor_core_;

template<typename _R>
struct _functor_core_<_R, make_typelist_<notype> > : _functor_base {
	typedef _R rettype;
	virtual rettype operator () () const = 0;
};
template<typename _R, typename _A0>
struct _functor_core_<_R, make_typelist_<_A0> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	virtual rettype operator () (arg0) const = 0;
};
template<typename _R, typename _A0, typename _A1>
struct _functor_core_<_R, make_typelist_<_A0, _A1> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	typedef typename traits_<_A1>::parameter arg1;
	virtual rettype operator () (arg0, arg1) const = 0;
};
template<typename _R, typename _A0, typename _A1, typename _A2>
struct _functor_core_<_R, make_typelist_<_A0, _A1, _A2> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	typedef typename traits_<_A1>::parameter arg1;
	typedef typename traits_<_A2>::parameter arg2;
	virtual rettype operator () (arg0, arg1, arg2) const = 0;
};
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3>
struct _functor_core_<_R, make_typelist_<_A0, _A1, _A2, _A3> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	typedef typename traits_<_A1>::parameter arg1;
	typedef typename traits_<_A2>::parameter arg2;
	typedef typename traits_<_A3>::parameter arg3;
	virtual rettype operator () (arg0, arg1, arg2, arg3) const = 0;
};
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4>
struct _functor_core_<_R, make_typelist_<_A0, _A1, _A2, _A3, _A4> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	typedef typename traits_<_A1>::parameter arg1;
	typedef typename traits_<_A2>::parameter arg2;
	typedef typename traits_<_A3>::parameter arg3;
	typedef typename traits_<_A4>::parameter arg4;
	virtual rettype operator () (arg0, arg1, arg2, arg3, arg4) const = 0;
};
template<typename _R, typename _A0, typename _A1, typename _A2, typename _A3, typename _A4, typename _A5>
struct _functor_core_<_R, make_typelist_<_A0, _A1, _A2, _A3, _A4, _A5> > : _functor_base {
	typedef _R rettype;
	typedef typename traits_<_A0>::parameter arg0;
	typedef typename traits_<_A1>::parameter arg1;
	typedef typename traits_<_A2>::parameter arg2;
	typedef typename traits_<_A3>::parameter arg3;
	typedef typename traits_<_A4>::parameter arg4;
	typedef typename traits_<_A5>::parameter arg5;
	virtual rettype operator () (arg0, arg1, arg2, arg3, arg4, arg5) const = 0;
};

// _functor_handler_

template<typename _Functor, typename _Fn> struct _functor_handler_ : _Functor::core {
	typedef typename _Functor::core core;
	typedef typename core::rettype rettype;
	typedef typename core::arg0 arg0;
	typedef typename core::arg1 arg1;
	typedef typename core::arg2 arg2;
	typedef typename core::arg3 arg3;
	typedef typename core::arg4 arg4;
	typedef typename core::arg5 arg5;
	typedef typename core::arg6 arg6;
	typedef typename core::arg7 arg7;
	typedef typename core::arg8 arg8;
	typedef typename core::arg9 arg9;

	inline _functor_handler_(_Fn _fn) : m_fn(_fn) {}
	inline _functor_handler_(const _functor_handler_ &_f) : m_fn(_f.m_fn) {}

	virtual _functor_handler_& clone() const { return * new _functor_handler_(*this); }

	inline rettype operator () () const {
		return m_fn();
	}
	inline rettype operator () (arg0 _a0) const {
		return m_fn(_a0);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1) const {
		return m_fn(_a0, _a1);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2) const {
		return m_fn(_a0, _a1, _a2);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3) const {
		return m_fn(_a0, _a1, _a2, _a3);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4) const {
		return m_fn(_a0, _a1, _a2, _a3, _a4);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4, arg4 _a5) const {
		return m_fn(_a0, _a1, _a2, _a3, _a4, _a5);
	}

private:
	friend _functor_handler_;
	_Fn m_fn;
};

// _functor_method_handler_

template<typename _Functor, typename _Object, typename _Method> struct _functor_method_handler_ : _Functor::core {
	typedef typename _Functor::core core;
	typedef typename core::rettype rettype;
	typedef typename core::arg0 arg0;
	typedef typename core::arg1 arg1;
	typedef typename core::arg2 arg2;
	typedef typename core::arg3 arg3;
	typedef typename core::arg4 arg4;
	typedef typename core::arg5 arg5;
	typedef typename core::arg6 arg6;
	typedef typename core::arg7 arg7;
	typedef typename core::arg8 arg8;
	typedef typename core::arg9 arg9;

	inline _functor_method_handler_(_Object &_object, const _Method &_method) : m_object(_object), m_method(_method) {}
	inline _functor_method_handler_(const _functor_method_handler_ &_f) : m_object(_f.m_object), m_method(_f.m_method) {}

	virtual _functor_method_handler_& clone() const { return * new _functor_method_handler_(*this); }

	inline rettype operator () () const {
		return (m_object.*m_method)();
	}
	inline rettype operator () (arg0 _a0) const {
		return (m_object.*m_method)(_a0);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1) const {
		return (m_object.*m_method)(_a0, _a1);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2) const {
		return (m_object.*m_method)(_a0, _a1, _a2);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3) const {
		return (m_object.*m_method)(_a0, _a1, _a2, _a3);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4) const {
		return (m_object.*m_method)(_a0, _a1, _a2, _a3, _a4);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4, arg5 _a5) const {
		return (m_object.*m_method)(_a0, _a1, _a2, _a3, _a4, _a5);
	}

private:
	friend _functor_method_handler_;
	_Object &m_object; _Method m_method;
};

///	A functor with up to ten arguments
/**	[TODO]
 */
template<
	typename _R = void,
	typename _A0 = notype, typename _A1 = notype, typename _A2 = notype, typename _A3 = notype, typename _A4 = notype,
	typename _A5 = notype, typename _A6 = notype, typename _A7 = notype, typename _A8 = notype, typename _A9 = notype
> struct functor_ {
	typedef _R rettype;
	typedef make_typelist_<_A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7, _A8, _A9> arglist;
	typedef _functor_core_<rettype, arglist> core;
	typedef typename core::arg0 arg0;
	typedef typename core::arg1 arg1;
	typedef typename core::arg2 arg2;
	typedef typename core::arg3 arg3;
	typedef typename core::arg4 arg4;
	typedef typename core::arg5 arg5;
	typedef typename core::arg6 arg6;
	typedef typename core::arg7 arg7;
	typedef typename core::arg8 arg8;
	typedef typename core::arg9 arg9;

	inline functor_() : m_core_p(0) {}
	template<typename _Fn> inline functor_(_Fn _fn) : m_core_p(new _functor_handler_<functor_, _Fn>(_fn)) {}
	template<typename _Object, typename _Method> inline functor_(_Object &_object, const _Method &_method) : m_core_p(new _functor_method_handler_<functor_, _Object, _Method>(_object, _method)) {}
	inline functor_(const functor_ &_f) : m_core_p(static_cast<core*>(&_f.m_core_p->clone())) {}
	inline functor_& operator = (const functor_ &_f) { if(m_core_p) delete m_core_p; m_core_p = static_cast<core*>(&_f.m_core_p->clone()); return *this; }
	inline bool valid() const { return m_core_p != 0; }
	~functor_() { delete m_core_p; }

	inline rettype operator () () const {
		return (*m_core_p)();
	}
	inline rettype operator () (arg0 _a0) const {
		return (*m_core_p)(_a0);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1) const {
		return (*m_core_p)(_a0, _a1);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2) const {
		return (*m_core_p)(_a0, _a1, _a2);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3) const {
		return (*m_core_p)(_a0, _a1, _a2, _a3);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4) const {
		return (*m_core_p)(_a0, _a1, _a2, _a3, _a4);
	}
	inline rettype operator () (arg0 _a0, arg1 _a1, arg2 _a2, arg3 _a3, arg4 _a4, arg5 _a5) const {
		return (*m_core_p)(_a0, _a1, _a2, _a3, _a4, _a5);
	}

private:
	friend functor_;
	core *m_core_p;
};
typedef functor_<> functor;
