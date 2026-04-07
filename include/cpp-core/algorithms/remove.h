// remove()

template <typename It, typename T>
It remove(It first, It last, const T& value){
  for(It dest = first; first != last; ++first)
    if(*first != value)
      *(dest++) = *first;
  return dest;
}
