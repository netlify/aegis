#include <aegis/x509.hpp>
#include <aegis/io.hpp>

#include <apex/core/utility.hpp>

#include <openssl/x509.h>
#include <openssl/ssl.h>

namespace aegis {

void retain_traits<X509>::increment (X509* ptr) noexcept { X509_up_ref(ptr); }
void retain_traits<X509>::decrement (X509* ptr) noexcept { X509_free(ptr); }

} /* namespace aegis */

namespace aegis::x509 {

certificate::certificate (io::stream_view const& stream) noexcept :
  retain_handle<X509> { PEM_read_bio_X509_AUX(stream.get(), nullptr, nullptr, nullptr) }
{ }

stack<GENERAL_NAME> certificate::subject_alternative_names () const noexcept {
  return stack<GENERAL_NAME> {
    static_cast<GENERAL_NAMES*>(
      X509_get_ext_d2i(
        this->get(),
        NID_subject_alt_name,
        nullptr,
        nullptr)
    )
  };
}

name certificate::subject_name () const noexcept {
  return name { X509_get_subject_name(this->get()) };
}

entry name::operator [] (size_type idx) const noexcept {
  return entry { X509_NAME_get_entry(this->get(), idx) };
}

name::size_type name::find (extension e, size_type s) const noexcept {
  return X509_NAME_get_index_by_NID(this->get(), apex::to_underlying(e), static_cast<int>(s));
}

name::size_type name::find (extension e) const noexcept {
  return X509_NAME_get_index_by_NID(this->get(), apex::to_underlying(e), -1);
}

name::size_type name::size () const noexcept {
  return X509_NAME_entry_count(this->get());
}

string entry::data () const noexcept {
  return string { ASN1_STRING_dup(X509_NAME_ENTRY_get_data(this->get())) };
}

} /* namespace aegis::x509 */
