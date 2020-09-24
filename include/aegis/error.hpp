#ifndef AEGIS_ERROR_HPP
#define AEGIS_ERROR_HPP

#include <system_error>

namespace aegis::category {

::std::error_category const& async () noexcept;
::std::error_category const& asn1 () noexcept;

::std::error_category const& bignum () noexcept;

::std::error_category const& certificate_management_protocol () noexcept; // CMP_*
::std::error_category const& cryptographic_message_syntax () noexcept; // CMS_*
::std::error_category const& certificate_transparency () noexcept; // CT_*
::std::error_category const& configuration () noexcept;
::std::error_category const& compression () noexcept;
::std::error_category const& crypto () noexcept;

::std::error_category const& diffie_hellman () noexcept;
::std::error_category const& dsa () noexcept;

::std::error_category const& enhanced_security_service () noexcept; // ess
::std::error_category const& elliptic_curve () noexcept;
::std::error_category const& envelope () noexcept; // evp
::std::error_category const& engine () noexcept;

::std::error_category const& generic () noexcept;

::std::error_category const& http () noexcept;

::std::error_category const& io () noexcept;

::std::error_category const& key_derivation () noexcept; // kdf

::std::error_category const& object () noexcept; // asn1 objects
::std::error_category const& ocsp () noexcept;

::std::error_category const& pkcs12 () noexcept;
::std::error_category const& pkcs7 () noexcept;
::std::error_category const& pem () noexcept;

::std::error_category const& random () noexcept;
::std::error_category const& rsa () noexcept;

::std::error_category const& store () noexcept;
::std::error_category const& ssl () noexcept;

::std::error_category const& ts () noexcept; // asn1 ts

::std::error_category const& ui () noexcept;

::std::error_category const& x509v3 () noexcept;
::std::error_category const& x509 () noexcept;

} /* namespace aegis */

namespace aegis::error {

enum class async { };
enum class asn1 { };

enum class bignum { };

enum class io {
  accept = 100,
  addrinfo_address_is_not_af_inet = 141,
  ambiguous_host_or_service = 129,
  bad_fopen_mode = 101,
  broken_pipe = 124,
  connect_error = 103,
  connect_timeout = 147,
  gethostbyname_address_is_not_af_inet = 107,
  getsockname = 132,
  getsocketname_truncated_address = 133,
  getting_socktype = 134,
  invalid_argument = 125,
  invalid_socket = 135,
  in_use = 123,
  length_too_long = 102,
  listen_v6_only = 136,
  lookup_returned_nothing = 142,
  malformed_host_or_service = 130,
  nbio_connect_error = 110,
  no_accept_address_or_service_specified = 143,
  no_hostname_or_service_specified = 144,
  no_port_defined = 113,
  no_such_file = 128,
  null_parameter = 115,
  transfer_error = 104,
  transfer_timeout = 105,
  unable_to_bind_socket = 117,
  unable_to_create_socket = 118,
  unable_to_keepalive = 137,
  unable_to_listen_socket = 119,
  unable_to_nodelay = 138,
  unable_to_reuse_address = 139,
  unavailable_ip_family = 145,
  uninitialized = 120,
  unknown_info_type = 140,
  unsupported_ip_family = 146,
  unsupported_method = 121,
  unsupported_protocol_family = 131,
  write_to_read_only_bio = 126,
  wsastartup = 122,
};

enum class compression { };
enum class cmp { }; // TODO: is this compare?
enum class cms { };

} /* namespace aegis */

#endif /* AEGIS_ERROR_HPP */
