// std::equal()

namespace cpp_core{

template <typename It1, typename It2>
bool equal(It1 first, It1 last, It2 dest){
  for( ; first != last; ++first, ++dest)
    if(*first != *dest)
      return false;
  return true;
}

}
