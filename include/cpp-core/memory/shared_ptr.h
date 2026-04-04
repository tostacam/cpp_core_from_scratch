// std::shared_ptr<T>
// - holds a raw pointer
// - uses a control block (ref count + deleter)
// - deletes the object when ref count reaches zero
// - can be copied (ref count increases), can be moved (transfers ownership)
// - allows shared ownership (multiple owners)
// - prevents double delete via reference counting

#include <cstddef>  /* for size_t */

class control_block{
public:
  size_t ref_count;
};

template <typename T>
class shared_ptr{
private:
  T* ptr_;
  control_block* ctrl_;
};
