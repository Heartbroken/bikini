/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008-2009 Viktor Reutskyy
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#include "header.hpp"

namespace bk { /*--------------------------------------------------------------------------------*/

namespace flash { /*-----------------------------------------------------------------------------*/

namespace as { /*--------------------------------------------------------------------------------*/

using namespace avmplus;

struct _mmgc_helper {
	_mmgc_helper() : m_GC_p(0) {
		MMgc::GCHeap::Init();
		MMgc::FixedMalloc::Init();
	}
	~_mmgc_helper() {
		if(m_GC_p) delete m_GC_p;
		MMgc::FixedMalloc::Destroy();
		MMgc::GCHeap::Destroy();
	}
	MMgc::GC* get_GC() {
		if(m_GC_p == 0) m_GC_p = new MMgc::GC(MMgc::GCHeap::GetGCHeap());
		return m_GC_p;
	}
	//MMgc::GCHeap* get_heap() {
	//	return MMgc::GCHeap::GetGCHeap();
	//}
private:
	MMgc::GC *m_GC_p;
};
static _mmgc_helper sg_mmgc_helper;

// avm2

avm2::avm2() : avmplus::AvmCore(sg_mmgc_helper.get_GC()), m_toplevel_p(0) {
	//config.verbose = true;
	initBuiltinPool();
	m_toplevel_p = initTopLevel();
}
bool avm2::do_ABC(pointer _data, uint _size) {
	avmplus::ReadOnlyScriptBufferImpl l_script((byte*)_data, _size);
	TRY(this, kCatchAction_ReportAsError) {
		handleActionBlock(avmplus::ScriptBuffer(&l_script), 0, m_toplevel_p->domainEnv(), m_toplevel_p, 0, 0);
	} CATCH(avmplus::Exception* e) {
		std::cerr << string(e->atom) << "\n";
	} END_CATCH
	END_TRY
	return true;
}
void avm2::interrupt(avmplus::MethodEnv *env) {
}
void avm2::stackOverflow(avmplus::MethodEnv *env) {
}

} /* namespace as -------------------------------------------------------------------------------*/

} /* namespace flash ----------------------------------------------------------------------------*/

} /* namespace bk -------------------------------------------------------------------------------*/

//
#ifdef AVMPLUS_MOPS
namespace avmplus {
 	// memory object glue
 	bool Domain::isMemoryObject(Traits *t) const
 	{
		assert(0);
		//Traits *cur = t;

		//// walk the traits to find a builtin pool
		//while(cur && !cur->pool->isBuiltin)
		//	cur = cur->base;

		//// have a traits with a builtin pool
		//if(cur)
		//{
		//	Stringp uri = core->constantString("flash.utils");
		//	Namespace* ns = core->internNamespace(core->newNamespace(uri));
		//	// try to get traits from flash.utils.ByteArray
		//	Traits *baTraits = cur->pool->getTraits(core->constantString("ByteArray"), ns);
		//	// and see if the original traits contains it!
		//	return t->containsInterface(baTraits) != 0;
		//}
		return false;
 	}
 
 	bool Domain::globalMemorySubscribe(ScriptObject *mem) const
 	{
		assert(0);
		//if(isMemoryObject(mem->traits()))
		//{
		//	avmshell::ByteArray::GlobalMemoryNotifyFunc notify = &Domain::notifyGlobalMemoryChanged;
		//	return ((avmshell::ByteArrayObject *)mem)->globalMemorySubscribe(this, notify);
		//}
		return false;
 	}
 
 	bool Domain::globalMemoryUnsubscribe(ScriptObject *mem) const
 	{
		assert(0);
		//if(isMemoryObject(mem->traits()))
		//{
		//	return ((avmshell::ByteArrayObject *)mem)->globalMemoryUnsubscribe(this);
		//}
		return false;
 	}
}	
#endif
