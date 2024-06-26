/* Copyright (c) (2012-2019,2021,2022) Apple Inc. All rights reserved.
 *
 * corecrypto is licensed under Apple Inc.’s Internal Use License Agreement (which
 * is contained in the License.txt file distributed with corecrypto) and only to
 * people who accept that license. IMPORTANT:  Any license rights granted to you by
 * Apple Inc. (if any) are limited to internal use within your organization only on
 * devices and computers you own or control, for the sole purpose of verifying the
 * security characteristics and correct functioning of the Apple Software.  You may
 * not, directly or indirectly, redistribute the Apple Software or any portions thereof.
 */

#ifndef _CORECRYPTO_CCDER_H_
#define _CORECRYPTO_CCDER_H_

#include <corecrypto/cc.h>
#include <corecrypto/ccasn1.h>
#include <corecrypto/ccn.h>
#include <corecrypto/ccder_blob.h>

/* DER types to be used with ccder_decode and ccder_encode functions. */
#define CCDER_EOL CCASN1_EOL
#define CCDER_BOOLEAN CCASN1_BOOLEAN
#define CCDER_INTEGER CCASN1_INTEGER
#define CCDER_BIT_STRING CCASN1_BIT_STRING
#define CCDER_OCTET_STRING CCASN1_OCTET_STRING
#define CCDER_NULL CCASN1_NULL
#define CCDER_OBJECT_IDENTIFIER CCASN1_OBJECT_IDENTIFIER
#define CCDER_OBJECT_DESCRIPTOR CCASN1_OBJECT_DESCRIPTOR
/* External or instance-of 0x08 */
#define CCDER_REAL CCASN1_REAL
#define CCDER_ENUMERATED CCASN1_ENUMERATED
#define CCDER_EMBEDDED_PDV CCASN1_EMBEDDED_PDV
#define CCDER_UTF8_STRING CCASN1_UTF8_STRING
/*                         0x0d */
/*                         0x0e */
/*                         0x0f */
#define CCDER_SEQUENCE CCASN1_SEQUENCE
#define CCDER_SET CCASN1_SET
#define CCDER_NUMERIC_STRING CCASN1_NUMERIC_STRING
#define CCDER_PRINTABLE_STRING CCASN1_PRINTABLE_STRING
#define CCDER_T61_STRING CCASN1_T61_STRING
#define CCDER_VIDEOTEX_STRING CCASN1_VIDEOTEX_STRING
#define CCDER_IA5_STRING CCASN1_IA5_STRING
#define CCDER_UTC_TIME CCASN1_UTC_TIME
#define CCDER_GENERALIZED_TIME CCASN1_GENERALIZED_TIME
#define CCDER_GRAPHIC_STRING CCASN1_GRAPHIC_STRING
#define CCDER_VISIBLE_STRING CCASN1_VISIBLE_STRING
#define CCDER_GENERAL_STRING CCASN1_GENERAL_STRING
#define CCDER_UNIVERSAL_STRING CCASN1_UNIVERSAL_STRING
/*                         0x1d */
#define CCDER_BMP_STRING CCASN1_BMP_STRING
#define CCDER_HIGH_TAG_NUMBER CCASN1_HIGH_TAG_NUMBER
#define CCDER_TELETEX_STRING CCDER_T61_STRING

#ifdef CCDER_MULTIBYTE_TAGS
#define CCDER_TAG_MASK ((ccder_tag)~0)
#define CCDER_TAGNUM_MASK ((ccder_tag) ~((ccder_tag)7 << (sizeof(ccder_tag) * 8 - 3)))

#define CCDER_METHOD_MASK ((ccder_tag)1 << (sizeof(ccder_tag) * 8 - 3))
#define CCDER_PRIMITIVE ((ccder_tag)0 << (sizeof(ccder_tag) * 8 - 3))
#define CCDER_CONSTRUCTED ((ccder_tag)1 << (sizeof(ccder_tag) * 8 - 3))

#define CCDER_CLASS_MASK ((ccder_tag)3 << (sizeof(ccder_tag) * 8 - 2))
#define CCDER_UNIVERSAL ((ccder_tag)0 << (sizeof(ccder_tag) * 8 - 2))
#define CCDER_APPLICATION ((ccder_tag)1 << (sizeof(ccder_tag) * 8 - 2))
#define CCDER_CONTEXT_SPECIFIC ((ccder_tag)2 << (sizeof(ccder_tag) * 8 - 2))
#define CCDER_PRIVATE ((ccder_tag)3 << (sizeof(ccder_tag) * 8 - 2))
#else /* !CCDER_MULTIBYTE_TAGS */
#define CCDER_TAG_MASK CCASN1_TAG_MASK
#define CCDER_TAGNUM_MASK CCASN1_TAGNUM_MASK

#define CCDER_METHOD_MASK CCASN1_METHOD_MASK
#define CCDER_PRIMITIVE CCASN1_PRIMITIVE
#define CCDER_CONSTRUCTED CCASN1_CONSTRUCTED

#define CCDER_CLASS_MASK CCASN1_CLASS_MASK
#define CCDER_UNIVERSAL CCASN1_UNIVERSAL
#define CCDER_APPLICATION CCASN1_APPLICATION
#define CCDER_CONTEXT_SPECIFIC CCASN1_CONTEXT_SPECIFIC
#define CCDER_PRIVATE CCASN1_PRIVATE
#endif /* !CCDER_MULTIBYTE_TAGS */
#define CCDER_CONSTRUCTED_SET (CCDER_SET | CCDER_CONSTRUCTED)
#define CCDER_CONSTRUCTED_SEQUENCE (CCDER_SEQUENCE | CCDER_CONSTRUCTED)

// MARK: - ccder_sizeof_ functions

/* Returns the size of an asn1 encoded item of length l in bytes. */
CC_CONST
size_t ccder_sizeof(ccder_tag tag, size_t len);

CC_NONNULL_ALL
size_t ccder_sizeof_overflow(ccder_tag tag, size_t nbytes, bool *overflowed);

CC_PURE
size_t ccder_sizeof_implicit_integer(ccder_tag implicit_tag, cc_size n, const cc_unit *s);

CC_PURE
size_t ccder_sizeof_implicit_octet_string(ccder_tag implicit_tag, cc_size n, const cc_unit *s);

CC_CONST
size_t ccder_sizeof_implicit_raw_octet_string(ccder_tag implicit_tag, size_t s_size);

CC_NONNULL_ALL
size_t ccder_sizeof_implicit_raw_octet_string_overflow(ccder_tag implicit_tag, size_t s_size, bool *overflowed);

CC_CONST
size_t ccder_sizeof_implicit_uint64(ccder_tag implicit_tag, uint64_t value);

CC_PURE
size_t ccder_sizeof_integer(cc_size n, const cc_unit *s);

CC_CONST
size_t ccder_sizeof_len(size_t len);

CC_PURE
size_t ccder_sizeof_octet_string(cc_size n, const cc_unit *s);

CC_PURE
size_t ccder_sizeof_oid(ccoid_t oid);

CC_CONST
size_t ccder_sizeof_raw_octet_string(size_t s_size);

CC_CONST
size_t ccder_sizeof_tag(ccder_tag tag);

CC_CONST
size_t ccder_sizeof_uint64(uint64_t value);

CC_PURE
size_t ccder_sizeof_eckey(size_t priv_size, ccoid_t oid, size_t pub_size);

/* alias of ccder_sizeof_eckey */
CC_PURE
size_t ccder_encode_eckey_size(size_t priv_size, ccoid_t oid, size_t pub_size);

/* All of the original functions are unavailable in a ptrcheck build. */
// MARK: - Encode/decode functions, unavailable in ptrcheck

/* Encode a tag backwards, der_end should point to one byte past the end of
   destination for the tag, returns a pointer to the first byte of the tag.
   Returns NULL if there is an encoding error. */
CC_NONNULL((2)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_tag(ccder_tag tag, const uint8_t *der, uint8_t *der_end);

/* Returns a pointer to the start of the len field.  returns NULL if there
 is an encoding error. */
CC_NONNULL((2)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_len(size_t len, const uint8_t *der, uint8_t *der_end);

/* der_end should point to the first byte of the content of this der item. */
CC_NONNULL((3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_tl(ccder_tag tag, size_t len, const uint8_t *der, uint8_t *der_end);

CC_PURE CC_NONNULL((2)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_body_nocopy(size_t size, const uint8_t *der, uint8_t *der_end);

/* Encode the tag and length of a constructed object.  der is the lower
   bound, der_end is one byte paste where we want to write the length and
   body_end is one byte past the end of the body of the der object we are
   encoding the tag and length of. */
CC_NONNULL((2, 3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_constructed_tl(ccder_tag tag, const uint8_t *body_end, const uint8_t *der, uint8_t *der_end);

/* Encodes oid into der and returns der + ccder_sizeof_oid(oid). */
CC_NONNULL((1, 2)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_oid(ccoid_t oid, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((3, 4)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_implicit_integer(ccder_tag implicit_tag, cc_size n, const cc_unit *s, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((2, 3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_integer(cc_size n, const cc_unit *s, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_implicit_uint64(ccder_tag implicit_tag, uint64_t value, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((2)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_uint64(uint64_t value, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((3, 4)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_implicit_octet_string(ccder_tag implicit_tag, cc_size n, const cc_unit *s, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((2, 3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_octet_string(cc_size n, const cc_unit *s, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((3, 4)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_implicit_raw_octet_string(ccder_tag implicit_tag,
                                                size_t s_size,
                                                const uint8_t *s,
                                                const uint8_t *der,
                                                uint8_t *der_end);

CC_NONNULL((2, 3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_raw_octet_string(size_t s_size, const uint8_t *s, const uint8_t *der, uint8_t *der_end);

CC_NONNULL((2, 5, 6)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_eckey(size_t priv_size,
                            const uint8_t *priv_key,
                            ccoid_t oid,
                            size_t pub_size,
                            const uint8_t *pub_key,
                            uint8_t *der,
                            uint8_t *der_end);

/* ccder_encode_body COPIES the body into the der.
   It's inefficient – especially when you already have to convert to get to
   the form for the body.
   see encode integer for the right way to unify conversion and insertion */
CC_NONNULL((3)) cc_ptrcheck_unavailable()
uint8_t *ccder_encode_body(size_t size, const uint8_t *body, const uint8_t *der, uint8_t *der_end);

/* Returns a pointer to the start of the length field, and returns the decoded tag in tag.
 returns NULL if there is a decoding error. */
CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_tag(ccder_tag *tagp, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_len(size_t *lenp, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_len_strict
 @abstract   Decode the length of a DER encoded item

 @param      lenp     Pointer to the length of the DER item
 @param      der      Beginning of input DER buffer
 @param      der_end  End of input DER buffer

 @result     First byte after the parsed length or NULL if the length is not valid (i.e. when the length isn't DER encoded)
 */
CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_len_strict(size_t *lenp, const uint8_t *der, const uint8_t *der_end);

/* Returns a pointer to the start of the der object, and returns the length in len.
 returns NULL if there is a decoding error. */
CC_NONNULL((2, 4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_tl(ccder_tag expected_tag, size_t *lenp, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_tl_strict
 @abstract   Decode a tag and length from a DER object given an expected tag.

 @param      expected_tag  Tag of expected DER object pointed to by `der`
 @param      lenp          Output length of DER object
 @param      der           Beginning of input DER buffer
 @param      der_end       End of input DER buffer

 @result     Pointer to the DER object with the length contained in `lenp` otherwise NULL.
 */
CC_NONNULL((2, 4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_tl_strict(ccder_tag expected_tag, size_t *lenp, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((2, 4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_constructed_tl(ccder_tag expected_tag,
                                           const uint8_t **body_end,
                                           const uint8_t *der,
                                           const uint8_t *der_end);

/*!
 @function   ccder_decode_constructed_tl_strict
 @abstract   Decode a tag and length from a contstructed DER object given an expected tag.

 @param      expected_tag  Tag of expected DER object pointed to by `der`
 @param      body_end      Pointer to hold the end of the sequence
 @param      der           Beginning of input DER buffer
 @param      der_end       End of input DER buffer

 @result     Pointer to the first DER object within the constructed object and the length of the total constructed object
 contained in `lenp`; NULL otherwise.
 */
CC_NONNULL((2, 4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_constructed_tl_strict(ccder_tag expected_tag, const uint8_t **body_end, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_sequence_tl(const uint8_t **body_end, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_sequence_tl_strict
 @abstract   Decode a DER sequence.

 @param      body_end Pointer to hold the end of the sequence
 @param      der      Beginning of input DER buffer
 @param      der_end  End of input DER buffer

 @result     Pointer to the first DER object within the sequence otherwise NULL.
 */
CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_sequence_tl_strict(const uint8_t **body_end, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_uint_n
 @abstract   length in cc_unit of a der unsigned integer after skipping the leading zeroes

 @param      der           Beginning of input DER buffer
 @param      der_end  End of input DER buffer
 @param      n               Output the number of cc_unit required to represent the number

 @result     First byte after the parsed integer or
        NULL if the integer is not valid (negative) or reach der_end when reading the integer
 */
CC_NONNULL((3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_uint_n(cc_size *n, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_uint
 @abstract   Represent in cc_unit a ber unsigned integer after skipping the leading zeroes

 @param      der           Beginning of input BER buffer
 @param      der_end  End of input BER buffer
 @param      n                Number of cc_unit allocated for r
 @param      r                Allocated array of cc_unit to copy the integer into.

 @result     First byte after the parsed integer or
NULL if the integer is not valid (negative)
            reach der_end when reading the integer
            n cc_unit is not enough to represent the integer
 */
CC_NONNULL((4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_uint(cc_size n, cc_unit *r, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_uint_strict
 @abstract   Represent in cc_unit a der unsigned integer after skipping the leading zeroes

 @param      n        Number of cc_unit allocated for r
 @param      r        Allocated array of cc_unit to copy the integer into.
 @param      der      Beginning of input DER buffer
 @param      der_end  End of input DER buffer

 @result     First byte after the parsed integer or NULL if the integer is not valid.
 */
CC_NONNULL((4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_uint_strict(cc_size n, cc_unit *r, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_uint64(uint64_t *r, const uint8_t *der, const uint8_t *der_end);

/* Decode SEQUENCE { r, s -- (unsigned)integer } in ber into r and s.
   Returns NULL on decode errors, returns pointer just past the end of the
   sequence of integers otherwise. */
CC_NONNULL((2, 3, 5)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_seqii(cc_size n, cc_unit *r, cc_unit *s, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_seqii_strict
 @abstract   Parse a DER sequence of two integers.

 @param      n        The maximum unit size of the integers.
 @param      r        First integer output
 @param      s        Second integer output
 @param      der      Beginning of input DER buffer
 @param      der_end  End of input DER buffer

 @result     Null on error, otherwise a pointer just past the end of the sequence buffer
 */
CC_NONNULL((2, 3, 5)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_seqii_strict(cc_size n, cc_unit *r, cc_unit *s, const uint8_t *der, const uint8_t *der_end);

/*!
 @function   ccder_decode_oid
 @abstract   Parse a DER sequence representing an oid.

 @param      oidp     Pointer to OID
 @param      der      Beginning of input DER buffer
 @param      der_end  End of input DER buffer

 @result     Null on error, otherwise a pointer just past the end of the sequence buffer.
 
 @warning    In case of error, *oidp is set to NULL.
             Otherwise, *oidp is a pointer to a buffer of "unsigned char" of size >= 2.
 */
CC_NONNULL((1, 3)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_oid(ccoid_t *oidp, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((1, 2, 4)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_bitstring(const uint8_t **bit_string, size_t *bit_length, const uint8_t *der, const uint8_t *der_end);

CC_NONNULL((1, 2, 3, 4, 5, 6, 7)) cc_ptrcheck_unavailable()
const uint8_t *ccder_decode_eckey(uint64_t *version,
                                  size_t *priv_size,
                                  const uint8_t **priv_key,
                                  ccoid_t *oid,
                                  size_t *pub_size,
                                  const uint8_t **pub_key,
                                  const uint8_t *der,
                                  const uint8_t *der_end);

// MARK: -

#define CC_EC_OID_SECP192R1                                           \
    {                                                                 \
        ((unsigned char *)"\x06\x08\x2a\x86\x48\xce\x3d\x03\x01\x01") \
    }
#define CC_EC_OID_SECP256R1                                           \
    {                                                                 \
        ((unsigned char *)"\x06\x08\x2a\x86\x48\xce\x3d\x03\x01\x07") \
    }
#define CC_EC_OID_SECP224R1                               \
    {                                                     \
        ((unsigned char *)"\x06\x05\x2B\x81\x04\x00\x21") \
    }
#define CC_EC_OID_SECP384R1                               \
    {                                                     \
        ((unsigned char *)"\x06\x05\x2B\x81\x04\x00\x22") \
    }
#define CC_EC_OID_SECP521R1                               \
    {                                                     \
        ((unsigned char *)"\x06\x05\x2B\x81\x04\x00\x23") \
    }

#endif /* _CORECRYPTO_CCDER_H_ */
