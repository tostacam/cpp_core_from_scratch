#pragma once
#include "../containers/vector.h"
#include "../utilities/function.h"

namespace cpp_core{

template <typename Event>
struct event_storage{
  static cpp_core::vector<cpp_core::function<void(const Event&)>> listeners;
};

template <typename Event>
cpp_core::vector<cpp_core::function<void(const Event&)>> event_storage<Event>::listeners;

class event_bus {
public:
  template <typename Event>
  void subscribe(cpp_core::function<void(const Event&)> f){
    event_storage<Event>::listeners.push_back(f); 
  }

  template <typename Event>
  void emit(const Event& e){
    auto& listeners = event_storage<Event>::listeners;

    for(auto it = listeners.begin(); it != listeners.end(); ++it)
      (*it)(e);
  }
};

}
