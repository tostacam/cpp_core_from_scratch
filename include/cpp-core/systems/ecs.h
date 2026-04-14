#pragma once
#include <cstddef>  /* for size_t */
#include "../containers/vector.h"

namespace cpp_core{

using entity = std::size_t;

template <typename T>
struct component_storage {
  static cpp_core::vector<T> data;
};

template <typename T>
cpp_core::vector<T> component_storage<T>::data;

struct world {
  entity next_entity = 0;

  entity create() {
    return next_entity++;
  }

  template <typename Component>
  void add(entity e, const Component& c) {
    auto& data = component_storage<Component>::data;

    if (e >= data.size())
      data.resize(e + 1);

    data[e] = c;
  }

  template <typename Component>
  Component& get(entity e) {
    return component_storage<Component>::data[e];
  }
};

}
