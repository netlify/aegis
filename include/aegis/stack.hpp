#ifndef AEGIS_STACK_HPP
#define AEGIS_STACK_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>

// XXX: The push_front and push_back functions take value_type* instead of value_type const*
// The documentation given to us by OpenSSL is incorrect
#define AEGIS_STACK_INTERFACE(TYPE) \
  template <> struct stack_of<TYPE> : apex::type_identity<                                 \
    apex::remove_pointer_t<                                                                \
      apex::invoke_result_t<decltype(sk_##TYPE##_new_null)>                                \
    >                                                                                      \
  > { };                                                                                   \
  template <> struct stack_traits<TYPE> {                                                  \
    using value_type = TYPE;                                                               \
    using stack_type = stack_of_t<value_type>;                                             \
    using size_type = int;                                                                 \
                                                                                           \
    using const_pointer = apex::add_pointer_t<apex::add_const_t<stack_type>>;              \
    using pointer = apex::add_pointer_t<stack_type>;                                       \
                                                                                           \
    using comparison_function_type = auto(*)(value_type const*, value_type const*) -> int; \
    using copy_function_type = auto(*)(value_type*) -> value_type*;                        \
    using free_function_type = auto(*)(value_type*) -> void;                               \
                                                                                           \
    inline static constexpr free_function_type free_function = TYPE##_free;                \
    inline static constexpr copy_function_type copy_function = TYPE##_dup;                 \
                                                                                           \
    /* properties */                                                                       \
    [[nodiscard]] static value_type* get (const_pointer, size_type) noexcept;              \
    [[nodiscard]] static size_type size(const_pointer) noexcept;                           \
    [[nodiscard]] static bool sorted (const_pointer) noexcept;                             \
                                                                                           \
    /* mutators */                                                                         \
    [[nodiscard]] static size_type reserve (pointer, size_type) noexcept;                  \
                                                                                           \
    [[nodiscard]] static value_type* erase (pointer, value_type*) noexcept;                \
    [[nodiscard]] static value_type* erase (pointer, size_type) noexcept;                  \
                                                                                           \
    [[nodiscard]] static value_type* pop_front (pointer) noexcept;                         \
    [[nodiscard]] static value_type* pop_back (pointer) noexcept;                          \
                                                                                           \
    static void push_front (pointer, value_type*) noexcept;                                \
    static void push_back (pointer, value_type*) noexcept;                                 \
                                                                                           \
    static void clear (pointer) noexcept;                                                  \
    static void sort (pointer) noexcept;                                                   \
                                                                                           \
    /* construct/destruct */                                                               \
    [[nodiscard]] static pointer construct (size_type) noexcept;                           \
    [[nodiscard]] static pointer construct () noexcept;                                    \
    static void destruct (pointer) noexcept;                                               \
    void operator () (pointer ptr) noexcept { stack_traits::destruct(ptr); }               \
  };                                                                                       \
  template <> struct stack_traits<TYPE const> : stack_traits<TYPE> { };                    \
  extern template struct stack_traits<TYPE>

namespace aegis {
template <class> struct stack_traits;
template <class> struct stack_of;

template <class T> struct stack_of<T const> : stack_of<T> { };
template <class T> using stack_of_t = typename stack_of<T>::type;

template <class T>
concept specialized_stack_traits = requires {
  typename stack_traits<T>::stack_type;

  typename stack_traits<T>::const_pointer;
  typename stack_traits<T>::pointer;

  typename stack_traits<T>::value_type;
};

template <class T>
concept stackable = specialized_stack_traits<T>
and requires (
  typename stack_traits<T>::const_pointer cref,
  typename stack_traits<T>::pointer ref,
  typename stack_traits<T>::value_type* val,
  typename stack_traits<T>::size_type n
) {
  { stack_traits<T>::get(cref, n) } noexcept -> apex::same_as<decltype(val)>;
  { stack_traits<T>::size(cref) } noexcept -> apex::same_as<decltype(n)>;
  { stack_traits<T>::sorted(cref) } noexcept -> apex::boolean;

  { stack_traits<T>::reserve(ref, n) } noexcept -> apex::same_as<decltype(n)>;
  { stack_traits<T>::erase(ref, val) } noexcept -> apex::same_as<decltype(val)>;
  { stack_traits<T>::erase(ref, n) } noexcept -> apex::same_as<decltype(val)>;
  { stack_traits<T>::pop_front(ref) } noexcept -> apex::same_as<decltype(val)>;
  { stack_traits<T>::pop_back(ref) } noexcept -> apex::same_as<decltype(val)>;
  { stack_traits<T>::push_front(ref, val) } noexcept -> apex::same_as<void>;
  { stack_traits<T>::push_back(ref, val) } noexcept -> apex::same_as<void>;
  { stack_traits<T>::clear(ref) } noexcept -> apex::same_as<void>;
  { stack_traits<T>::sort(ref) } noexcept -> apex::same_as<void>;

  { stack_traits<T>::construct() } noexcept -> apex::same_as<decltype(ref)>;
  { stack_traits<T>::destruct(ref) } noexcept -> apex::same_as<void>;
};

AEGIS_STACK_INTERFACE(GENERAL_NAME);

// TODO: use apex::mixin::iterator<T> once stable
template <stackable T>
struct stack_iterator : protected view_handle<typename stack_traits<T>::stack_type> {
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = int;
  using value_type = T;
  using reference = apex::add_lvalue_reference_t<value_type>;
  using pointer = apex::add_pointer_t<value_type>;

  using traits_type = stack_traits<value_type>;

  stack_iterator (typename traits_type::pointer ptr, difference_type idx) noexcept :
    view_handle<typename traits_type::stack_type> { ptr },
    idx { idx }
  { }

  stack_iterator (stack_iterator const&) noexcept = default;
  stack_iterator () = delete;

  pointer operator -> () const noexcept {
    return traits_type::get(this->get(), this->idx);
  }

  reference operator * () const noexcept {
    return *traits_type::get(this->get(), this->idx);
  }

  stack_iterator operator ++ (int) noexcept {
    stack_iterator that { *this };
    this->idx++;
    return that;
  }

  stack_iterator operator -- (int) noexcept {
    stack_iterator that { *this };
    this->idx--;
    return that;
  }

  stack_iterator& operator ++ () noexcept {
    ++this->idx;
    return *this;
  }

  stack_iterator& operator -- () noexcept {
    --this->idx;
    return *this;
  }

  bool operator == (stack_iterator const& that) const noexcept {
    return this->get() == that.get() and this->idx == that.idx;
  }

  bool operator != (stack_iterator const& that) const noexcept {
    return not (*this == that);
  }

  bool operator >= (stack_iterator const& that) const noexcept {
    return not (*this < that);
  }

  bool operator <= (stack_iterator const& that) const noexcept {
    return not (*this > that);
  }

  bool operator > (stack_iterator const& that) const noexcept {
    return that < *this;
  }

  bool operator < (stack_iterator const& that) const noexcept {
    return this->get() == that.get() and this->idx < that.idx;
  }

private:
  difference_type idx { 0 };
};

// while this will be difficult to write for "all types", we can at least
// guarantee the iterators will "just work" for all types involved.
// We *will* be automatically generating a default_delete<T> for each
// stack_of_t<T>, as we use the apex::mixin::unique_handle type to
// do most of this work.
template <stackable T>
struct stack : private unique_handle<typename stack_traits<T>::stack_type, stack_traits<T>> {
  using traits_type = stack_traits<T>;
  using value_type = typename traits_type::value_type;
  using stack_type = typename traits_type::stack_type;
  using size_type = typename traits_type::size_type;

  using const_iterator = stack_iterator<apex::add_const_t<value_type>>;
  using iterator = stack_iterator<value_type>;

  using resource_type = unique_handle<stack_type, traits_type>;

  using resource_type::resource_type;
  using resource_type::get;

  stack (stack const&) = delete;
  stack () = delete;

  const_iterator begin () const noexcept { return { this->get(), 0 }; }
  const_iterator end () const noexcept { return { this->get(), this->size() }; }

  iterator begin () noexcept { return { this->get(), 0 }; }
  iterator end () noexcept { return { this->get(), this->size() }; }

  auto operator [] (size_type idx) { return traits_type::get(this->get(), idx); }

  [[nodiscard]] size_type reserve (size_type n) { return traits_type::reserve(this->get(), n); }
  [[nodiscard]] bool is_sorted () const noexcept;

  /* returns -1 if this->get() == nullptr */
  [[nodiscard]] size_type size () const noexcept { return traits_type::size(this->get()); }
  [[nodiscard]] bool empty () const noexcept { return this->size() <= 0; }
};

} /* namespace aegis */

#endif /* AEGIS_STACK_HPP */
