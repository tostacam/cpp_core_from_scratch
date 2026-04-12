// std::allocator<T>
// - https://en.cppreference.com/w/cpp/memory/allocator.html

#include <cstddef>  /* for size_t */

template <typename T>
struct allocator{
  using value_type = T;

  T* allocate(size_t n){
    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  void deallocate(T* p, size_t n){
    ::operator delete(p);
  }

  template <typename... Args>
  void construct(T* p, Args&&... args){
    new (p) T(::forward<Args>(args)...);
  }

  void destroy(T* p){
    p->~T();
  }
};
