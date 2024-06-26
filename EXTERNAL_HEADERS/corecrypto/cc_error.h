/* Copyright (c) (2017-2022) Apple Inc. All rights reserved.
 *
 * corecrypto is licensed under Apple Inc.’s Internal Use License Agreement (which
 * is contained in the License.txt file distributed with corecrypto) and only to
 * people who accept that license. IMPORTANT:  Any license rights granted to you by
 * Apple Inc. (if any) are limited to internal use within your organization only on
 * devices and computers you own or control, for the sole purpose of verifying the
 * security characteristics and correct functioning of the Apple Software.  You may
 * not, directly or indirectly, redistribute the Apple Software or any portions thereof.
 */

#ifndef _CORECRYPTO_CC_ERROR_H_
#define _CORECRYPTO_CC_ERROR_H_

enum {
    CCERR_OK = 0,

    /* the default error code */
    CCERR_INTERNAL = -1,

    CCERR_INTEGRITY = -2,

    CCERR_DEVICE = -3,
    CCERR_INTERRUPTS = -4,
    CCERR_CRYPTO_CONFIG = -5,
    CCERR_PERMS = -6,
    CCERR_PARAMETER = -7,
    CCERR_MEMORY = -8,
    CCERR_FILEDESC = -9,
    CCERR_OUT_OF_ENTROPY = -10,
    CCERR_ATFORK = -11,
    CCERR_OVERFLOW = -12,

    CCERR_MEMORY_ALLOC_FAIL = -13,

    CCEC_GENERATE_KEY_DEFAULT_ERR = -14,
    CCEC_GENERATE_KEY_TOO_MANY_TRIES = -15,
    CCEC_GENERATE_KEY_MULT_FAIL = -16,
    CCEC_GENERATE_KEY_AFF_FAIL = -17,
    CCEC_GENERATE_KEY_CONSISTENCY = -18,
    CCEC_GENERATE_NOT_ON_CURVE = -19,
    CCEC_GENERATE_NOT_ENOUGH_ENTROPY = -20,
    CCEC_GENERATE_NOT_SUPPORTED = -21,
    CCEC_GENERATE_INVALID_INPUT = -22,

    // Program error: buffer too small or encrypted message is too small
    CCRSA_INVALID_INPUT = -23,
    // Invalid crypto configuration: Hash length versus RSA key size
    CCRSA_INVALID_CONFIG = -24,
    CCRSA_ENCODING_ERROR = -25,
    CCRSA_DECODING_ERROR = -26,

    // The data is invalid (we won't say more for security)
    CCRSA_PRIVATE_OP_ERROR = -27,
    CCRSA_KEY_ERROR = -28,

    // Key generation specific
    CCRSA_KEYGEN_PRIME_NOT_FOUND = -29,
    CCRSA_KEYGEN_PRIME_NEED_NEW_SEED = -30,
    CCRSA_KEYGEN_PRIME_TOO_MANY_ITERATIONS = -31,
    CCRSA_KEYGEN_PRIME_SEED_GENERATION_ERROR = -32,
    CCRSA_KEYGEN_MODULUS_CRT_INV_ERROR = -33,
    CCRSA_KEYGEN_NEXT_PRIME_ERROR = -34,
    CCRSA_KEYGEN_SEED_X_ERROR = -35,
    CCRSA_KEYGEN_SEED_r_ERROR = -36,
    CCRSA_KEYGEN_KEYGEN_CONSISTENCY_FAIL = -37,
    CCRSA_KEYGEN_R1R2_SIZE_ERROR = -38,
    CCRSA_KEYGEN_PQ_DELTA_ERROR = -39,

    CCRSA_FIPS_KEYGEN_DISABLED = -40,

    CCZP_INV_ERROR = -41,
    CCZP_INV_NO_INVERSE = -42,
    CCZP_INV_INVALID_INPUT = -43,

    CCZ_INVALID_INPUT_ERROR = -44,
    CCZ_INVALID_RADIX_ERROR = -45,

    CCDH_ERROR_DEFAULT = -46,
    CCDH_GENERATE_KEY_TOO_MANY_TRIES = -47,
    CCDH_NOT_SUPPORTED_CONFIGURATION = -48,
    CCDH_SAFETY_CHECK = -49,
    CCDH_PUBLIC_KEY_MISSING = -50,
    CCDH_INVALID_DOMAIN_PARAMETER = -51,
    CCDH_INVALID_INPUT = -52,
    CCDH_DOMAIN_PARAMETER_MISMATCH = -53,
    CCDH_GENERATE_KEY_CONSISTENCY = -54,

    CCSRP_ERROR_DEFAULT = -55,
    CCSRP_GENERATE_KEY_TOO_MANY_TRIES = -56,
    CCSRP_NOT_SUPPORTED_CONFIGURATION = -57,
    CCSRP_SAFETY_CHECK = -58,
    CCSRP_PUBLIC_KEY_MISSING = -59,
    CCSRP_INVALID_DOMAIN_PARAMETER = -60,

    CCDRBG_STATUS_ERROR = -61,
    CCDRBG_STATUS_NEED_RESEED = -62,
    CCDRBG_STATUS_PARAM_ERROR = -63,
    // If this value is returned, the caller must abort or panic the process for
    // security reasons. For example in the case of catastrophic error in
    // http://csrc.nist.gov/publications/drafts/800-90/sp800_90a_r1_draft.pdf
    // ccdrbg calls abort() or panic(), if they are available in the system.
    CCDRBG_STATUS_ABORT = -64,

    CCKPRNG_NEED_ENTROPY = -65,
    CCKPRNG_ABORT = -66,

    CCMODE_INVALID_INPUT = -67,
    CCMODE_INVALID_CALL_SEQUENCE = -68,
    CCMODE_INTEGRITY_FAILURE = -69,
    CCMODE_NOT_SUPPORTED = -70,
    CCMODE_INTERNAL_ERROR = -71,

    // Configuration or unexpected issue
    CCPOST_GENERIC_FAILURE = -72,
    CCPOST_LIBRARY_ERROR = -73,
    CCPOST_INTEGRITY_ERROR = -74,
    // Output of the algo is not as expected
    CCPOST_KAT_FAILURE = -75,

    CCKPRNG_SEEDFILE_OPEN = -76,
    CCKPRNG_SEEDFILE_READ = -78,
    CCKPRNG_SEEDFILE_WRITE = -79,
    CCKPRNG_SEEDFILE_CHMOD = -80,
    CCKPRNG_SEEDFILE_CHOWN = -81,
    CCKPRNG_RANDOMDEV_OPEN = -82,
    CCKPRNG_RANDOMDEV_WRITE = -83,
    CCKPRNG_GETENTROPY = -84,

    CCSAE_HUNTPECK_EXCEEDED_MAX_TRIALS = -85,

    CCERR_CALL_SEQUENCE = -86,

    CCVRF_POINT_DECODE_FAILURE = -87,
    CCVRF_POINT_INVALID_PUBLIC_KEY = -88,
    CCVRF_VERIFY_FAILURE = -89,

    // Error codes for Authenticated Encryption Modes
    CCMODE_TAG_LENGTH_REQUEST_TOO_LONG = -100,
    CCMODE_TAG_LENGTH_TOO_SHORT = -101,
    CCMODE_NONCE_EMPTY = -102,
    CCMODE_AD_EMPTY = -103,
    CCMODE_DECRYPTION_OR_VERIFICATION_ERR=-104,
    CCMODE_BUFFER_OUT_IN_OVERLAP = -105,

    // Error codes for Secret Sharing
    CCSS_ELEMENT_TOO_LARGE_FOR_FIELD = -120,
    CCSS_NOT_ENOUGH_SHARES = -121,
    CCSS_TOO_MANY_SHARES = -122,
    CCSS_IMPROPER_DEGREE = -123,
    CCSS_TWO_SHARES_FOR_SAME_X = -124,
    CCSS_THRESHOLD_NOT_LARGE_ENOUGH = -125,
    CCSS_SHARE_BAG_FULL = -126,
    CCSS_SHARE_ALREADY_PRESENT_IN_SHARE_BAG = -127,
    CCSS_THRESHOLD_LARGER_OR_EQUAL_TO_FIELD = -128,
    CCSS_TOO_MANY_SHARES_REQUESTED = -129,
    CCSS_FIELD_MISMATCH = -130,
    CCSS_INDEX_OUT_OF_RANGE = -131,
    
    CCSAE_NOT_ENOUGH_COMMIT_PARTIAL_CALLS = -132,
    CCSAE_GENERATE_COMMIT_CALL_AGAIN = -133,

    CCERR_VALID_SIGNATURE = CCERR_OK,
    CCERR_INVALID_SIGNATURE = -146,

    CCERR_IOSERVICE_GETMATCHING = -147,
    CCERR_IOSERVICE_OPEN = -148,
    CCERR_IOCONNECT_CALL = -149,
    
    CCEC_KEY_CANNOT_BE_UNIT = -160,
    CCEC_COMPRESSED_POINT_ENCODING_ERROR = -161,

    CCERR_RNG_NOT_SEEDED = -162,
    
    CCERR_BUFFER_TOO_SMALL = -163,

    CCERR_XTS_KEYS_EQUAL = -164,

    CCERR_RETRY = -165,

    CCDH_GP_P_NOTPRIME = -166,
    CCDH_GP_Q_NOTPRIME = -167,
    CCDH_GP_NONSAFE_PRIME = -168,

    // -169, // deprecated

    CCEC_POINT_CANNOT_BE_UNIT = CCEC_KEY_CANNOT_BE_UNIT,
    CCEC_UNCOMPRESSED_POINT_ENCODING_ERROR = -170,
    CCEC_HYBRID_POINT_ENCODING_ERROR = -171,
    CCEC_COMPACT_POINT_ENCODING_ERROR = -172,

    CCERR_NOT_SUPPORTED = -173,
    
    // Always add error codes above this line, and always keep
    // their value greater than the value of CCERR_MIN.
    CCERR_MIN = -255,
};

#define CCDRBG_STATUS_OK CCERR_OK
#define CCKPRNG_OK CCERR_OK

#endif /* _CORECRYPTO_CC_ERROR_H_ */
