// std::vector<T>

#pragma once
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

  void push_back(T value){
    if(size_ < capacity_){
      new (data_ + size_) T(value);
      ++size_;
    }
    else{
      size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2; /* increasing capacity */
      T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

      for(size_t i = 0; i < size_; ++i)
        new (new_data + i) T(data_[i]);

      for(size_t i = 0; i < size_; ++i)
        data_[i].~T();
      ::operator delete(data_);

      data_ = new_data;
      capacity_ = new_capacity;

      new (data_ + size_) T(value);
      ++size_;
    }
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;
};
