// std::fill()

namespace cpp_core{

template <typename It, typename T>
void fill(It first, It last, const T& value){
  for( ; first != last; ++first)
    *first = value;
}

}
