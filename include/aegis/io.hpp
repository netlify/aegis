#ifndef AEGIS_IO_HPP
#define AEGIS_IO_HPP

#include <aegis/memory.hpp>
#include <aegis/key.hpp>

#include <apex/core/span.hpp>
#include <openssl/ssl.h>

#include <string_view>
#include <string>

namespace aegis {

template <> struct default_delete<BIO> {
  void operator () (BIO*) const noexcept;
};

} /* namespace aegis */

namespace aegis::io {

struct stream : private unique_handle<BIO> {
  stream (apex::span<apex::byte>) noexcept;
  stream (std::string const&) noexcept;
  stream (std::string_view) noexcept;

  using unique_handle<BIO>::get;

private:
  stream (void const*, size_t) noexcept;
};

} /* namespace aegis::io */

#endif /* AEGIS_IO_HPP */
