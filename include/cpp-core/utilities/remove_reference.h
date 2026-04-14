// std::remove_reference<T>
// - isolate T from T&, T&&

#pragma once

namespace cpp_core{

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename T>
struct remove_reference<T&&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

}
