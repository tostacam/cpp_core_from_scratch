// std::reverse_iterator<T>

#pragma once

#include "iterator_traits.h"

template <typename It>
class reverse_iterator {
public:
  using difference_type   = typename iterator_traits<It>::difference_type;
  using value_type        = typename iterator_traits<It>::value_type;
  using pointer           = typename iterator_traits<It>::pointer;
  using reference         = typename iterator_traits<It>::reference;
  using iterator_category = bidirectional_iterator_tag; /* no -, +, [] implementation yet */

  reverse_iterator() = default;
  
  explicit reverse_iterator(It it) : current(it) {}

  reverse_iterator& operator++(){
    --current;
    return *this;
  }

  reverse_iterator operator++(int){
    reverse_iterator tmp = *this;
    --current;
    return tmp;
  }

  It base() const {
    return current;
  }

  reverse_iterator& operator--(){
    ++current;
    return *this;
  }

  reverse_iterator operator--(int){
    reverse_iterator temp = *this;
    ++current;
    return temp;
  }

  reference operator*() const {
    It temp = current;
    return *--temp;
  }

  pointer operator->() const {
    It temp = current;
    return &(*--temp);
  }

  bool operator==(const reverse_iterator& other) const {
    return current == other.current;
  }

  bool operator!=(const reverse_iterator& other) const {
    return current != other.current;
  }

private:
  It current; 
};
