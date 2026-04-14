// std::iterator_traits
// - https://saco-evaluator.org.za/docs/cppreference/en/cpp/iterator/iterator_traits.html

#pragma once

#include <cstddef>
#include "iterator_tags.h"

namespace cpp_core{

template <typename It>
struct iterator_traits {
  using difference_type   = typename It::difference_type;
  using value_type        = typename It::value_type;
  using pointer           = typename It::pointer;
  using reference         = typename It::reference;
  using iterator_category = typename It::iterator_category;
};

template <typename T>
struct iterator_traits<T*> {
  using difference_type   = ptrdiff_t;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using iterator_category = random_access_iterator_tag;
};

template <typename T>
struct iterator_traits<const T*> {
  using difference_type   = ptrdiff_t;
  using value_type        = T;
  using pointer           = const T*;
  using reference         = const T&;
  using iterator_category = random_access_iterator_tag;
};

}
