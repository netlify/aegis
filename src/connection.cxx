#include <aegis/connection.hpp>
#include <aegis/context.hpp>

#include <openssl/ssl.h>

namespace aegis {

void retain_traits<SSL>::increment (SSL* ptr) noexcept { SSL_up_ref(ptr); }
void retain_traits<SSL>::decrement (SSL* ptr) noexcept { SSL_free(ptr); }

connection::connection (context const& c) noexcept :
  retain_handle<SSL> { SSL_new(c.get()) }
{ }

std::string connection::host () const {
  auto ptr = SSL_get_servername(this->get(), TLSEXT_NAMETYPE_host_name);
  if (not ptr) { return std::string { }; }
  return ptr;
}

} /* namespace aegis */
