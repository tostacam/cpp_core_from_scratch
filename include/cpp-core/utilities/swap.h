// std::swap()
// - use move operations to swap data

#pragma once
#include "move.h"

namespace cpp_core{

template <typename T>
void swap(T& a, T& b){
  T temp = move(a);
  a = move(b);
  b = move(temp);
}

}
