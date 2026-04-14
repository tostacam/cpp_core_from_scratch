// remove_if()

namespace cpp_core{

template <typename It, typename Pred>
It remove_if(It first, It last, Pred pred){
  for(It dest = first; first != last; ++first)
    if(!pred(*first))
      *(dest++) = *first;
  return dest;
}

}
