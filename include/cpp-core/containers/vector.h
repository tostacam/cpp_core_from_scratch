// std::vector<T>

#pragma once
#include <cstddef>  /* for size_t */
#include <utility>  /* for move */

template <typename T>
class vector{
public:
  /* a vector does not own memory until it does */
  vector() : data_(nullptr), size_(0), capacity_(0) {}
  
  vector(const vector& other){
    T* new_data = static_cast<T*>(::operator new(sizeof(T) * other.capacity_));

    data_ = new_data; 
    size_ = other.size_;
    capacity_ = other.capacity_;

    for(size_t i = 0; i < other.size_; ++i)
      new (data_ + i) T(other.data_[i]);
  }

  vector& operator=(const vector& other){
    if(this == &other)    /* other = other; */
      return *this;
    
    T* new_data = static_cast<T*>(::operator new(sizeof(T) * other.capacity_));
    for(size_t i = 0; i < other.size_; ++i)
      new (new_data + i) T(other.data_[i]);

    destroy_and_deallocate();   /* if an operation fails, object */
                                /* should remain unchanged */
    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
  }

  vector(vector&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  vector& operator=(vector&& other){
    if(this == &other)
      return *this;

    destroy_and_deallocate();
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
  }

  T& operator[](size_t i){
    return data_[i];  /* no bounds checking, UB */
  }

  const T& operator[](size_t i) const {
    return data_[i];  /* no bounds checking, UB */
  }
 
  ~vector(){
    destroy_and_deallocate();
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

  void push_back(const T& value){
    if(size_ >= capacity_)
      grow();
    new (data_ + size_) T(value);
    ++size_;
  }

  void pop_back(){
    if(size_ > 0){
      --size_;
      data_[size_].~T();
    }
  }

  template<typename... Args>
  void emplace_back(Args&&... args){
    if(size_ >= capacity_)
      grow();
    new (data_ + size_) T(std::forward<Args>(args)...);
    ++size_;
  }

  void reserve(const size_t& new_capacity){
    if(new_capacity <= capacity_)
      return;
    reallocate(new_capacity);
  }

  void grow(){
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2; /* increasing capacity */
    reallocate(new_capacity);
  }

  void reallocate(size_t new_capacity){
    T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

    size_t temp = size_, constructed = 0;
    try {
      for(size_t i = 0; i < size_; ++i){
        new (new_data + i) T(std::move(data_[i]));
        ++constructed;
      }
    } catch(...) {
      for(size_t j = 0; j < constructed; ++j)
        new_data[j].~T();
      ::operator delete(new_data);
      throw;
    }

    destroy_and_deallocate();
    data_ = new_data;
    size_ = temp;
    capacity_ = new_capacity;
  }

  void destroy_and_deallocate(){
    for(size_t i = 0; i < size_; ++i)
      data_[i].~T();          /* destroying each element */
    ::operator delete(data_); /* releasing raw memory */

    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  void clear(){
    for(size_t i = 0; i < size_; ++i)
     data_[i].~T();
    size_ = 0; 
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;
};
