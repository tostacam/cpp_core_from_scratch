// std::move_backward()

#pragma once
#include "../utilities/move.h"

namespace cpp_core{

template <typename InIt, typename OutIt>
OutIt move_backward(InIt first, InIt last, OutIt dest){
  for(; first != last;)
    *(--dest) = move(*(--last));
  return dest;
}

}
