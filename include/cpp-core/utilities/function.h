// std::function()

#pragma once
#include "forward.h"

namespace cpp_core{

template <typename>
class function {};

template <typename R, typename... Args>
class function<R(Args...)> {
  struct callable_base{
    virtual R call(Args... args) = 0;
    virtual ~callable_base() = default;
  };

  template <typename F>
  struct callable : callable_base {
    F f;

    callable(F&& func) : f(cpp_core::forward<F>(func)) {}

    R call(Args... args) override{
      return f(args...);
    }
  };

  callable_base* ptr_ = nullptr;

public:

  template <typename F>
  function(F&& f){
    ptr_ = new callable<F>(cpp_core::forward<F>(f));
  }

  R operator()(Args... args){
    return ptr_->call(args...);
  }

  ~function(){
    delete ptr_;
  }
};

}
