// std::lower_bound()

#pragma once

namespace cpp_core{

template <typename It, typename T>
It lower_bound(It first, It last, const T& value){
  while(first < last){
    It mid = first + (last - first) / 2;

    if(*mid < value)
      first = mid + 1;
    else
      last = mid;
  }
  return first;
}

}
