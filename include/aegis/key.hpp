#ifndef AEGIS_KEY_HPP
#define AEGIS_KEY_HPP

#include <aegis/memory.hpp>
#include <aegis/types.hpp>

namespace aegis::io { struct stream_view; } /* namespace aegis::io */

namespace aegis {

struct private_key : view_handle<EVP_PKEY> {
  private_key (io::stream_view const&) noexcept;
  using view_handle<EVP_PKEY>::view_handle;
  using view_handle<EVP_PKEY>::get;
};

} /* namespace aegis */

#endif /* AEGIS_KEY_HPP */
