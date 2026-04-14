// std::reverse()

#pragma once

#include "../utilities/swap.h"

namespace cpp_core{

template <typename It>
void reverse(It first, It last){
  while(first < last){
    --last;
    swap(*first, *last);
    ++first;
  }
}

}
