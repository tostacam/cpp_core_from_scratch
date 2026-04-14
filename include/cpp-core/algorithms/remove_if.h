// remove_if()

namespace cpp_core{

template <typename It, typename Pred>
It remove_if(It first, It last, Pred pred){
  It dest = first;
  for(; first != last; ++first)
    if(!pred(*first))
      *(dest++) = *first;
  return dest;
}

}
