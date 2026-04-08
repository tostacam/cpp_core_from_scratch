// std::advance()

#pragma once

#include "iterator_traits.h"

/* internal helper: input iterator */
template <typename It, typename Dist>
void advance_impl(It& it, Dist n, input_iterator_tag){
  while(n-- > 0)
    ++it;
}

/* internal helper: bidirectional iterator */
template <typename It, typename Dist>
void advance_impl(It& it, Dist n, bidirectional_iterator_tag){
  if(n >= 0)
    while(n-- > 0)
      ++it;
  else
    while(n++ < 0)
      --it;
}

/* internal helper: random access iterator */
template <typename It, typename Dist>
void advance_impl(It& it, Dist n, random_access_iterator_tag){
  it += n; 
}

/* public interface */
template <typename It, typename Dist>
void advance(It& it, Dist n){
  using category = typename iterator_traits<It>::iterator_category;
  advance_impl(it, n, category{});
}
