// std::reverse_iterator<T>

template <typename It>
class reverse_iterator {
public:
  reverse_iterator() = default;
  
  reverse_iterator(It it) : current(it) {}

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

  auto operator*() const {
    It temp = current;
    return *--temp;
  }

  auto operator->() const {
    It temp = current;
    return &(*--temp);
  }

private:
  It current; 
};
