// partition()

#pragma once
#include "../utilities/swap.h"

namespace cpp_core{

template <typename It, typename Pred>
It partition(It first, It last, Pred pred){
  It part = first;
  for(; first != last; ++first)
    if(pred(*first)){
      if(first == part)
        ++part;
      else 
        swap(*part++, *first);
    }
  return part;
}

}
