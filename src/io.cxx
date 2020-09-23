#include <aegis/io.hpp>

namespace aegis {

void retain_traits<BIO>::increment (BIO* ptr) noexcept { BIO_up_ref(ptr); }
void retain_traits<BIO>::decrement (BIO* ptr) noexcept { BIO_free(ptr); }

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

stream_view::stream_view (apex::span<apex::byte> const& s) noexcept :
  stream_view { s.data(), s.size() }
{ }

stream_view::stream_view (std::string_view const& s) noexcept :
  stream_view { s.data(), s.size() }
{ }

stream_view::stream_view (std::string const& s) noexcept :
  stream_view { s.data(), s.size() }
{ }

stream_view::stream_view (void const* ptr, size_t length) noexcept :
  retain_handle<BIO> { BIO_new_mem_buf(ptr, length) }
{ }

} /* namespace aegis::io */
