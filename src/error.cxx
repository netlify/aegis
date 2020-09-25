#include <aegis/error.hpp>

#include <apex/mixin/singleton.hpp>
#include <openssl/err.h>

namespace {

/* We rely on NRVO optimizations to reduce unnecessary allocations. Do NOT
 * call std::move. That will remove the ability to optimize this call
 */
::std::string to_error_string (int reason) {
  ::std::string buffer(512, '\0');
  ERR_error_string_n(reason, buffer.data(), buffer.capacity());
  return buffer;
}

struct category : ::std::error_category {
  virtual ::std::string message (int reason) const override final {
    return to_error_string(reason);
  }
};

struct async final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::async";
  }
};

struct asn1 final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::asn1";
  }
};

struct bignum final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::bignum";
  }
};

struct certificate_management_protocol : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::certificate_management_protocol";
  }
};

struct cryptographic_message_syntax : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::cryptographic_message_syntax";
  }
};

struct certificate_transparency : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::certificate_transparency";
  }
};

struct configuration : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::configuration";
  }
};

struct compression : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::compression";
  }
};

struct crypto : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::crypto";
  }
};

struct diffie_hellman : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::diffie_hellman";
  }
};

struct dsa : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::dsa";
  }
};

struct enhanced_security_service : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::enhanced_security_service";
  }
};

struct elliptic_curve : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::elliptic_curve";
  }
};

struct envelope : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::envelope";
  }
};

struct engine : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::engine";
  }
};

struct generic : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::generic";
  }
};

struct http : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::http";
  }
};

struct io final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::io";
  }
};

struct object final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::object";
  }
};

struct ocsp final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::ocsp";
  }
};

struct pkcs12 final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::pkcs12";
  }
};

struct pkcs7 final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::pkcs7";
  }
};

struct pem final : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::pem";
  }
};

struct random : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::random";
  }
};

struct rsa : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::rsa";
  }
};

struct store : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::store";
  }
};

struct ssl : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::ssl";
  }
};

struct ts : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::ts";
  }
};

struct ui : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::ui";
  }
};

struct x509v3 : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::x509v3";
  }
};

struct x509 : category {
  virtual char const* name () const noexcept override final {
    return "aegis::category::x509";
  }
};


} /* nameless namespace */

namespace aegis::category {

::std::error_category const& async () noexcept { return apex::global<::async const>; }
::std::error_category const& asn1 () noexcept { return apex::global<::asn1 const>; }

::std::error_category const& bignum () noexcept { return apex::global<::bignum const>; }

::std::error_category const& certificate_management_protocol () noexcept {
  return apex::global<::certificate_management_protocol const>;
}

::std::error_category const& certificate_transparency () noexcept {
  return apex::global<::certificate_transparency const>;
}

::std::error_category const& configuration () noexcept {
  return apex::global<::configuration const>;
}

::std::error_category const& compression () noexcept {
  return apex::global<::compression const>;
}

::std::error_category const& crypto () noexcept {
  return apex::global<::crypto const>;
}

::std::error_category const& diffie_hellman () noexcept {
  return apex::global<::diffie_hellman const>;
}

::std::error_category const& dsa () noexcept { return apex::global<::dsa const>; }

::std::error_category const& enhanced_security_service () noexcept {
  return apex::global<::enhanced_security_service const>;
}

::std::error_category const& elliptic_curve () noexcept {
  return apex::global<::elliptic_curve const>;
}

::std::error_category const& envelope () noexcept { return apex::global<::envelope const>; }
::std::error_category const& engine () noexcept { return apex::global<::engine const>; }

::std::error_category const& generic () noexcept { return apex::global<::generic const>; }

::std::error_category const& http () noexcept { return apex::global<::http const>; }

::std::error_category const& io () noexcept { return apex::global<::io const>; }

::std::error_category const& object () noexcept { return apex::global<::object const>; }
::std::error_category const& ocsp () noexcept { return apex::global<::ocsp const>; }

::std::error_category const& pkcs12 () noexcept { return apex::global<::pkcs12 const>; }
::std::error_category const& pkcs7 () noexcept { return apex::global<::pkcs7 const>; }
::std::error_category const& pem () noexcept { return apex::global<::pem const>; }

::std::error_category const& random () noexcept { return apex::global<struct random const>; }
::std::error_category const& rsa () noexcept { return apex::global<::rsa const>; }

::std::error_category const& store () noexcept { return apex::global<::store const>; }
::std::error_category const& ssl () noexcept { return apex::global<::ssl const>; }

::std::error_category const& ts () noexcept { return apex::global<::ts const>; }

::std::error_category const& ui () noexcept { return apex::global<::ui const>; }

::std::error_category const& x509v3 () noexcept { return apex::global<::x509v3 const>; }
::std::error_category const& x509 () noexcept { return apex::global<::x509 const>; }

} /* namespace aegis::category */
