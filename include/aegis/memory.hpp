#ifndef AEGIS_MEMORY_HPP
#define AEGIS_MEMORY_HPP

#include <apex/memory/retain.hpp>
#include <apex/memory/view.hpp>

#include <apex/mixin/handle.hpp>
#include <apex/mixin/resource.hpp>

namespace aegis {

template <class> struct default_delete;

template <apex::complete_type T>
struct default_delete<T> {
  void operator () (T* ptr) const noexcept { delete ptr; }
};

template <apex::incomplete_type T>
struct default_delete<T> {
  void operator () (T*) const noexcept = delete;
};

// This requires users to specialize the traits type
template <class T>
struct retain_traits {
  static void increment (T*) noexcept = delete;
  static void decrement (T*) noexcept = delete;
};

template <class T, class D=default_delete<T>>
using unique_ptr = std::unique_ptr<T, D>;

template <class T, class D=default_delete<T>>
using unique_handle = apex::mixin::resource<T, unique_ptr<T, D>>;

template <class T, class R=retain_traits<T>>
using retain_handle = apex::mixin::resource<T, apex::retain_ptr<T, R>>;

template <class T>
using view_handle = apex::mixin::resource<
  apex::remove_pointer_t<T>,
  apex::view_ptr<apex::remove_pointer_t<T>>
>;

} /* namespace aegis */


#endif /* AEGIS_MEMORY_HPP */
