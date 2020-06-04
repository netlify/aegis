#ifndef AEGIS_STACK_HPP
#define AEGIS_STACK_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>

// XXX: This entire setup is EXTREMELY volatile (not the keyword, :P)
// Effectively, OpenSSL uses macros to generate names. However, we can't
// *reflect* on a type name with the preprocessor (that's just basic
// rules of the translation phases). So we have to 'get' the name of
// various types. To do this, we use AEGIS_DECLARE_STACK_TYPE_OF(TYPE)
// to create a specialization for stack_of<T>. We can then use this to set
// the correct type information, as we now have both T and stack_of<T>.
// However, because of how these macros are used, we need to permit them to 
// exist beyond *just* this header (or else we'll be including EVERY header
// in the openssl...)
//
// On the bright side, once we have this type information, declaring the
// 'interface' for a given type T becomes as simple as using the type
// info to recreate the interface defined within openssl/safestack.h
// We then declare all of these functions within aegis::impl::stack::,
// and then rely on overloads to make sure functions are declared correctly.
// We also add `void (const)*` overloads that are deleted to help prevent
// mistakes. We'll then use a separate macro within src/stack.cxx to generate
// the actual implementation of all these functions. Then "adding" a new type
// becomes as simple as adding two lines. One to the file where we declare the
// stack type, and src/stack.cxx
//
// An alternative approach to getting the stack type might be to just use the
// AEGIS_DECLARE_STACK_INTERFACE(TYPE) and then extract the first parameter.
// Personally, I think that's safer, but it requires more template
// metaprogramming.

// XXX: The push_front and push_back functions take value_type* instead of value_type const*
// The documentation given to us by OpenSSL is incorrect
#define AEGIS_STACK_INTERFACE(TYPE) \
  template <> struct stack_of<TYPE> : apex::type_identity<                                 \
    std::remove_pointer_t<                                                                 \
      std::invoke_result_t<decltype(sk_##TYPE##_new_null)>                                 \
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
                                                                                           \
    /* construct/destruct */                                                               \
    [[nodiscard]] static pointer construct (size_type) noexcept;                           \
    [[nodiscard]] static pointer construct () noexcept;                                    \
    static void destruct (pointer) noexcept;                                               \
    void operator () (pointer ptr) noexcept { stack_traits::destruct(ptr); }               \
  };                                                                                       \
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
};

// This concept is used to make sure that the entire 'raw' interface is
// allowed to be called, as stack<T> depends on this.
// As a result, this should probably be changed to use typename stack_traits<T>::stack_type;
// and friends.
// This concept WILL grow over time and possibly break code :)
template <class T>
concept stackable = specialized_stack_traits<T>
and requires (typename stack_traits<T>::pointer ref, typename stack_traits<T>::const_pointer cref) {
  { stack_traits<T>::construct() } noexcept -> apex::same_as<typename stack_traits<T>::pointer>;
  { stack_traits<T>::destruct(ref) } noexcept -> apex::same_as<void>;
  { stack_traits<T>::size(cref) } noexcept -> apex::same_as<int>;
};


AEGIS_STACK_INTERFACE(GENERAL_NAME);

template <stackable T>
struct stack_iterator;

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
  using handle_type = unique_handle<stack_type, traits_type>;

  using handle_type::handle_type;
  using handle_type::get;
  //using const_iterator stack_iterator<apex::add_const_t<value_type>>;
  //using iterator = stack_iterator<value_type>;

  //stack (stack const&) noexcept;
  //stack () noexcept;

  // const_iterator begin () const noexcept;
  // const_iterator end () const noexcept;
  // iterator begin () noexcept;
  // iterator end () noexcept;
  auto operator [] (size_type idx) { return traits_type::get(this->get(), idx); }

  [[nodiscard]] size_type reserve (size_type n) { return traits_type::reserve(this->get(), n); }
  [[nodiscard]] bool sorted () const noexcept;

  [[nodiscard]] size_type size () const noexcept { return traits_type::size(this->get()); }
  [[nodiscard]] bool empty () const noexcept { return this->get() and this->size(); }
};

} /* namespace aegis */

#endif /* AEGIS_STACK_HPP */
