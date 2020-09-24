#include <aegis/error.hpp>

#include <apex/mixin/singleton.hpp>
#include <openssl/err.h>


namespace { namespace categories {

struct io final : ::std::error_category {
  /* We rely on NRVO optimizations to reduce unnecessary allocations. Do NOT
   * call std::move. That will remove the ability to optimize this call
   */
  virtual ::std::string message (int condition) const override final {
    ::std::string buffer { 512 };
    ERR_error_string_n(condition, buffer.data(), buffer.capacity());
    return buffer;
  }
  virtual char const* name () const noexcept override final { return "openssl io"; }
};

}} /* namespace ::categories */

namespace aegis::category {

::std::error_category const& io () noexcept { return apex::global<::categories::io const>; }

} /* namespace aegis::category */
