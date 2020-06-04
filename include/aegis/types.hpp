#ifndef AEGIS_TYPES_HPP
#define AEGIS_TYPES_HPP

// This header handles pulling in forward declarations

#if __has_include(<openssl/types.h>)
  #include <openssl/types.h>
#else
  #include <openssl/ossl_typ.h>
#endif /* __has_include(<openssl/types.h>) */

// This is where several important extension types are defined
// Sadly, they aren't all forward declared here, so we need to just take the
// small hit when including :(
#include <openssl/x509v3.h>

#endif /* AEGIS_TYPES_HPP */
