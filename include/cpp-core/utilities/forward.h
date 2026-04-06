// std::forward<T>
// - maintain ravlue/lvalue-ness

#pragma once
#include "remove_reference.h"

template <typename T>
struct is_lvalue_reference {
  static constexpr bool value = false;
};

template <typename T>
struct is_lvalue_reference<T&> {
  static constexpr bool value = false;
};

template <typename T>
T&& forward(remove_reference_t<T>& t){
  return static_cast<T&&>(t);  
}

template <typename T>
T&& forward(remove_reference_t<T>&& t){
  /* stops forwarding of rvalue as lvalue */
  static_assert(!is_lvalue_reference<T>::value, "wrong forward");
  return static_cast<T&&>(t);
}
