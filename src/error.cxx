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

} /* nameless namespace */

namespace aegis::category {

::std::error_category const& async () noexcept { return apex::global<::async const>; }
::std::error_category const& asn1 () noexcept { return apex::global<::asn1 const>; }

::std::error_category const& bignum () noexcept { return apex::global<::bignum const>; }

::std::error_category const& io () noexcept { return apex::global<::io const>; }

} /* namespace aegis::category */
