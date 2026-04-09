// std::sort()

#pragma once

#include "../utilities/swap.h"

template <typename It>
It partition_qs(It first, It last){
  auto pivot = *(last - 1);
  It i = first;

  for(It j = first; j != last - 1; ++j)
    if(*j < pivot){
      swap(*i, *j);
      ++i;
    }

  swap(*i, *(last - 1));
  return i;
}

template <typename It>
void sort(It first, It last){
  if(last - first <= 1)
    return;

  It mid = first + (last - first) / 2;
  if(*mid < *first)
    swap(*mid, *first);
  if(*(last - 1) < *first)
    swap(*(last - 1), *first);
  if(*(last - 1) < *mid)
    swap(*(last - 1), *mid);
  swap(*mid, *(last -1));

  It p = partition_qs(first, last);

  sort(first, p);
  sort(p + 1, last);  
}

template <typename It, typename Comp>
It partition_qs(It first, It last, Comp comp){
  auto pivot = *(last - 1);
  It i = first;

  for(It j = first; j != last - 1; ++j)
    if(comp(*j, pivot)){
      swap(*i, *j);
      ++i;
    }

  swap(*i, *(last - 1));
  return i;
}

template <typename It, typename Comp>
void sort(It first, It last, Comp comp){
  if(last - first <= 1)
    return;

  It mid = first + (last - first) / 2;
  if(comp(*mid, *first))
    swap(*mid, *first);
  if(comp(*(last - 1), *first))
    swap(*(last - 1), *first);
  if(comp(*(last - 1), *mid))
    swap(*(last - 1), *mid);
  swap(*mid, *(last -1));

  It p = partition_qs(first, last, comp);

  sort(first, p, comp);
  sort(p + 1, last, comp);
}
