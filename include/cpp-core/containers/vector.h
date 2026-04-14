// std::vector<T>

#pragma once
#include <cstddef>  /* for size_t */
#include "../utilities/move.h"
#include "../iterator/distance.h"
#include "../memory/allocator.h"

namespace cpp_core{

template <typename T>
class vector{
public:
  /* a vector does not own memory until it does */
  vector() : data_(nullptr), size_(0), capacity_(0) {}
  
  template<typename It>
  vector(It first, It last) : data_(nullptr), size_(0), capacity_(0) {
    size_t constructed = 0;
    try{
      size_t dist = distance(first, last);
      reserve(dist);
      for( ; first != last; ++first){
        alloc_.construct(data_ + size_, *first);
        ++size_;
        ++constructed;
      }
    } catch(...) {
      for(size_t i = 0; i < constructed; ++i)
        alloc_.destroy(data_ + i);
      alloc_.deallocate(data_);
      throw;
    }
  }

  vector(const vector& other){
    T* new_data = alloc_.allocate(other.capacity_);

    data_ = new_data; 
    size_ = other.size_;
    capacity_ = other.capacity_;

    for(size_t i = 0; i < other.size_; ++i)
      alloc_.construct(data_ + i, other.data_[i]);
  }

  vector& operator=(const vector& other){
    if(this == &other)    /* other = other; */
      return *this;

    T* new_data = alloc_.allocate(other.capacity_);
    for(size_t i = 0; i < other.size_; ++i)
      alloc_.construct(new_data + i, other.data_[i]);

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

  bool empty() const {
    if(size_ == 0)
      return true;
    return false;
 }

  void push_back(const T& value){
    if(size_ >= capacity_)
      grow();
    alloc_.construct(data_ + size_, value);
    ++size_;
  }

  void push_back(T&& value){
    if(size_ >= capacity_)
      grow();
    alloc_.construct(data_ + size_, forward<T>(value));
    ++size_;
  }

  T* insert(T* pos, const T& value){
    size_t dist = distance(begin(), pos);
    if(size_ == capacity_){
      grow();
      pos = begin() + dist;
    }

    for(size_t i = size_; i > dist; --i){
      alloc_.construct(data_ + i, move(data_[i - 1]));
      alloc_.destroy(data_ + i - 1);
    }

    alloc_.construct(pos, value);
    ++size_;

    return pos;
  }

  T* erase(T* pos){
    for(T* it = pos; it < end() - 1; ++it){
      alloc_.construct(it, move(*(it + 1)));
      alloc_.destroy(it + 1);
    }
    alloc_.destroy(data_ + size_ - 1);
    --size_;

    return pos;
  }

  void pop_back(){
    if(size_ > 0){
      --size_;
      alloc_.destroy(data_ + size_);
    }
  }

  template<typename... Args>
  void emplace_back(Args&&... args){
    if(size_ >= capacity_)
      grow();
    alloc_.construct(data_ + size_, forward<Args>(args)...);
    ++size_;
  }

  void resize(size_t new_size){
    if(new_size < size_){
      for(size_t i = new_size; i < size_; ++i)
        alloc_.destroy(data_ + i);
      size_ = new_size;
    }
    else if(new_size > size_){
      if(new_size > capacity_)
        reallocate(new_size);

      for(size_t i = size_; i < new_size; ++i)
        alloc_.construct(data_ + i, T());

      size_ = new_size;
    }
  }

  void resize(size_t new_size, const T& value){
    if(new_size < size_){
      for(size_t i = new_size; i < size_; ++i)
        alloc_.destroy(data_ + i);
      size_ = new_size;
    }
    else if(new_size > size_){
      if(new_size > capacity_)
        reallocate(new_size);

      for(size_t i = size_; i < new_size; ++i)
        alloc_.construct(data_ + i, value);

      size_ = new_size;
    } 
  }

  void assign(size_t count, const T& value){
    if(count <= capacity_){
      size_t i = 0;
      
      for(; i < size_ && i < count; ++i)
        data_[i] = value;

      for(; i < count; ++i)
        alloc_.construct(data_ + i, value);

      for(size_t j = count; j < size_; ++j)
        alloc_.destroy(data_ + j);

      size_ = count;
    }
    else{
      reallocate(count);

      for(size_t i = 0; i < count; ++i)
        alloc_.destroy(data_ + i, value);
      
      size_ = count;
    }
  }

  T* begin(){
    return data_;
  }

  const T* begin() const {
    return data_;
  }

  T* end(){
    return (data_ + size_);
  }

  const T* end() const {
    return (data_ + size_);
  }

  T* data(){
    return data_;
  }

  const T* data() const {
    return data_;
  }

  T& front(){
    return data_[0];
  }

  const T& front() const {
    return data_[0];
  }

  T& back(){
    return data_[size_ - 1];
  }

  const T& back() const {
    return data_[size_ - 1];
  }

  void reserve(const size_t& new_capacity){
    if(new_capacity <= capacity_)
      return;
    reallocate(new_capacity);
  }

  void shrink_to_fit(){
    if(size_ == 0)
      destroy_and_deallocate();
    else if(size_ < capacity_)
      reallocate(size_);
  }

  void clear(){
    for(size_t i = 0; i < size_; ++i)
      alloc_.destroy(data_ + i);
    size_ = 0; 
  }

private:
  void grow(){
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2; /* increasing capacity */
    reallocate(new_capacity);
  }

  void reallocate(size_t new_capacity){
    T* new_data = alloc_.allocate(new_capacity);

    /* construction loops must always be exception-safe */
    size_t temp = (size_ < new_capacity) ? size_ : new_capacity; 
    size_t constructed = 0;
    try {
      for(size_t i = 0; i < size_ && i < new_capacity; ++i){
        alloc_.construct(new_data + i, data_[i]); 
        ++constructed;
      }
    } catch(...) {
      for(size_t j = 0; j < constructed; ++j)
        alloc_.destroy(new_data + j);
      alloc_.deallocate(new_data);
      throw;
    }

    destroy_and_deallocate();
    data_ = new_data;
    size_ = temp;
    capacity_ = new_capacity;
  }

  void destroy_and_deallocate(){
    for(size_t i = 0; i < size_; ++i)
      alloc_.destroy(data_ + i);  /* destroying each element */
    alloc_.deallocate(data_);     /* releasing raw memory */

    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  T* data_;
  size_t size_;
  size_t capacity_;
  allocator<T> alloc_;
};

}
