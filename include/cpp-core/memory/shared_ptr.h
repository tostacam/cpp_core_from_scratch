// std::shared_ptr<T>
// - holds a raw pointer
// - uses a control block (ref count + deleter)
// - deletes the object when ref count reaches zero
// - can be copied (ref count increases), can be moved (transfers ownership)
// - allows shared ownership (multiple owners)
// - prevents double delete via reference counting

#pragma once
#include <cstddef>  /* for size_t */

#include <iostream>
class control_block{
public:
  size_t ref_count;
};

template <typename T>
class shared_ptr{
public:
  shared_ptr() : ptr_(nullptr), ctrl_(nullptr) {}

  explicit shared_ptr(T* ptr) : ptr_(ptr) {
    if(ptr_)
      ctrl_ = new control_block{1};
    else
      ctrl_ = nullptr;
  }

  shared_ptr(const shared_ptr& other){
    std::cout << "from copy ctr\n";
    ptr_ = other.ptr_;
    ctrl_ = other.ctrl_;
    if(ctrl_)
      ctrl_->ref_count++;
  }

  shared_ptr& operator=(const shared_ptr& other){
    if(this != &other){ /* in case of self copy */
      /* remove current pointer */
      if(ctrl_ && --(ctrl_->ref_count) == 0){
        delete ptr_;
        delete ctrl_;
      }

      ptr_ = other.ptr_;
      ctrl_ = other.ctrl_;
      if(ctrl_)
        ctrl_->ref_count++;
    }
    return *this;
  }

  shared_ptr(shared_ptr&& other){
    std::cout << "from move ctr\n";
    ptr_ = other.ptr_;
    ctrl_ = other.ctrl_;
    other.ptr_ = nullptr;
    other.ctrl_ = nullptr;
  }

  shared_ptr& operator=(shared_ptr&& other){
    if(this != &other){ /* in case of self move */
      /* release current */
      if(ctrl_ && --(ctrl_->ref_count) == 0){
        delete ptr_;
        delete ctrl_;
      }

      ptr_ = other.ptr_;
      ctrl_ = other.ctrl_;
      other.ptr_ = nullptr;
      other.ctrl_ = nullptr;
    }
    return *this;
  }

  ~shared_ptr(){
    if(ctrl_ && --(ctrl_->ref_count) == 0){
      delete ptr_;
      delete ctrl_;
    }
  }
private:
  T* ptr_;
  control_block* ctrl_;
};
