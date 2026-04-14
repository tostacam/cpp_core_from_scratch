// std::list()

#include <cstddef>  /* for size_t */

template <typename T>
struct list_node{
  T value;
  list_node* prev;
  list_node* next;
};

template <typename T>
class list{
public:
  list() : size_(0) {
    sentinel_ = new list_node<T>;
    sentinel_->prev = sentinel_;
    sentinel_->next = sentinel_;
  }

  ~list(){
    delete sentinel_;
  }

private:
  list_node<T>* sentinel_;
  size_t size_;
};
