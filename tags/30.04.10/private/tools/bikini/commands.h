#pragma once

namespace commands { //----------------------------------------------------------------------------

// Create command system
void create();

// Destroy command system
void destroy();

// Add command
template <typename _F>
inline void add(const bk::achar* _name, const _F &_functor);

// Remove command
void remove(const bk::achar* _name);

#include "commands.inl"

} // namespace commands ---------------------------------------------------------------------------
