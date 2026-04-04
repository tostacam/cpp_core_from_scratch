// std::unique_ptr<T>
// - holds a raw pointer
// - deletes it on destruction
// - cannot be copied
// - can be moved (transfers ownership)
// - guarantees single ownership (prevents double delete, UB)

#include <utility> /* for move */

template <typename T>
class unique_ptr{
public:
  unique_ptr() : ptr_(nullptr) {}
  
  explicit unique_ptr(T* ptr) : ptr_(ptr) {}

  unique_ptr(const unique_ptr&) = delete;

  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr (unique_ptr&& other){
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& other){
    if(this != &other){ /* would delete in case of self-move */
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~unique_ptr(){
    delete ptr_; /* allocation: new T(...) */
  }

  T* get(){
    return ptr_;
  }

  T& operator*(){
    return *ptr_;
  }
  
  T* operator->(){
    return ptr_;
  }

  /* const applies to handle not resource */
  T* get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  T* release(){
    T* temp = ptr_;
    ptr_ = nullptr;
    return temp;
  }

  void reset(T* ptr){
    if(ptr_ != ptr){
      delete ptr_;
      ptr_ = ptr;
    }
  }

private:
  T* ptr_;
};
