#include <aegis/stack.hpp>

// Add headers and implementations here as needed

#define AEGIS_STACK_IMPLEMENTATION(TYPE)                                        \
  TYPE* stack_traits<TYPE>::get (const_pointer ptr, size_type idx) noexcept {   \
    return sk_##TYPE##_value(ptr, idx);                                         \
  }                                                                             \
  int stack_traits<TYPE>::size (const_pointer ptr) noexcept {                   \
    return sk_##TYPE##_num(ptr);                                                \
  }                                                                             \
  int stack_traits<TYPE>::reserve(pointer ptr, size_type n) noexcept {          \
    return sk_##TYPE##_reserve(ptr, n);                                         \
  }                                                                             \
  TYPE* stack_traits<TYPE>::erase(pointer ptr, value_type* val) noexcept {      \
    return sk_##TYPE##_delete_ptr(ptr, val);                                    \
  }                                                                             \
  TYPE* stack_traits<TYPE>::erase(pointer ptr, size_type idx) noexcept {        \
    return sk_##TYPE##_delete(ptr, idx);                                        \
  }                                                                             \
  TYPE* stack_traits<TYPE>::pop_front (pointer ptr) noexcept {                  \
    return sk_##TYPE##_shift(ptr);                                              \
  }                                                                             \
  TYPE* stack_traits<TYPE>::pop_back (pointer ptr) noexcept {                   \
    return sk_##TYPE##_pop(ptr);                                                \
  }                                                                             \
  void stack_traits<TYPE>::push_front (pointer ptr, value_type* val) noexcept { \
    std::ignore = sk_##TYPE##_unshift(ptr, val);                                \
  }                                                                             \
  void stack_traits<TYPE>::push_back (pointer ptr, value_type* val) noexcept {  \
    std::ignore = sk_##TYPE##_push(ptr, val);                                   \
  }                                                                             \
  void stack_traits<TYPE>::clear (pointer ptr) noexcept {                       \
    sk_##TYPE##_zero(ptr);                                                      \
  }                                                                             \
  auto stack_traits<TYPE>::construct (size_type n) noexcept -> pointer {        \
    return sk_##TYPE##_new_reserve(nullptr, n);                                 \
  }                                                                             \
  auto stack_traits<TYPE>::construct () noexcept -> pointer {                   \
    return sk_##TYPE##_new_null();                                              \
  }                                                                             \
  void stack_traits<TYPE>::destruct (pointer ptr) noexcept {                    \
    sk_##TYPE##_pop_free(ptr, stack_traits<TYPE>::free_function);               \
  }                                                                             \
  template struct stack_traits<TYPE>
namespace aegis {

AEGIS_STACK_IMPLEMENTATION(GENERAL_NAME);

} /* namespace aegis */

