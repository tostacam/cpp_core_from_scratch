// std::make_heap()

#pragma once

#include "../utilities/swap.h"

namespace cpp_core{

template <typename It>
void make_heap(It first, It last){
  if(last - first <= 1)
    return;

  for(auto i = first + ((last - first) / 2 - 1); ; --i){
    It root = i;

    while(true){
      auto left = first + (2 * (root - first) + 1);
      auto right = left + 1;

      if(left >= last)
        break;

      It largest = left;

      if(right < last && *left < *right)
        largest = right;

      if(*root < *largest){
        swap(*root, *largest);
        root = largest;
      }
      else
        break;
    }

    if(i == first)
      break;
  }
}

}
