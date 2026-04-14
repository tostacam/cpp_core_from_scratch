// std::list()

template <typename T>
struct list_node{
  T value;
  list_node* prev;
  list_node* next;
};

template <typename T>
class list{
public:
  list();

  ~list();

private:
  list_node<T> *sentinel_;
  size_t size;
};
