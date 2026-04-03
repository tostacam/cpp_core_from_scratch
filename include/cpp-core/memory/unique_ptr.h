// std::unique_ptr<T>
// - holds a raw pointer
// - deletes it on destruction
// - cannot be copied
// - can be moved (transfers ownership)
// - guarantees single ownership

template <typename T>
class unique_ptr{
public:
  unique_ptr() : ptr(nullptr) {}
  
  explicit unique_ptr(T* ptr) : ptr(ptr) {}

  unique_ptr(const unique_ptr&) = delete;

  unique_ptr& operator=(const unique_ptr&) = delete;

  ~unique_ptr(){
    delete ptr; /* allocation: new T(...) */
  } 

private:
  T* ptr;
};
