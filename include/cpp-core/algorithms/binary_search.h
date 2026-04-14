// std::binary_search()

#pragma once

#include "lower_bound.h"

namespace cpp_core{

template <typename It, typename T>
bool binary_search(It first, It last, const T& value){
  It it = lower_bound(first, last, value);
  return (it != last && !(value < *it));
}

}
