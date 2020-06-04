#ifndef AEGIS_STRING_HPP
#define AEGIS_STRING_HPP

#include <aegis/memory.hpp>

#include <apex/core/span.hpp>

#include <openssl/asn1.h>

#include <string_view>
#include <string>


// TODO: Move to aegis::asn1::string
// TODO: Add an aegis::asn1::string_view for non-owning returns

namespace aegis {

template <> struct default_delete<ASN1_STRING> {
  void operator () (ASN1_STRING*) const noexcept;
};

struct string : private unique_handle<ASN1_STRING> {
  using size_type = int;

  using handle_type::handle_type;

// TODO: needs a 'type' setting
//  explicit string (apex::span<byte const>) noexcept;
//  explicit string (std::string_view) noexcept;

  explicit operator apex::span<apex::byte const> () const noexcept;
  explicit operator std::string () const noexcept;

  [[nodiscard]] bool empty () const noexcept;
  size_type length () const noexcept;
  size_type size () const noexcept;
};

} /* namespace aegis */

#endif /* AEGIS_STRING_HPP */
