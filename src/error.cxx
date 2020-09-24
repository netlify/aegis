#include <aegis/error.hpp>

#include <apex/mixin/singleton.hpp>
#include <openssl/err.h>

namespace {

/* We rely on NRVO optimizations to reduce unnecessary allocations. Do NOT
 * call std::move. That will remove the ability to optimize this call
 */
::std::string to_error_string (int reason) {
  ::std::string buffer { 512 };
  ERR_error_string_n(reason, buffer.data(), buffer.capacity());
  return buffer;
}

struct category : ::std::error_category {
  virtual ::std::string message (int reason) const override final { return to_error_string(reason); }
};

struct async final : category {
  virtual char const* name () const noexcept override final { return "openssl async"; }
};

struct io final : category {
  virtual char const* name () const noexcept override final { return "openssl io"; }
};

} /* nameless namespace */

namespace aegis::category {

::std::error_category const& async () noexcept { return apex::global<::async const>; }
::std::error_category const& io () noexcept { return apex::global<::io const>; }

} /* namespace aegis::category */
