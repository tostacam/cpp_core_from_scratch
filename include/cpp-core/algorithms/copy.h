// copy()

template <typename InIt, typename OutIt>
OutIt copy(InIt first, InIt last, OutIt dest){
  for( ; first != last; ++first, ++dest)
    *dest = *first;
  return dest;
}
