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

enum class async {
  failed_to_set_pool = 101,
  failed_to_swap_context = 102,
  init_failed = 105,
  invalid_pool_size = 103,
};

enum class asn1 {
  adding_object = 171,
  asn1_parse_error = 203,
  asn1_sig_parse_error = 204,
  aux_error = 100,
  bad_object_header = 102,
  bmpstring_is_wrong_length = 214,
  bn_lib = 105,
  boolean_is_wrong_length = 106,
  buffer_too_small = 107,
  cipher_has_no_object_identifier = 108,
  context_not_initialised = 217,
  data_is_wrong = 109,
  decode_error = 110,
  depth_exceeded = 174,
  digest_and_key_type_not_supported = 198,
  encode_error = 112,
  error_getting_time = 173,
  error_loading_section = 172,
  error_setting_cipher_params = 114,
  expecting_an_integer = 115,
  expecting_an_object = 116,
  explicit_length_mismatch = 119,
  explicit_tag_not_constructed = 120,
  field_missing = 121,
  first_num_too_large = 122,
  header_too_long = 123,
  illegal_bitstring_format = 175,
  illegal_boolean = 176,
  illegal_characters = 124,
  illegal_format = 177,
  illegal_hex = 178,
  illegal_implicit_tag = 179,
  illegal_integer = 180,
  illegal_negative_value = 226,
  illegal_nested_tagging = 181,
  illegal_null = 125,
  illegal_null_value = 182,
  illegal_object = 183,
  illegal_optional_any = 126,
  illegal_options_on_item_template = 170,
  illegal_padding = 221,
  illegal_tagged_any = 127,
  illegal_time_value = 184,
  illegal_zero_content = 222,
  integer_not_ascii_format = 185,
  integer_too_large_for_long = 128,
  invalid_bit_string_bits_left = 220,
  invalid_bmpstring_length = 129,
  invalid_digit = 130,
  invalid_mime_type = 205,
  invalid_modifier = 186,
  invalid_number = 187,
  invalid_object_encoding = 216,
  invalid_scrypt_parameters = 227,
  invalid_separator = 131,
  invalid_string_table_value = 218,
  invalid_universalstring_length = 133,
  invalid_utf8string = 134,
  invalid_value = 219,
  list_error = 188,
  mime_no_content_type = 206,
  mime_parse_error = 207,
  mime_sig_parse_error = 208,
  missing_eoc = 137,
  missing_second_number = 138,
  missing_value = 189,
  mstring_not_universal = 139,
  mstring_wrong_tag = 140,
  nested_asn1_string = 197,
  nested_too_deep = 201,
  non_hex_characters = 141,
  not_ascii_format = 190,
  not_enough_data = 142,
  no_content_type = 209,
  no_matching_choice_type = 143,
  no_multipart_body_failure = 210,
  no_multipart_boundary = 211,
  no_sig_content_type = 212,
  null_is_wrong_length = 144,
  object_not_ascii_format = 191,
  odd_number_of_chars = 145,
  second_number_too_large = 147,
  sequence_length_mismatch = 148,
  sequence_not_constructed = 149,
  sequence_or_set_needs_config = 192,
  short_line = 150,
  sig_invalid_mime_type = 213,
  streaming_not_supported = 202,
  string_too_long = 151,
  string_too_short = 152,
  the_asn1_object_identifier_is_not_known_for_this_md = 154,
  time_not_ascii_format = 193,
  too_large = 223,
  too_long = 155,
  too_small = 224,
  type_not_constructed = 156,
  type_not_primitive = 195,
  unexpected_eoc = 159,
  universalstring_is_wrong_length = 215,
  unknown_format = 160,
  unknown_message_digest_algorithm = 161,
  unknown_object_type = 162,
  unknown_public_key_type = 163,
  unknown_signature_algorithm = 199,
  unknown_tag = 194,
  unsupported_any_defined_by_type = 164,
  unsupported_cipher = 228,
  unsupported_public_key_type = 167,
  unsupported_type = 196,
  wrong_integer_type = 225,
  wrong_public_key_type = 200,
  wrong_tag = 168,
};

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
