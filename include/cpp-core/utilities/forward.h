// std::forward<T>

#pragma once
#include "remove_reference.h"

template <typename T>
T&& forward(remove_reference_t<T>& t){
  return static_cast<T&&>(t);  
}

template <typename T>
T&& forward(remove_reference_t<T>&& t){
  return static_cast<T&&>(t);
}
