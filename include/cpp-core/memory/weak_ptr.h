// std::weak_ptr<T>
// - does NOT own the object (non-owning reference)
// - observes an object managed by shared_ptr
// - does NOT affect object ligetime (does not increment ref count)
// - can become expired when the object is deleted
// - must be converted to shared_ptr (with lock()) to access the object safely
// - prevent cyclic ownership (breaks shared_ptr reference cycles)
// - uses the same control block as shared_ptr (separate weak count)

#pragma once
#include "shared_ptr.h"

template <typename T>
class weak_ptr{
private:
  T* ptr_;
  control_block* ctrl_;
};
