#include <aegis/context.hpp>
#include <aegis/x509.hpp>
#include <aegis/key.hpp>

#include <apex/core/prelude.hpp>

#include <openssl/ssl.h>
#include <openssl/err.h>

namespace aegis {

void retain_traits<SSL_CTX>::increment (SSL_CTX* ptr) noexcept { SSL_CTX_up_ref(ptr); }
void retain_traits<SSL_CTX>::decrement (SSL_CTX* ptr) noexcept { SSL_CTX_free(ptr); }

unsigned long context::add_extra_chain (x509::certificate&& cert) noexcept {
  if (SSL_CTX_add_extra_chain_cert(this->get(), cert.release()) < 1) {
    return ERR_get_error();
  }
  return 0;
}

unsigned long context::use (x509::certificate const& cert) noexcept {
  if (SSL_CTX_use_certificate(this->get(), cert.get()) < 1) {
    return ERR_get_error();
  }
  return 0;
}

unsigned long context::use (private_key const& key) noexcept {
  if (SSL_CTX_use_PrivateKey(this->get(), key.get()) < 1) {
    return ERR_get_error();
  }
  return 0;
}

std::chrono::seconds context::timeout () const noexcept {
  return std::chrono::seconds { SSL_CTX_get_timeout(this->get()) };
}

void context::timeout (std::chrono::seconds duration) noexcept {
  apex::ignore = SSL_CTX_set_timeout(this->get(), duration.count());
}

} /* namespace aegis */
