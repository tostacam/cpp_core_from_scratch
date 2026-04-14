// std::sort_heap()

#include "pop_heap.h"

namespace cpp_core{

template <typename It>
void sort_heap(It first, It last){
  while(last - first > 1){
    pop_heap(first, last);
    --last;
  }
}

}
