#include <aegis/string.hpp>

#include <apex/core/scope.hpp>

namespace aegis {

void default_delete<ASN1_STRING>::operator () (ASN1_STRING* ptr) const noexcept {
  ASN1_STRING_free(ptr);
}

string::operator apex::span<apex::byte const> () const noexcept {
  return apex::span<apex::byte const> {
    reinterpret_cast<apex::byte const*>(ASN1_STRING_get0_data(this->get())),
    static_cast<std::size_t>(this->size())
  };
}

string::operator std::string () const noexcept {
  unsigned char* text;
  apex::scope_exit deallocate { [&] { OPENSSL_free(text); } };
  auto length = ASN1_STRING_to_UTF8(&text, this->get());
  if (length < 0) { return { }; }
  return {
    reinterpret_cast<char const*>(text),
    static_cast<std::size_t>(length)
  };
}

string::size_type string::length () const noexcept { return ASN1_STRING_length(this->get()); }
string::size_type string::size () const noexcept { return this->length(); }
bool string::empty () const noexcept { return this->size(); }

} /* namespace aegis */
