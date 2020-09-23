#ifndef AEGIS_IO_HPP
#define AEGIS_IO_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>
#include <aegis/key.hpp>

#include <apex/core/string.hpp>
#include <apex/core/span.hpp>

namespace aegis {

template <> struct retain_traits<BIO> {
  using reset_action = apex::adopt_t;
  static void increment (BIO*) noexcept;
  static void decrement (BIO*) noexcept;
};

template <> struct default_delete<BIO> {
  void operator () (BIO*) const noexcept;
};

} /* namespace aegis */

namespace aegis::io {

struct [[deprecated("use aegis::io::stream_view")]] stream : private unique_handle<BIO> {
  stream (apex::span<apex::byte>) noexcept;
  stream (std::string const&) noexcept;
  stream (std::string_view) noexcept;

  using unique_handle<BIO>::get;

private:
  stream (void const*, size_t) noexcept;
};

struct stream_view : private retain_handle<BIO> {
  stream_view (apex::span<apex::byte> const&) noexcept;
  stream_view (std::string_view const&) noexcept;
  stream_view (std::string const&) noexcept;

  stream_view (apex::span<apex::byte>&&) = delete;
  stream_view (std::string_view&&) = delete;
  stream_view (std::string&&) = delete;

  using resource_type::get;
private:
  stream_view (void const*, size_t) noexcept;
};

} /* namespace aegis::io */

#endif /* AEGIS_IO_HPP */
