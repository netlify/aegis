#ifndef AEGIS_CONSTANTS_HPP
#define AEGIS_CONSTANTS_HPP

#include <openssl/obj_mac.h>

namespace aegis {

enum class extension {
  common_name = NID_commonName,
};

} /* namespace aegis */

#endif /* AEGIS_CONSTANTS_HPP */
