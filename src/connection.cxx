#include <aegis/connection.hpp>
#include <aegis/context.hpp>

namespace aegis {

void retain_traits<SSL>::increment (SSL* ptr) noexcept { SSL_up_ref(ptr); }
void retain_traits<SSL>::decrement (SSL* ptr) noexcept { SSL_free(ptr); }

connection::connection (context const& c) noexcept :
  retain_handle<SSL> { SSL_new(c.get()) }
{ }

} /* namespace aegis */
