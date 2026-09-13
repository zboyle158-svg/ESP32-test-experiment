# Install script for directory: J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/iot_env_monitor")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "J:/Espressif/tools/riscv32-esp-elf/esp-14.2.0_20260121/riscv32-esp-elf/bin/riscv32-esp-elf-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "J:/esp/v5.5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

