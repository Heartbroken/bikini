#pragma once

namespace commands { /*--------------------------------------------------------------------------*/

struct _command;

void create();
void destroy();

template <typename _F>
inline void add(const bk::achar* _name, const _F &_functor);
void remove(const bk::achar* _name);

#include "commands.inl"

} /* namespace commands -------------------------------------------------------------------------*/
