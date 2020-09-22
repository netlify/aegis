#ifndef AEGIS_CONTEXT_HPP
#define AEGIS_CONTEXT_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>

namespace aegis::x509 { struct certificate; } /* namespace aegis::x509 */

namespace aegis {

struct private_key;

template <> struct retain_traits<SSL_CTX> {
  static void increment (SSL_CTX*) noexcept;
  static void decrement (SSL_CTX*) noexcept;
};

struct context : private retain_handle<SSL_CTX> {
  // TODO: consider renaming add_extra_chain to just chain
  // TODO: change to std::error_code instead of unsigned long
  unsigned long add_extra_chain (x509::certificate&&) noexcept;
  unsigned long use (x509::certificate const&) noexcept;
  unsigned long use (private_key const&) noexcept;

  using resource_type::resource_type;
  using resource_type::operator bool;
  using resource_type::get;
};

} /* namespace aegis */

#endif /* AEGIS_CONTEXT_HPP */
