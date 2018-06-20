/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017-2018, Linaro Limited
 */

#ifndef __SKS_PROCESSING_H__
#define __SKS_PROCESSING_H__

#include <tee_internal_api.h>

struct pkcs11_session;
struct sks_object;

/*
 * Entry points frpom SKS TA invocation commands
 */

uint32_t entry_import_object(uintptr_t teesess, TEE_Param *ctrl,
			     TEE_Param *in, TEE_Param *out);

uint32_t entry_cipher_init(uintptr_t teesess, TEE_Param *ctrl,
			   TEE_Param *in, TEE_Param *out, int enc);

uint32_t entry_cipher_update(uintptr_t teesess, TEE_Param *ctrl,
			     TEE_Param *in, TEE_Param *out, int enc);

uint32_t entry_cipher_final(uintptr_t teesess, TEE_Param *ctrl,
			    TEE_Param *in, TEE_Param *out, int enc);

uint32_t entry_generate_object(uintptr_t teesess,
			       TEE_Param *ctrl, TEE_Param *in, TEE_Param *out);

uint32_t entry_signverify_init(uintptr_t teesess, TEE_Param *ctrl,
				TEE_Param *in, TEE_Param *out, int sign);

uint32_t entry_signverify_update(uintptr_t teesess, TEE_Param *ctrl,
				 TEE_Param *in, TEE_Param *out, int sign);

uint32_t entry_signverify_final(uintptr_t teesess, TEE_Param *ctrl,
				TEE_Param *in, TEE_Param *out, int sign);

/*
 * Crypto algorithm specific
 */
void tee_release_ctr_operation(struct pkcs11_session *session);
uint32_t tee_init_ctr_operation(struct pkcs11_session *session,
				    void *proc_params, size_t params_size);

uint32_t tee_ae_decrypt_update(struct pkcs11_session *session,
			       void *in, size_t in_size);

uint32_t tee_ae_decrypt_final(struct pkcs11_session *session,
			      void *out, uint32_t *out_size);

uint32_t tee_ae_encrypt_final(struct pkcs11_session *session,
			      void *out, uint32_t *out_size);

void tee_release_ccm_operation(struct pkcs11_session *session);
uint32_t tee_init_ccm_operation(struct pkcs11_session *session,
				    void *proc_params, size_t params_size);

void tee_release_gcm_operation(struct pkcs11_session *session);
uint32_t tee_init_gcm_operation(struct pkcs11_session *session,
				    void *proc_params, size_t params_size);

#endif /*__SKS_PROCESSING_H__*/
