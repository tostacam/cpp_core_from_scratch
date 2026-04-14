// std::unique()

namespace cpp_core{

template <typename It>
It unique(It first, It last){
  if(first == last)
    return last;

  It dest = first;

  while(++first != last){
    if(!(*dest == *first)){
      ++dest;
      *dest = *first;
    }
  }

  return ++dest;
}

}
