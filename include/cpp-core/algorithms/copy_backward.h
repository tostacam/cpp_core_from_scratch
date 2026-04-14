// std::copy_backward()

namespace cpp_core{

template <typename InIt, typename OutIt>
OutIt copy_backward(InIt first, InIt last, OutIt dest) {
  for( ; first != last; )
    *(--dest) = *(--last);
  return dest;
}

}
