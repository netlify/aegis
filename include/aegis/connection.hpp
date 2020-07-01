#ifndef AEGIS_CONNECTION_HPP
#define AEGIS_CONNECTION_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>

namespace aegis {

template <> struct retain_traits<SSL> {
  static void increment (SSL*) noexcept;
  static void decrement (SSL*) noexcept;
};

struct context;

struct connection : retain_handle<SSL> {
  connection (context const&) noexcept;

  using retain_handle<SSL>::retain_handle;
  using retain_handle<SSL>::operator bool;
  using retain_handle<SSL>::get;

  std::string host() const;
};

} /* namespace aegis */

#endif /* AEGIS_CONNECTION_HPP */
