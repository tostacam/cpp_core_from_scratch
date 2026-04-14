// std::find_if()

namespace cpp_core{

template<typename It, typename Pred>
It find_if(It first, It last, Pred pred){
  for(; first != last; ++first)
    if(pred(*first)) return first;
  return last;
}

}
