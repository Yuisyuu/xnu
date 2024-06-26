/*!
 * @header
 * Provides an interface for managing nonces to govern the lifetime of a
 * personalization performed with TSS. A nonce managed by this interface may
 * be used in a TSS signing request as the value for the BNCH tag.
 *
 * These interfaces require the caller to possess the
 *
 *     com.apple.private.security.AppleImage4.user-client
 *
 * entitlement.
 *
 * @section Threat Model
 * The adversary possesses the following:
 *
 *     1. a manifest which was previously valid but has since been invalidated
 *        by rolling the nonce associated with it
 *     2. user-level code execution
 *     3. knowledge of the raw nonce value for the previously-valid manifest
 *
 * The defense against this adversary is a system in which knowledge of the raw
 * nonce is insufficient to impact the evaluation of a personalization. This
 * system has the following characteristics:
 *
 *     1. A nonce seed is stored in an nvram variable which is only writable by
 *        the kernel
 *     2. When making a new signing request, the nonce seed is encrypted by a
 *        UID1-derived key in-kernel and then hashed -- the output of this
 *        operation the nonce to be used in the signing request
 *     3. On boot, AppleImage4 obtains the nonce seed from nvram and stores it
 *        in a data structure which will be covered by KTRR
 *     4. When evaluating a manifest, AppleImage4 reads the raw nonce from the
 *        KTRR-covered data structure and validates it with the same
 *        transformation as was done in (2)
 *     5. When the nonce is to be invalidated, AppleImage4 sets a flag in an
 *        nvram variable which is only writable by the kernel
 *     6. On the subsequent boot, AppleImage4 notices the flag, generates a new
 *        nonce and repeats the procedure in (3)
 *
 * In this system, the raw nonce seed never leaves the kernel, and the nonce
 * itself is a non-reversible representation of the seed.
 */


#ifndef __IMG4_NONCE_H
#define __IMG4_NONCE_H

#ifndef __IMG4_INDIRECT
#error "Please #include <img4/firmware.h> instead of this file directly"
#endif // __IMG4_INDIRECT

__BEGIN_DECLS
OS_ASSUME_NONNULL_BEGIN
OS_ASSUME_PTR_ABI_SINGLE_BEGIN

/*!
 * @typedef img4_nonce_domain_t
 * An opaque type describing a nonce domain.
 */
IMG4_API_AVAILABLE_20181106
typedef struct _img4_nonce_domain img4_nonce_domain_t;

/*!
 * @const IMG4_NONCE_STRUCT_VERSION
 * The version of the {@link img4_nonce_t} structure supported by the
 * implementation.
 */
#define IMG4_NONCE_STRUCT_VERSION ((img4_struct_version_t)0)
#define IMG4_NONCE_VERSION IMG4_NONCE_STRUCT_VERSION

/*!
 * @const IMG4_NONCE_MAX_LENGTH
 * The maximum length of a nonce. Currently, this is the length of a SHA2-384
 * hash.
 */
#define IMG4_NONCE_MAX_LENGTH (48u)

/*!
 * @typedef img4_nonce_domain_index_t
 * An enumeration describing nonce domains.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_TEST
 * The enumerated constant corresponding to the internal test nonce domain.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_TRUST_CACHE
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_TRUST_CACHE}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_PDI
 * The enumerated constant corresponding to {@link IMG4_NONCE_DOMAIN_TRUST_PDI}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX
 * The enumerated constant corresponding to {@link IMG4_NONCE_DOMAIN_CRYPTEX}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_DDI
 * The enumerated constant corresponding to {@link IMG4_NONCE_DOMAIN_DDI}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_EPHEMERAL_CRYPTEX
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_EPHEMERAL_CRYPTEX}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_SNUF_STUB
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_CRYPTEX1_SNUF_STUB}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_BOOT
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_CRYPTEX1_BOOT}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_ASSET
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_CRYPTEX1_ASSET}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_GENERIC
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_CRYPTEX1_GENERIC}.
 *
 * @const IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_SIMULATOR
 * The enumerated constant corresponding to
 * {@link IMG4_NONCE_DOMAIN_CRYPTEX1_SIMULATOR}.
 *
 * @const _IMG4_NONCE_DOMAIN_INDEX_CNT
 * A sentinel value indicating the number of nonce domains.
 */
IMG4_API_AVAILABLE_20210521
OS_CLOSED_ENUM(img4_nonce_domain_index, uint64_t,
	IMG4_NONCE_DOMAIN_INDEX_TEST = 0,
	IMG4_NONCE_DOMAIN_INDEX_TRUST_CACHE,
	IMG4_NONCE_DOMAIN_INDEX_PDI,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX,
	IMG4_NONCE_DOMAIN_INDEX_DDI,
	IMG4_NONCE_DOMAIN_INDEX_EPHEMERAL_CRYPTEX,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_SNUF_STUB,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_BOOT,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_ASSET,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_GENERIC,
	IMG4_NONCE_DOMAIN_INDEX_CRYPTEX1_SIMULATOR,
	_IMG4_NONCE_DOMAIN_INDEX_CNT,
);

/*!
 * @typedef img4_nonce_t
 * A structure describing a nonce.
 *
 * @field i4n_version
 * The version of the structure. When declaring this structure, you must
 * initialize this field to {@link IMG4_NONCE_VERSION}.
 *
 * @field i4n_nonce
 * The bytes comprising the nonce.
 *
 * @field i4n_length
 * The length of the nonce. Will be at most {@link IMG4_NONCE_MAX_LENGTH}.
 *
 * @discussion
 * The {@link i4n_nonce} field was previously const. This was a terrible idea,
 * and the const storage qualifier was removed without adjusting the structure
 * version.
 */
IMG4_API_AVAILABLE_20181106
typedef struct _img4_nonce {
	img4_struct_version_t i4n_version;
	uint8_t i4n_nonce[IMG4_NONCE_MAX_LENGTH];
	uint32_t i4n_length;
} img4_nonce_t;

/*!
 * @const IMG4_NONCE_INIT
 * A convenience initializer for {@link img4_nonce_t} which ensures that the
 * {@link i4n_version} field is properly initialized.
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define IMG4_NONCE_INIT (img4_nonce_t){.i4n_version = IMG4_NONCE_STRUCT_VERSION}
#elif defined(__cplusplus) && __cplusplus >= 201103L
#define IMG4_NONCE_INIT (img4_nonce_t{IMG4_NONCE_STRUCT_VERSION})
#elif defined(__cplusplus)
#define IMG4_NONCE_INIT \
		(img4_nonce_t((img4_nonce_t){IMG4_NONCE_STRUCT_VERSION}))
#else
#define IMG4_NONCE_INIT {IMG4_NONCE_STRUCT_VERSION}
#endif

/*!
 * @const IMG4_NONCE_ZERO
 * A convenience initializer for {@link img4_nonce_t} which initializes a 48-
 * byte nonce of all zeroes.
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define IMG4_NONCE_ZERO (img4_nonce_t){ \
	.i4n_version = IMG4_NONCE_STRUCT_VERSION, \
	.i4n_nonce = {0}, \
	.i4n_length = IMG4_NONCE_MAX_LENGTH, \
}
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_TRUST_CACHE
 * The nonce domain governing trust cache personalizations. Use of this domain
 * requires the
 *
 *     com.apple.private.img4.nonce.trust-cache
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20181106
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_trust_cache;
#define IMG4_NONCE_DOMAIN_TRUST_CACHE (&_img4_nonce_domain_trust_cache)
#else
#define IMG4_NONCE_DOMAIN_TRUST_CACHE (img4if->i4if_v1.nonce_domain_trust_cache)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_PDI
 * The nonce domain governing disk image personalizations. Use of this domain
 * requires the
 *
 *     com.apple.private.img4.nonce.pdi
 *
 * entitlement. The nonce for this domain is regenerated once every boot.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20181106
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_pdi;
#define IMG4_NONCE_DOMAIN_PDI (&_img4_nonce_domain_pdi)
#else
#define IMG4_NONCE_DOMAIN_PDI (img4if->i4if_v3.nonce_domain_pdi)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX
 * The nonce domain governing cryptex personalizations. Use of this domain
 * requires the
 *
 *     com.apple.private.img4.nonce.cryptex
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20181106
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex;
#define IMG4_NONCE_DOMAIN_CRYPTEX (&_img4_nonce_domain_cryptex)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX (img4if->i4if_v3.nonce_domain_cryptex)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_DDI
 * The nonce domain governing developer disk image personalizations. Use of this
 * domain requires the
 *
 *     com.apple.private.img4.nonce.ddi
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20181106
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_ddi;
#define IMG4_NONCE_DOMAIN_DDI (&_img4_nonce_domain_ddi)
#else
#define IMG4_NONCE_DOMAIN_DDI (img4if->i4if_v12.nonce_domain_ddi)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_EPHEMERAL_CRYPTEX
 * The nonce domain governing ephemeral cryptex personalizations. Use of this
 * domain requires the
 *
 *     com.apple.private.img4.nonce.ephemeral-cryptex
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20210305
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_ephemeral_cryptex;
#define IMG4_NONCE_DOMAIN_EPHEMERAL_CRYPTEX \
		(&_img4_nonce_domain_ephemeral_cryptex)
#else
#define IMG4_NONCE_DOMAIN_EPHEMERAL_CRYPTEX \
		(img4if->i4if_v12.nonce_domain_ephemeral_cryptex)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX1_SNUF_STUB
 * The nonce domain which acts as a null stub for the snuf value for Cryptex1
 * processors. This domain corresponds to a value of 0 for the
 * Cryptex1,NonceDomain tag. Use of this domain requires the
 *
 *     com.apple.private.img4.nonce.cryptex1.snuf-stub
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20220322
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex1_snuf_stub;
#define IMG4_NONCE_DOMAIN_CRYPTEX1_SNUF_STUB \
		(&_img4_nonce_domain_cryptex1_snuf_stub)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX1_SNUF_STUB \
		(img4if->i4if_v18.nonce_domain_cryptex1_snuf_stub)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX1_BOOT
 * The nonce domain governing personalizations for the virtual Cryptex1
 * coprocessor's boot objects. This domain corresponds to a value of 1 for the
 * Cryptex1,NonceDomain tag. Use of this domain requires the
 *
 *     com.apple.private.img4.nonce.cryptex1.boot
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20211112
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex1_boot;
#define IMG4_NONCE_DOMAIN_CRYPTEX1_BOOT \
		(&_img4_nonce_domain_cryptex1_boot)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX1_BOOT \
		(img4if->i4if_v16.nonce_domain_cryptex1_boot)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX1_ASSET
 * The nonce domain governing personalizations for the virtual Cryptex1
 * coprocessor's asset brain objects. This domain corresponds to a value of 2
 * for the Cryptex1,NonceDomain tag. Use of this domain requires the
 *
 *     com.apple.private.img4.nonce.cryptex1.asset
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20211112
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex1_asset;
#define IMG4_NONCE_DOMAIN_CRYPTEX1_ASSET \
		(&_img4_nonce_domain_cryptex1_asset)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX1_ASSET \
		(img4if->i4if_v16.nonce_domain_cryptex1_asset)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX1_GENERIC
 * The nonce domain governing personalizations for the virtual Cryptex1
 * coprocessor's generic supplemental objects. This domain corresponds to a
 * value of 3 for the Cryptex1,NonceDomain tag. Use of this domain requires the
 *
 *     com.apple.private.img4.nonce.cryptex1.supplemental
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20221202
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex1_generic;
#define IMG4_NONCE_DOMAIN_CRYPTEX1_GENERIC \
		(&_img4_nonce_domain_cryptex1_generic)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX1_GENERIC \
		(img4if->i4if_v20.nonce_domain_cryptex1_generic)
#endif

/*!
 * @const IMG4_NONCE_DOMAIN_CRYPTEX1_SIMULATOR
 * The nonce domain governing personalizations for the virtual Cryptex1
 * coprocessor's Simulator runtime objects. This domain corresponds to a value
 * of 4 for the Cryptex1,NonceDomain tag. Use of this domain requires the
 *
 *     com.apple.private.img4.nonce.cryptex1.simulator
 *
 * entitlement.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20221202
OS_EXPORT
const struct _img4_nonce_domain _img4_nonce_domain_cryptex1_simulator;
#define IMG4_NONCE_DOMAIN_CRYPTEX1_SIMULATOR \
		(&_img4_nonce_domain_cryptex1_simulator)
#else
#define IMG4_NONCE_DOMAIN_CRYPTEX1_SIMULATOR \
		(img4if->i4if_v20.nonce_domain_cryptex1_simulator)
#endif

/*!
 * @function img4_nonce_domain_copy_nonce
 * Copies the current value of the nonce in the given domain.
 *
 * @param nd
 * The nonce domain.
 *
 * @param n
 * Upon successful return, storage that will contain the current nonce. The
 * provided structure's {@link i4n_version} must be initialized to
 * {@link IMG4_NONCE_VERSION}.
 *
 * @result
 * Upon success, zero is returned. The implementation may also return one of the
 * following error codes directly:
 *
 *     [ESTALE]     The nonce for the given domain has been invalidated, and the
 *                  host must reboot in order to generate a new one
 *     [EPERM]      The caller lacked the entitlement necessary to read the
 *                  given nonce
 *     [ENOTSUP]    Nonce management is not available on the host
 *     [EACCES]     The nonce requested is not accessible in this environment
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20210305
OS_EXPORT OS_WARN_RESULT OS_NONNULL1 OS_NONNULL2
errno_t
img4_nonce_domain_copy_nonce(const img4_nonce_domain_t *nd, img4_nonce_t *n);
#else
#define img4_nonce_domain_copy_nonce(...) \
		(img4if->i4if_v1.nonce_domain_copy_nonce(__VA_ARGS__))
#endif

/*!
 * @function img4_nonce_domain_roll_nonce
 * Invalidates the current nonce for the given domain and forces a re-generation
 * of the domain's nonce seed at the next boot.
 *
 * @param nd
 * The nonce domain.
 *
 * @result
 * Upon success, zero is returned. The kernel implementation will never return
 * a non-zero code. The userspace implementation may return one of the following
 * error codes directly:
 *
 *     [EPERM]      The caller lacked the entitlement necessary to roll the
 *                  given nonce
 *     [EROFS]      The boot mode didn't allow committing to non-volatile storage
 *     [ENOTSUP]    Nonce management is not available on the host
 *     [EACCES]     The nonce requested is not accessible in this environment
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20181106
OS_EXPORT OS_WARN_RESULT OS_NONNULL1
errno_t
img4_nonce_domain_roll_nonce(const img4_nonce_domain_t *nd);
#else
#define img4_nonce_domain_roll_nonce(...) \
		(img4if->i4if_v1.nonce_domain_roll_nonce(__VA_ARGS__))
#endif

/*!
 * @function img4_nonce_domain_preroll_nonce
 * Generates a new nonce seed and returns the resulting hash. The new nonce seed
 * will be in force at the next reboot if and only if the boot manifest hash
 * changes. Otherwise, the current nonce seed value will remain stable (modulo
 * the regeneration policy associated with its domain).
 *
 * @param nd
 * The nonce domain.
 *
 * @param n
 * Upon successful return, storage that will contain the current nonce. The
 * provided structure's {@link i4n_version} must be initialized to
 * {@link IMG4_NONCE_VERSION}.
 *
 * @result
 * Upon success, zero is returned. The kernel implementation will never return
 * a non-zero code. The userspace implementation may return one of the following
 * error codes directly:
 *
 *     [EPERM]      The caller lacked the entitlement necessary to roll the
 *                  given nonce
 *     [EROFS]      The boot mode didn't allow committing to non-volatile storage
 *     [ENOTSUP]    Nonce management is not available on the host
 *     [EACCES]     The nonce requested is not accessible in this environment
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_FALL_2021_B
OS_EXPORT OS_WARN_RESULT OS_NONNULL1 OS_NONNULL2
errno_t
img4_nonce_domain_preroll_nonce(const img4_nonce_domain_t *nd, img4_nonce_t *n);
#else
#define img4_nonce_domain_preroll_nonce(...) \
		(img4if->i4if_v14.nonce_domain_preroll_nonce(__VA_ARGS__))
#endif

/*!
 * @function img4_nonce_domain_peek_nonce
 * Copies the current proposed value of a nonce domain.
 *
 * @param nd
 * The nonce domain.
 *
 * @param n
 * Upon successful return, storage that will contain the current proposed
 * nonce. The provided structure's {@link i4n_version} must be initialized to
 * {@link IMG4_NONCE_VERSION}.
 *
 * @result
 * Upon success, zero is returned. The implementation may also return one of the
 * following error codes directly:
 *
 *     [EPERM]      The caller lacked the entitlement necessary to roll the
 *                  given nonce
 *     [ENOENT]     The nonce doesn't have a proposed value
 *     [ENOTSUP]    Nonce management is not available on the host
 *     [EACCES]     The nonce requested is not accessible in this environment
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20220714
OS_EXPORT OS_WARN_RESULT OS_NONNULL1 OS_NONNULL2
errno_t
img4_nonce_domain_peek_nonce(const img4_nonce_domain_t *nd, img4_nonce_t *n);
#else
#define img4_nonce_domain_peek_nonce(...) \
		(img4if->i4if_v19.nonce_domain_peek_nonce(__VA_ARGS__))
#endif

/*!
 * @function img4_nonce_domain_get_from_handle
 * Obtains the nonce domain for the given integer handle.
 *
 * @param handle
 * The nonce domain handle.
 *
 * @result
 * The nonce domain associated with the provided handle. If no domain is
 * associated with the handle, NULL is returned.
 */
#if !XNU_KERNEL_PRIVATE
IMG4_API_AVAILABLE_20221202
OS_EXPORT OS_WARN_RESULT
const img4_nonce_domain_t *_Nullable
img4_nonce_domain_get_from_handle(uint32_t handle);
#else
#define img4_nonce_domain_get_from_handle(...) \
		(img4if->i4if_v20.nonce_domain_get_from_handle(__VA_ARGS__))
#endif

OS_ASSUME_PTR_ABI_SINGLE_END
OS_ASSUME_NONNULL_END
__END_DECLS

#endif // __IMG4_NONCE_H
