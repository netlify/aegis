#include <aegis/key.hpp>
#include <aegis/io.hpp>

namespace aegis {

private_key::private_key (io::stream const& stream) noexcept :
  view_handle<EVP_PKEY> { PEM_read_bio_PrivateKey(stream.get(), nullptr, nullptr, nullptr) }
{ }

} /* namespace aegis */
