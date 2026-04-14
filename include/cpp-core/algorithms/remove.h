// std::remove()

#pragma once

namespace cpp_core{

template <typename It, typename T>
It remove(It first, It last, const T& value){
  It dest = first;
  for(; first != last; ++first)
    if(*first != value)
      *(dest++) = *first;
  return dest;
}

}
