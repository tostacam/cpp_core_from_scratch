// std::rotate()

#pragma once

#include "reverse.h"

namespace cpp_core{

template <typename It>
void rotate(It first, It middle, It last){
  reverse(first, middle);
  reverse(middle, last);
  reverse(first, last);
}

}
