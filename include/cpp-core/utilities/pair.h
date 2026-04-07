// std::pair<T1, T2>

#pragma once
#include "forward.h"

template <typename T1, typename T2>
struct pair{
  T1 first;
  T2 second;

  pair() = default;

  pair(const T1& a, const T2& b) : first(a), second(b) {}

  /* perfect forwarding */
  template <typename U1, typename U2>
  pair(U1&& a, U2&& b) : first(::forward<U1&&>(a)), second(::forward<U2&&>(b)) {}
};
