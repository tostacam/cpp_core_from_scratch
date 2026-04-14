// std::fill_n()

namespace cpp_core{

template <typename It, typename Size, typename T>
It fill_n(It first, Size n, const T& value){
  for( ; n > 0; --n, ++first)
    *first = value;
  return first;
}

}
