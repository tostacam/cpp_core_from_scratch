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

  void insert_node(list_node<T>* pos, list_node<T>* node){
    node->next = pos;
    node->prev = pos->prev;

    pos->prev->next = node;
    pos->prev = node;
  }

  void erase_node(list_node<T>* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
  }

  void push_back(const T& value){
    list_node<T>* node = new list_node<T>;
    node->value = value;
    insert_node(sentinel_, node);
    ++size_;
  }

  void push_front(const T& value){
    list_node<T>* node = new list_node<T>;
    node->value = value;
    insert_node(sentinel_->next, node);
    ++size_;
  }

private:
  list_node<T>* sentinel_;
  size_t size_;
};
