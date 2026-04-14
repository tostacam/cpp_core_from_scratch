// std::distance()

#pragma once
#include "iterator_traits.h"

namespace cpp_core{

/* internal helper: input iterator */
template <typename It>
typename iterator_traits<It>::difference_type distance_impl(It first, It last, input_iterator_tag){
  typename iterator_traits<It>::difference_type n = 0;
  for(; first != last; ++first)
    ++n;
  return n;
}

/* internal helper: random access iterator */
template <typename It>
typename iterator_traits<It>::difference_type distance_impl(It first, It last, random_access_iterator_tag){
  return last - first;
}

/* public interface */
template <typename It>
typename iterator_traits<It>::difference_type distance(It first, It last){
  using category = typename iterator_traits<It>::iterator_category;
  return distance_impl(first, last, category{});
}

}
