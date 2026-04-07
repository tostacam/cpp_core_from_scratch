// transform()

template <typename It, typename OutIt, typename Pred>
OutIt transform(It first, It last, OutIt dest, Pred pred){
  for(; first != last; ++first, ++dest)
    *(dest) = pred(*first);
  return dest;  
}
