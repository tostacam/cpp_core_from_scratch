// std::weak_ptr<T>
// - does NOT own the object (non-owning reference)
// - observes an object managed by shared_ptr
// - does NOT affect object ligetime (does not increment ref count)
// - can become expired when the object is deleted
// - must be converted to shared_ptr (with lock()) to access the object safely
// - prevent cyclic ownership (breaks shared_ptr reference cycles)
// - uses the same control block as shared_ptr (separate weak count)

#pragma once
#include "shared_ptr.h"

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

  ~weak_ptr(){
    if(ctrl_ && --(ctrl_->weak_count) == 0 && ctrl_->shared_count == 0)
      delete ctrl_;
  }
private:
  T* ptr_;
  control_block* ctrl_;
};
