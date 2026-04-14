// partition_copy()

#pragma once
#include "../utilities/pair.h"

namespace cpp_core{

template <typename It, typename OutIt1, typename OutIt2, typename Pred>
pair<OutIt1, OutIt2> partition_copy(It first, It last, OutIt1 out_true, OutIt2 out_false, Pred pred){
  for(; first != last; ++first)
    if(pred(*first))
      *out_true++ = *first;
    else
      *out_false++ = *first;
  return pair{out_true, out_false};
}

}
