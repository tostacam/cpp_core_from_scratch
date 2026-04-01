// std::vector<T>

#include <cstddef>  /* for size_t */

template <typename T>
class vector{
public:
  // a vector does not own memory until it does
  vector() : data_(nullptr), size_(0), capacity_(0) {}

  ~vector(){
    for(size_t i = 0; i < size_; ++i)
      data_[i].~T();          /* destroying each object */
    ::operator delete(data_); /* releasing raw memory buffer */
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;
};
