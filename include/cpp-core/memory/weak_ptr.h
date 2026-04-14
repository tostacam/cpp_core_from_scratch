// std::weak_ptr<T>

#pragma once

#include "shared_ptr.h"

namespace cpp_core{

template <typename T>
class weak_ptr{
public:
  weak_ptr() : ptr_(nullptr), ctrl_(nullptr) {}

  weak_ptr(const shared_ptr<T>& sp) {
    if(sp.ctrl_){
      ptr_ = sp.ptr_;
      ctrl_ = sp.ctrl_;
      ctrl_->weak_count++; 
    }
    else{
      ptr_ = nullptr;
      ctrl_ = nullptr;
    }
  }

  weak_ptr(const weak_ptr& other){
    if(other.ctrl_){
      ptr_ = other.ptr_;
      ctrl_ = other.ctrl_;
      ctrl_->weak_count++;
    }
    else {
      ptr_ = nullptr;
      ctrl_ = nullptr;
    }
  }

  weak_ptr& operator=(const weak_ptr& other) {
    if(this != &other){
      if(ctrl_ && --(ctrl_->weak_count) == 0 && ctrl_->shared_count == 0)
        delete ctrl_;

      if(other.ctrl_){
        ptr_ = other.ptr_;
        ctrl_ = other.ctrl_;
        ctrl_->weak_count++;
      }
      else{
        ptr_ = nullptr;
        ctrl_ = nullptr;
      }
    }
    return *this;
  }

  weak_ptr(weak_ptr&& other){
    ptr_ = other.ptr_;
    ctrl_ = other.ctrl_;
    other.ptr_ = nullptr;
    other.ctrl_ = nullptr; 
  }

  weak_ptr& operator=(weak_ptr&& other){
    if(this != &other){
      if(ctrl_ && --(ctrl_->weak_count) == 0 && ctrl_->shared_count == 0)
        delete ctrl_;
      
      ptr_ = other.ptr_;
      ctrl_ = other.ctrl_;
      other.ptr_ = nullptr;
      other.ctrl_ = nullptr;
    }
    return *this;
  }

  ~weak_ptr(){
    if(ctrl_ && --(ctrl_->weak_count) == 0 && ctrl_->shared_count == 0)
      delete ctrl_;
  }

  shared_ptr<T> lock() const {
    if(ctrl_ && ctrl_->shared_count > 0){
      return shared_ptr<T>(ptr_, ctrl_);
    }
    return shared_ptr<T>();
  }

  bool expired() const {
    return ctrl_ == nullptr || ctrl_->shared_count == 0;
  }
private:
  T* ptr_;
  control_block* ctrl_;
};

}
