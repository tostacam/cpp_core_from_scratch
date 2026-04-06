// std::move()
// - casts to an rvalue reference

#pragma once
#include "remove_reference.h"

template <typename T>
remove_reference_t<T>&& move(T&& t){
  return static_cast<remove_reference_t<T>&&>(t);
}
