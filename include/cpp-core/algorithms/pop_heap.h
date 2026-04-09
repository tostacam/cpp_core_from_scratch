// std::pop_heap()

#pragma once

#include "../utilities/swap.h"

template <typename It>
void pop_heap(It first, It last){
  swap(*first, *(last - 1));

  It root = first;
  It end = last - 1;

  while(true){
    auto left = first + (2 * (root - first) + 1);
    auto right = left + 1;

    if(left >= end)
      break;

    It largest = left;

    if(right < end && *left < *right)
      largest = right;

    if(*root < *largest){
      swap(*root, *largest);
      root = largest;
    }
    else 
      break;
  }
}
