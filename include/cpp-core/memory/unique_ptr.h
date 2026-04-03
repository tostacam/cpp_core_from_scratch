// std::unique_ptr<T>
// - holds a raw pointer
// - deletes it on destruction
// - cannot be copied
// - can be moved (transfers ownership)
// - guarantees single ownership

#include <utility> /* for move */

template <typename T>
class unique_ptr{
public:
  unique_ptr() : ptr(nullptr) {}
  
  explicit unique_ptr(T* ptr) : ptr(ptr) {}

  unique_ptr(const unique_ptr&) = delete;

  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr (unique_ptr&& other){
    ptr = other.ptr;
    other.ptr = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& other){
    if(this != other){
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  ~unique_ptr(){
    delete ptr; /* allocation: new T(...) */
  } 

private:
  T* ptr;
};
