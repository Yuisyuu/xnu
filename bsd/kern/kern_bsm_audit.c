 * Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * NOTICE: This file was modified by SPARTA, Inc. in 2005 to introduce
 * support for mandatory and extensible security protections.  This notice
 * is included in support of clause 2.2 (b) of the Apple Public License,
 * Version 2.0.
#include <sys/vnode_internal.h>

#include <sys/ipc.h>
#include <bsm/audit.h>
#include <bsm/audit_record.h>
#include <bsm/audit_kernel.h>
#include <bsm/audit_kevents.h>
#include <bsm/audit_klib.h>

#include <kern/kalloc.h>

#if CONFIG_MACF
#include <security/mac_framework.h>
#endif
static lck_grp_t	*bsm_audit_grp;
static lck_attr_t	*bsm_audit_attr;
static lck_grp_attr_t	*bsm_audit_grp_attr;
static lck_mtx_t	*bsm_audit_mutex;

static void audit_sys_auditon(struct audit_record *ar, struct au_record *rec);
	bsm_audit_grp_attr = lck_grp_attr_alloc_init();
	bsm_audit_grp = lck_grp_alloc_init("BSM Audit", bsm_audit_grp_attr);
	bsm_audit_attr = lck_attr_alloc_init();
	bsm_audit_mutex = lck_mtx_alloc_init(bsm_audit_grp, bsm_audit_attr);
	au_evclassmap_init();
	lck_mtx_lock(bsm_audit_mutex);
	lck_mtx_unlock(bsm_audit_mutex);
		lck_mtx_lock(bsm_audit_mutex);
			lck_mtx_unlock(bsm_audit_mutex);
		lck_mtx_unlock(bsm_audit_mutex);
		rec = (struct au_record *)kalloc(sizeof(*rec));
		rec->data = (u_char *)kalloc(MAX_AUDIT_RECORD_SIZE * sizeof(u_char));
			kfree(rec, sizeof(*rec));
		lck_mtx_lock(bsm_audit_mutex);
		lck_mtx_unlock(bsm_audit_mutex);
int
kau_close(struct au_record *rec, struct timespec *ctime, short event)

	return(retval);
		kfree(tok, sizeof(*tok) + tok->len);
	lck_mtx_lock(bsm_audit_mutex);
	lck_mtx_unlock(bsm_audit_mutex);
 * to reduce the generated code size.
#if CONFIG_MACF
#define MAC_VNODE1_LABEL_TOKEN						\
	do {								\
		if (ar->ar_vnode1_mac_labels != NULL) {			\
			tok = au_to_text(ar->ar_vnode1_mac_labels);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)

#define MAC_VNODE2_LABEL_TOKEN						\
	do {								\
		if (ar->ar_vnode2_mac_labels != NULL) {			\
			tok = au_to_text(ar->ar_vnode2_mac_labels);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)
#else
#define MAC_VNODE1_LABEL_TOKEN
#define MAC_VNODE2_LABEL_TOKEN
#endif
#define UPATH1_KPATH1_VNODE1_TOKENS	\
		if (ar->ar_valid_arg & ARG_UPATH1) {  		\
			tok = au_to_path(ar->ar_arg_upath1);	\
			kau_write(rec, tok);			\
		}						\
			tok = kau_to_attr32(&ar->ar_arg_vnode1);\
			MAC_VNODE1_LABEL_TOKEN;			\
#define KPATH1_VNODE1_TOKENS	\
			tok = kau_to_attr32(&ar->ar_arg_vnode1);\
			MAC_VNODE1_LABEL_TOKEN;			\
			tok = kau_to_attr32(&ar->ar_arg_vnode2);\
			MAC_VNODE2_LABEL_TOKEN;			\
				tok = kau_to_attr32(&ar->ar_arg_vnode1);\
				MAC_VNODE1_LABEL_TOKEN;		\
#define PROCESS_PID_TOKENS(argn)	\
	do { \
		if ((ar->ar_arg_pid > 0) /* Kill a single process */	\
		    && (ar->ar_valid_arg & ARG_PROCESS)) {		\
			tok = au_to_process(ar->ar_arg_auid, ar->ar_arg_euid, \
				ar->ar_arg_egid, ar->ar_arg_ruid,	\
				ar->ar_arg_rgid, ar->ar_arg_pid,	\
				ar->ar_arg_asid, &ar->ar_arg_termid);	\
			kau_write(rec, tok);				\
		} else {						\
			tok = au_to_arg32(argn, "process", ar->ar_arg_pid);\
			kau_write(rec, tok);				\
		}							\
	} while (0)							\

#define PROCESS_MAC_TOKENS						\
	do {								\
		if (ar->ar_valid_arg & ARG_MAC_STRING) {		\
			tok = au_to_text(ar->ar_arg_mac_string);	\
			kau_write(rec, tok);				\
		}							\
	} while (0)							\

/*
 * Implement auditing for the auditon() system call. The audit tokens
 * that are generated depend on the command that was sent into the 
 * auditon() system call.
 *
 */
static void
audit_sys_auditon(struct audit_record *ar, struct au_record *rec)
{
	struct au_token *tok;

	switch (ar->ar_arg_cmd) {
	case A_SETPOLICY:
		if (sizeof(ar->ar_arg_auditon.au_flags) > 4)
			tok = au_to_arg64(1, "policy", 
				ar->ar_arg_auditon.au_flags);
		else
			tok = au_to_arg32(1, "policy", 
				ar->ar_arg_auditon.au_flags);
		kau_write(rec, tok);
		break;
	case A_SETKMASK:
		tok = au_to_arg32(2, "setkmask:as_success", 
			ar->ar_arg_auditon.au_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setkmask:as_failure", 
			ar->ar_arg_auditon.au_mask.am_failure);
		kau_write(rec, tok);
		break;
	case A_SETQCTRL:
		tok = au_to_arg32(3, "setqctrl:aq_hiwater", 
			ar->ar_arg_auditon.au_qctrl.aq_hiwater);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setqctrl:aq_lowater", 
			ar->ar_arg_auditon.au_qctrl.aq_lowater);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setqctrl:aq_bufsz", 
			ar->ar_arg_auditon.au_qctrl.aq_bufsz);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setqctrl:aq_delay", 
			ar->ar_arg_auditon.au_qctrl.aq_delay);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setqctrl:aq_minfree", 
			ar->ar_arg_auditon.au_qctrl.aq_minfree);
		kau_write(rec, tok);
		break;
	case A_SETUMASK:
		tok = au_to_arg32(3, "setumask:as_success", 
			ar->ar_arg_auditon.au_auinfo.ai_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setumask:as_failure", 
			ar->ar_arg_auditon.au_auinfo.ai_mask.am_failure);
		kau_write(rec, tok);
		break;
	case A_SETSMASK:
		tok = au_to_arg32(3, "setsmask:as_success", 
			ar->ar_arg_auditon.au_auinfo.ai_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setsmask:as_failure", 
			ar->ar_arg_auditon.au_auinfo.ai_mask.am_failure);
		kau_write(rec, tok);
		break;
	case A_SETCOND:
		if (sizeof(ar->ar_arg_auditon.au_cond) > 4)
			tok = au_to_arg64(3, "setcond", 
				ar->ar_arg_auditon.au_cond);
		else
			tok = au_to_arg32(3, "setcond", 
				ar->ar_arg_auditon.au_cond);
		kau_write(rec, tok);
		break;
	case A_SETCLASS:
		tok = au_to_arg32(2, "setclass:ec_event",
			ar->ar_arg_auditon.au_evclass.ec_number);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "setclass:ec_class",
			ar->ar_arg_auditon.au_evclass.ec_class);
		kau_write(rec, tok);
		break;
	case A_SETPMASK:
		tok = au_to_arg32(2, "setpmask:as_success", 
			ar->ar_arg_auditon.au_aupinfo.ap_mask.am_success);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "setpmask:as_failure", 
			ar->ar_arg_auditon.au_aupinfo.ap_mask.am_failure);
		kau_write(rec, tok);
		break;
	case A_SETFSIZE:
		tok = au_to_arg32(2, "setfsize:filesize", 
			ar->ar_arg_auditon.au_fstat.af_filesz);
		kau_write(rec, tok);
		break;
	default:
		break;
	}
}

	struct au_token *tok = NULL, *subj_tok;
		tok = au_to_arg32(1,"domain", ar->ar_arg_sockinfo.so_domain);
		tok = au_to_arg32(2,"type", ar->ar_arg_sockinfo.so_type);
		tok = au_to_arg32(3,"protocol",ar->ar_arg_sockinfo.so_protocol);
	case AUE_ACCT:
		if (ar->ar_valid_arg & (ARG_KPATH1 | ARG_UPATH1)) {
			UPATH1_KPATH1_VNODE1_TOKENS;
		} else {
			tok = au_to_arg32(1, "accounting off", 0);
			kau_write(rec, tok);
		}
		break;

		break;

	case AUE_SETAUDIT:
		if (ar->ar_valid_arg & ARG_AUID) {
			tok = au_to_arg32(1, "setaudit:auid", ar->ar_arg_auid);
			kau_write(rec, tok);
			tok = au_to_arg32(1, "setaudit:port", 
					ar->ar_arg_termid.port);
			kau_write(rec, tok);
			tok = au_to_arg32(1, "setaudit:machine", 
					ar->ar_arg_termid.machine);
			kau_write(rec, tok);
			tok = au_to_arg32(1, "setaudit:as_success", 
					ar->ar_arg_amask.am_success);
			kau_write(rec, tok);
			tok = au_to_arg32(1, "setaudit:as_failure", 
					ar->ar_arg_amask.am_failure);
			kau_write(rec, tok);
			tok = au_to_arg32(1, "setaudit:asid", ar->ar_arg_asid);
			kau_write(rec, tok);
		}
		break;

	case AUE_SETAUDIT_ADDR:
		break;		/* XXX need to add arguments */

	case AUE_AUDITON:
		/* For AUDITON commands without own event, audit the cmd */
		tok = au_to_arg32(1, "cmd", ar->ar_arg_cmd);
		kau_write(rec, tok);
		/* fall thru */

	case AUE_AUDITON_GETCAR:
	case AUE_AUDITON_GETCLASS:
	case AUE_AUDITON_GETCOND:
	case AUE_AUDITON_GETCWD:
	case AUE_AUDITON_GETKMASK:
	case AUE_AUDITON_GETSTAT:
	case AUE_AUDITON_GPOLICY:
	case AUE_AUDITON_GQCTRL:
	case AUE_AUDITON_SETCLASS:
	case AUE_AUDITON_SETCOND:
	case AUE_AUDITON_SETKMASK:
	case AUE_AUDITON_SETSMASK:
	case AUE_AUDITON_SETSTAT:
	case AUE_AUDITON_SETUMASK:
	case AUE_AUDITON_SPOLICY:
	case AUE_AUDITON_SQCTRL:
		if (ar->ar_valid_arg & ARG_AUDITON) {
			audit_sys_auditon(ar, rec);
		}
		break;
	
	case AUE_AUDITCTL:
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_GETAUDIT:
	case AUE_GETAUDIT_ADDR:
	case AUE_MAC_GETFSSTAT:
	case AUE_SETSID:
	case AUE_SETTIMEOFDAY:
		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;
	case AUE_LCHOWN:
		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;

	case AUE_NFSSVC:
		tok = au_to_arg32(1, "request", ar->ar_arg_cmd);
		kau_write(rec, tok);
		if (ar->ar_valid_arg & (ARG_KPATH1 | ARG_UPATH1)) {
			UPATH1_KPATH1_VNODE1_TOKENS;
		}
		break;

	case AUE_EXTATTR_GET_FD:
	case AUE_EXTATTR_LIST_FD:
	case AUE_EXTATTR_SET_FD:
	case AUE_EXTATTR_DELETE_FD:
		tok = au_to_arg32(2, "cmd", ar->ar_arg_cmd);
		kau_write(rec, tok);
		if (ar->ar_valid_arg & ARG_VNODE1) {
	case AUE_FORK:
	case AUE_VFORK:
		tok = au_to_arg32(0, "child PID", ar->ar_arg_pid);
		kau_write(rec, tok);
		break;
	
	case AUE_GETLCID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		break;

	case AUE_SETLCID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "lcid", (u_int32_t)ar->ar_arg_value);
		kau_write(rec, tok);
		break;

	case AUE_IOCTL:
		tok = au_to_arg32(2, "cmd", ar->ar_arg_cmd);
		kau_write(rec, tok);
		tok = au_to_arg32(1, "arg", (u_int32_t)ar->ar_arg_addr);
		kau_write(rec, tok);
		if (ar->ar_valid_arg & ARG_VNODE1) {
			FD_KPATH1_VNODE1_TOKENS;
		} else {
			if (ar->ar_valid_arg & ARG_SOCKINFO) {
			    tok = kau_to_socket(&ar->ar_arg_sockinfo); 
			    kau_write(rec, tok);
			} else {
			    tok = au_to_arg32(1, "fd", ar->ar_arg_fd);
			    kau_write(rec, tok);
			}
		}
		break;

	case AUE_KILL:
		tok = au_to_arg32(2, "signal", ar->ar_arg_signum);
		kau_write(rec, tok);
		PROCESS_PID_TOKENS(1);
		break;

		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_MMAP:
	case AUE_MUNMAP:
	case AUE_MPROTECT:
	case AUE_MLOCK:
	case AUE_MUNLOCK:
	case AUE_MINHERIT:
		tok = au_to_arg32(1, "addr", (u_int32_t)ar->ar_arg_addr); /* LP64todo */
		kau_write(rec, tok);
		tok = au_to_arg32(2, "len", ar->ar_arg_len); /* LP64todo */
		kau_write(rec, tok);
		if (ar->ar_event == AUE_MMAP)
			FD_KPATH1_VNODE1_TOKENS;
		if (ar->ar_event == AUE_MPROTECT) {
			tok = au_to_arg32(3, "protection", ar->ar_arg_value);
			kau_write(rec, tok);
		}
		if (ar->ar_event == AUE_MINHERIT) {
			tok = au_to_arg32(3, "inherit", ar->ar_arg_value);
			kau_write(rec, tok);
		}
#if CONFIG_MACF
	case AUE_MAC_MOUNT:
		PROCESS_MAC_TOKENS;
		/* fall through */
#endif
		if (ar->ar_valid_arg & ARG_TEXT) {
	case AUE_UNMOUNT:
		UPATH1_KPATH1_VNODE1_TOKENS;
		tok = au_to_arg32(3, "mode", ar->ar_arg_mode);
		kau_write(rec, tok);
		/* fall thru */

	case AUE_OPEN:
	case AUE_OPEN_R:
	case AUE_OPEN_RT:
	case AUE_OPEN_RW:
	case AUE_OPEN_RWT:
	case AUE_OPEN_W:
		tok = au_to_arg32(2, "flags", ar->ar_arg_fflags);
		kau_write(rec, tok);
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_PTRACE:
		tok = au_to_arg32(1, "request", ar->ar_arg_cmd);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "addr", (u_int32_t)ar->ar_arg_addr); /* LP64todo */
		kau_write(rec, tok);
		tok = au_to_arg32(4, "data", ar->ar_arg_value);
		kau_write(rec, tok);
		PROCESS_PID_TOKENS(2);
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_REBOOT:
		tok = au_to_arg32(1, "howto", ar->ar_arg_cmd);
		kau_write(rec, tok);
			u_int ctr;

				tok = au_to_arg32(1, "setgroups", ar->ar_arg_groups.gidset[ctr]);

	case AUE_SETLOGIN:
		if (ar->ar_valid_arg & ARG_TEXT) {
			tok = au_to_text(ar->ar_arg_text);
			kau_write(rec, tok);
		}
		break;

	case AUE_SETPRIORITY:
		tok = au_to_arg32(1, "which", ar->ar_arg_cmd);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "who", ar->ar_arg_uid);
		kau_write(rec, tok);
		tok = au_to_arg32(2, "priority", ar->ar_arg_value);
		kau_write(rec, tok);
		break;

	case AUE_SETPRIVEXEC:
		tok = au_to_arg32(1, "flag", ar->ar_arg_value);
		kau_write(rec, tok);
		break;

	/* AUE_SHMAT, AUE_SHMCTL, AUE_SHMDT and AUE_SHMGET are SysV IPC */
		tok = au_to_arg64(2, "shmaddr", ar->ar_arg_svipc_addr);
		tok = au_to_arg64(1, "shmaddr", ar->ar_arg_svipc_addr);
	/* AUE_SHMOPEN, AUE_SHMUNLINK, AUE_SEMOPEN, AUE_SEMCLOSE 
	 * and AUE_SEMUNLINK are Posix IPC */
	case AUE_SHMOPEN:
		tok = au_to_arg32(2, "flags", ar->ar_arg_fflags);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "mode", ar->ar_arg_mode);
		kau_write(rec, tok);
	case AUE_SHMUNLINK:
		if (ar->ar_valid_arg & ARG_TEXT) {
			tok = au_to_text(ar->ar_arg_text);
			kau_write(rec, tok);
		}
		if (ar->ar_valid_arg & ARG_POSIX_IPC_PERM) {
		/* Create an ipc_perm token */
			struct ipc_perm perm;
			perm.uid = ar->ar_arg_pipc_perm.pipc_uid;
			perm.gid = ar->ar_arg_pipc_perm.pipc_gid;
			perm.cuid = ar->ar_arg_pipc_perm.pipc_uid;
			perm.cgid = ar->ar_arg_pipc_perm.pipc_gid;
			perm.mode = ar->ar_arg_pipc_perm.pipc_mode;
			perm._seq = 0;
			perm._key = 0;
			tok = au_to_ipc_perm(&perm);
			kau_write(rec, tok);
		}
		break;

	case AUE_SEMOPEN:
		tok = au_to_arg32(2, "flags", ar->ar_arg_fflags);
		kau_write(rec, tok);
		tok = au_to_arg32(3, "mode", ar->ar_arg_mode);
		kau_write(rec, tok);
		tok = au_to_arg32(4, "value", ar->ar_arg_value);
		kau_write(rec, tok);
		/* fall through */
	case AUE_SEMUNLINK:
		if (ar->ar_valid_arg & ARG_TEXT) {
			tok = au_to_text(ar->ar_arg_text);
			kau_write(rec, tok);
		}
		if (ar->ar_valid_arg & ARG_POSIX_IPC_PERM) {
		/* Create an ipc_perm token */
			struct ipc_perm perm;
			perm.uid = ar->ar_arg_pipc_perm.pipc_uid;
			perm.gid = ar->ar_arg_pipc_perm.pipc_gid;
			perm.cuid = ar->ar_arg_pipc_perm.pipc_uid;
			perm.cgid = ar->ar_arg_pipc_perm.pipc_gid;
			perm.mode = ar->ar_arg_pipc_perm.pipc_mode;
			perm._seq = 0;
			perm._key = 0;
			tok = au_to_ipc_perm(&perm);
			kau_write(rec, tok);
		}
		break;

	case AUE_SEMCLOSE:
		tok = au_to_arg32(1, "sem", ar->ar_arg_fd);
		kau_write(rec, tok);
		break;

		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_SYSCTL:
	case AUE_SYSCTL_NONADMIN:
		if (ar->ar_valid_arg & (ARG_CTLNAME | ARG_LEN)) {
			int ctr;

			for (ctr = 0; ctr < ar->ar_arg_len; ctr++) {
			  tok = au_to_arg32(1, "name", ar->ar_arg_ctlname[ctr]);
			  kau_write(rec, tok);
			}
		}
		if (ar->ar_valid_arg & ARG_VALUE) {
			tok = au_to_arg32(5, "newval", ar->ar_arg_value);
			kau_write(rec, tok);
		}
		if (ar->ar_valid_arg & ARG_TEXT) {
			tok = au_to_text(ar->ar_arg_text);
			kau_write(rec, tok);
		}
	/************************
	 * Mach system calls    *
	 ************************/
	case AUE_INITPROCESS:
		break;

	case AUE_PIDFORTASK:
		tok = au_to_arg32(1, "port", (u_int32_t)ar->ar_arg_mach_port1);
		kau_write(rec, tok);
		if (ar->ar_valid_arg & ARG_PID) {
			tok = au_to_arg32(2, "pid", (u_int32_t)ar->ar_arg_pid);
			kau_write(rec, tok);
		}
		break;

	case AUE_TASKFORPID:
		tok = au_to_arg32(1, "target port", 
			(u_int32_t)ar->ar_arg_mach_port1);
		kau_write(rec, tok);
		if (ar->ar_valid_arg & ARG_MACHPORT2) {
			tok = au_to_arg32(3, "task port", 
				(u_int32_t)ar->ar_arg_mach_port2);
			kau_write(rec, tok);
		}
		PROCESS_PID_TOKENS(2);
		break;

	case AUE_SWAPON:
		tok = au_to_arg32(4, "priority", 
			(u_int32_t)ar->ar_arg_value);
		kau_write(rec, tok);
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_SWAPOFF:
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_MAPFD:
		tok = au_to_arg32(3, "va", (u_int32_t)ar->ar_arg_addr);
		kau_write(rec, tok);
		FD_KPATH1_VNODE1_TOKENS;
		break;

	case AUE_EXTATTR_GET_FILE:
	case AUE_EXTATTR_SET_FILE:
	case AUE_EXTATTR_LIST_FILE:
	case AUE_EXTATTR_DELETE_FILE:
	case AUE_EXTATTR_GET_LINK:
	case AUE_EXTATTR_SET_LINK:
	case AUE_EXTATTR_LIST_LINK:
	case AUE_EXTATTR_DELETE_LINK:
		UPATH1_KPATH1_VNODE1_TOKENS;
		break;

#if CONFIG_MACF
	case AUE_MAC_GET_FILE:
	case AUE_MAC_SET_FILE:
	case AUE_MAC_GET_LINK:
	case AUE_MAC_SET_LINK:
	case AUE_MAC_GET_MOUNT:
		UPATH1_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_FD:
	case AUE_MAC_SET_FD:
		FD_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_SYSCALL:
		PROCESS_MAC_TOKENS;
		tok = au_to_arg32(3, "call", ar->ar_arg_value);
		kau_write(rec, tok);
		break;

	case AUE_MAC_EXECVE:
		UPATH1_KPATH1_VNODE1_TOKENS;
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_PID:
		tok = au_to_arg32(1, "pid", (u_int32_t)ar->ar_arg_pid);
		kau_write(rec, tok);
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_LCID:
		tok = au_to_arg32(1, "lcid", (u_int32_t)ar->ar_arg_value);
		kau_write(rec, tok);
		PROCESS_MAC_TOKENS;
		break;

	case AUE_MAC_GET_PROC:
	case AUE_MAC_SET_PROC:
	case AUE_MAC_GET_LCTX:
	case AUE_MAC_SET_LCTX:
		PROCESS_MAC_TOKENS;
		break;
#endif

#if CONFIG_MACF
	do {
		/* Convert the audit data from the MAC policies */
		struct mac_audit_record *mar;
		
		LIST_FOREACH(mar, ar->ar_mac_records, records) {
			switch (mar->type) {
				case MAC_AUDIT_DATA_TYPE:
					tok = au_to_data(AUP_BINARY, AUR_BYTE,
					    mar->length, mar->data);
					break;
				case MAC_AUDIT_TEXT_TYPE:
					tok = au_to_text((char*) mar->data);
					break;
				default:
					/*
					 * XXX: we can either continue,
					 * skipping this particular entry,
					 * or we can pre-verify the list and
					 * abort before writing any records
					 */
					printf("kaudit_to_bsm(): BSM conversion requested for unknown mac_audit data type %d\n",
					    mar->type);
			}

			kau_write(rec, tok);
		}
	} while (0);
#endif


#if CONFIG_MACF
	if (ar->ar_cred_mac_labels != NULL) {
		tok = au_to_text(ar->ar_cred_mac_labels);
		kau_write(rec, tok);
	}
#endif

bsm_rec_verify(void* rec)
	char c = *(char *)rec;
	if ( (c != AU_HEADER_32_TOKEN) && 
		(c != AU_HEADER_EX_32_TOKEN) && 
		(c != AU_HEADER_64_TOKEN) && 
		(c != AU_HEADER_EX_64_TOKEN) ) {