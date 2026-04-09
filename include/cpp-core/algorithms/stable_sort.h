// std::stable_sort()

#pragma once

#include "../iterator/iterator_traits.h"

template <typename It1, typename It2, typename OutIt>
OutIt merge(It1 f1, It1 l1, It2 f2, It2 l2, OutIt dest){
  while(f1 != l1 && f2 != l2){
    if(*f2 < *f1)
      *dest++ = *f2++;
    else
      *dest++ = *f1++;
  }

  while(f1 != l1)
    *dest++ = *f1++;
  while(f2 != l2)
    *dest++ = *f2++;

  return dest;
}

template <typename It>
void stable_sort(It first, It last){
  iterator_traits<It>::difference_type n = last - first;
  if(n <= 1) 
    return;

  It mid = first + (last - first) / 2;

  stable_sort(first, mid);
  stable_sort(mid, last);

  /* buffer */
  using T = typename iterator_traits<It>::value_type;
  T* buffer = new T[n];

  /* merge into buffer */
  merge(first, mid, mid, last, buffer);

  /* copy buffer back */
  copy(buffer, buffer + n, first);

  /* release buffer */
  delete[] buffer;
}
