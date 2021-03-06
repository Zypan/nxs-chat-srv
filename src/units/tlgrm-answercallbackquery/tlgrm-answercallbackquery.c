#ifndef _INCLUDE_NXS_CHAT_SRV_U_TLGRM_ANSWERCALLBACKQUERY_C
#define _INCLUDE_NXS_CHAT_SRV_U_TLGRM_ANSWERCALLBACKQUERY_C
#endif

// clang-format off

#include <nxs-core/nxs-core.h>

/* Project core include */
#include <nxs-chat-srv-core.h>
#include <nxs-chat-srv-meta.h>
#include <nxs-chat-srv-collections.h>
#include <nxs-chat-srv-dal.h>

#include <units/tlgrm-answercallbackquery/tlgrm-answercallbackquery-typedefs.h>
#include <units/tlgrm-answercallbackquery/tlgrm-answercallbackquery.h>
#include <units/tlgrm-answercallbackquery/tlgrm-answercallbackquery-subunits.h>

/* Definitions */



/* Project globals */
extern		nxs_process_t				process;
extern		nxs_chat_srv_cfg_t		nxs_chat_srv_cfg;

/* Module typedefs */



/* Module declarations */

struct nxs_chat_srv_u_tlgrm_answercallbackquery_s
{

};

/* Module internal (static) functions prototypes */

// clang-format on

// clang-format off

/* Module initializations */



/* Module global functions */

// clang-format on

nxs_chat_srv_err_t nxs_chat_srv_u_tlgrm_answercallbackquery_push(nxs_string_t *callback_query_id, nxs_string_t *text, size_t cache_time)
{
	nxs_chat_srv_err_t rc;
	nxs_string_t       message, text_serialized;

	if(callback_query_id == NULL) {

		return NXS_CHAT_SRV_E_PTR;
	}

	rc = NXS_CHAT_SRV_E_OK;

	nxs_string_init(&message);
	nxs_string_init(&text_serialized);

	if(text != NULL) {

		nxs_string_escape(&text_serialized, text, NXS_STRING_ESCAPE_TYPE_JSON);

		nxs_string_printf(&message,
		                  "{\"callback_query_id\":\"%r\",\"text\":\"%r\",\"show_alert\":true,\"cache_time\":%zu}",
		                  callback_query_id,
		                  &text_serialized,
		                  cache_time);
	}
	else {

		nxs_string_printf(&message, "{\"callback_query_id\":\"%r\",\"cache_time\":%zu}", callback_query_id, cache_time);
	}

	if(nxs_chat_srv_d_tlgrm_request(NXS_CHAT_SRV_TLGRM_REQUEST_TYPE_ANSWER_CALLBACK_QUERY, &message, NULL, NULL) != NXS_CHAT_SRV_E_OK) {

		nxs_log_write_error(
		        &process, "[%s]: can't send tlgrm answer callback query (message: \"%r\")", nxs_proc_get_name(&process), &message);

		nxs_error(rc, NXS_CHAT_SRV_E_ERR, error);
	}

error:

	nxs_string_free(&message);
	nxs_string_free(&text_serialized);

	return rc;
}

/* Module internal (static) functions */
