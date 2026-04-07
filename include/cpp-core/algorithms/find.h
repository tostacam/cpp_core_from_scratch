// find()

template <typename It, typename T>
It find(It first, It last, const T& value){
  for( ; first != last; ++first)
    if(*first == value)
      return first;
  return last;
}
