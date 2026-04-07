// std::move()

#pragma once
#include "../utilities/move.h"

template <typename InIt, typename OutIt>
OutIt move(InIt first, InIt last, OutIt dest){
  for(; first != last; ++first, ++dest)
    *(dest) = ::move(*first);
  return dest;
}
