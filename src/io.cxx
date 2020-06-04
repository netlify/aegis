#include <aegis/io.hpp>

namespace aegis {

void default_delete<BIO>::operator () (BIO* ptr) const noexcept { BIO_free(ptr); }

} /* namespace aegis */

namespace aegis::io {

stream::stream (apex::span<apex::byte> s) noexcept :
  stream { s.data(), s.size() }
{ }

stream::stream (std::string const& s) noexcept :
  stream { s.data(), s.size() }
{ }

stream::stream (std::string_view s) noexcept :
  stream { s.data(), s.size() }
{ }

stream::stream (void const* ptr, size_t length) noexcept :
  unique_handle<BIO> { BIO_new_mem_buf(ptr, length) }
{ }

} /* namespace aegis::io */
