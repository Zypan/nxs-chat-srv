#ifndef _INCLUDE_NXS_CHAT_SRV_D_RDMN_ISSUES_H
#define _INCLUDE_NXS_CHAT_SRV_D_RDMN_ISSUES_H

// clang-format off

/* Structs declarations */



/* Prototypes */

nxs_chat_srv_err_t			nxs_chat_srv_d_rdmn_issues_add_comment		(size_t issue_id, nxs_string_t *note, nxs_bool_t private_notes, size_t status_id, nxs_array_t *custom_fields, nxs_string_t *user_api_key, nxs_http_code_t *http_code, nxs_buf_t *out_buf);
nxs_chat_srv_err_t			nxs_chat_srv_d_rdmn_issues_create		(size_t project_id, size_t priority_id, nxs_string_t *subject, nxs_string_t *description, nxs_bool_t is_private, nxs_string_t *user_api_key, nxs_http_code_t *http_code, nxs_buf_t *out_buf);
nxs_chat_srv_err_t			nxs_chat_srv_d_rdmn_issues_get_query		(size_t issue_query_id, nxs_string_t *user_api_key, size_t offset, size_t limit, nxs_http_code_t *http_code, nxs_buf_t *out_buf);
nxs_chat_srv_err_t			nxs_chat_srv_d_rdmn_issues_get_issue		(size_t issue_id, nxs_string_t *user_api_key, nxs_http_code_t *http_code, nxs_buf_t *out_buf);

#endif /* _INCLUDE_NXS_CHAT_SRV_D_RDMN_ISSUES_H */
