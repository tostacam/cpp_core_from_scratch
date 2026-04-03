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
private:
  T* ptr;
};
