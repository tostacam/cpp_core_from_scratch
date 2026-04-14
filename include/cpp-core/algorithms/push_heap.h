// std::push_heap()

#pragma once

#include "../utilities/swap.h"

namespace cpp_core{

template <typename It>
void push_heap(It first, It last){
  auto child = last - 1;
  
  while(child > first){
    auto parent = first + (child - 1 - first) / 2;
    
    if(*parent < *child){
      swap(*parent, *child);
      child = parent;
    }
    else 
      break;
  }
}

}
