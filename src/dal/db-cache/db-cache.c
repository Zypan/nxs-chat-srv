#ifndef _INCLUDE_NXS_CHAT_SRV_D_DB_CACHE_C
#define _INCLUDE_NXS_CHAT_SRV_D_DB_CACHE_C
#endif

// clang-format off

#include <nxs-core/nxs-core.h>

/* Project core include */
#include <nxs-chat-srv-core.h>
#include <nxs-chat-srv-meta.h>
#include <nxs-chat-srv-collections.h>

#include <dal/db-cache/db-cache-typedefs.h>
#include <dal/db-cache/db-cache.h>
#include <dal/db-cache/db-cache-subdals.h>

/* Definitions */



/* Project globals */
extern		nxs_process_t			process;
extern		nxs_chat_srv_cfg_t		nxs_chat_srv_cfg;

/* Module typedefs */



/* Module declarations */

typedef struct
{
	nxs_chat_srv_d_db_cache_type_t		type;
	char					*name;
} nxs_chat_srv_d_db_cache_name_t;

struct nxs_chat_srv_d_db_cache_s
{
	nxs_string_t				redis_prefix;
	nxs_chat_srv_m_redis_ctx_t		redis_ctx;
};

/* Module internal (static) functions prototypes */

// clang-format on

static char *nxs_chat_srv_d_db_cache_get_name(nxs_chat_srv_d_db_cache_type_t cache_type);

// clang-format off

/* Module initializations */

nxs_chat_srv_d_db_cache_name_t cache_names[] =
{
	{NXS_CHAT_SRV_D_DB_CACHE_TYPE_PROJECTS,			"projects"},
	{NXS_CHAT_SRV_D_DB_CACHE_TYPE_USERS,			"users"},
	{NXS_CHAT_SRV_D_DB_CACHE_TYPE_ISSUE_PRIORITIES,		"issue_priorities"},

	{NXS_CHAT_SRV_D_DB_CACHE_TYPE_NONE,			""}
};

/* Module global functions */

// clang-format on

nxs_chat_srv_d_db_cache_t *nxs_chat_srv_d_db_cache_init(void)
{
	nxs_chat_srv_d_db_cache_t *d_ctx;

	d_ctx = (nxs_chat_srv_d_db_cache_t *)nxs_malloc(NULL, sizeof(nxs_chat_srv_d_db_cache_t));

	nxs_string_init(&d_ctx->redis_prefix);

	nxs_chat_srv_c_redis_get_prefix(&d_ctx->redis_prefix, "nxs-chat-srv:%r:cache");

	/* Connect to Redis */

	if(nxs_chat_srv_c_redis_init(&d_ctx->redis_ctx, &nxs_chat_srv_cfg.redis.nodes, nxs_chat_srv_cfg.redis.is_cluster) !=
	   NXS_CHAT_SRV_E_OK) {

		return nxs_chat_srv_d_db_cache_free(d_ctx);
	}

	return d_ctx;
}

nxs_chat_srv_d_db_cache_t *nxs_chat_srv_d_db_cache_free(nxs_chat_srv_d_db_cache_t *d_ctx)
{

	if(d_ctx == NULL) {

		return NULL;
	}

	nxs_string_free(&d_ctx->redis_prefix);

	nxs_chat_srv_c_redis_free(&d_ctx->redis_ctx);

	return (nxs_chat_srv_d_db_cache_t *)nxs_free(d_ctx);
}

nxs_chat_srv_err_t
        nxs_chat_srv_d_db_cache_get(nxs_chat_srv_d_db_cache_t *d_ctx, nxs_chat_srv_d_db_cache_type_t cache_type, nxs_string_t *value)
{
	redisReply *       redis_reply;
	nxs_chat_srv_err_t rc;
	char *             cache_name;

	if(d_ctx == NULL || value == NULL) {

		return NXS_CHAT_SRV_E_PTR;
	}

	if((cache_name = nxs_chat_srv_d_db_cache_get_name(cache_type)) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache get error: unknown cache type (cache type id: %d)",
		                    nxs_proc_get_name(&process),
		                    cache_type);

		return NXS_CHAT_SRV_E_TYPE;
	}

	rc = NXS_CHAT_SRV_E_OK;

	if((redis_reply = nxs_chat_srv_c_redis_command(
	            &d_ctx->redis_ctx, "HGET %s %s", nxs_string_str(&d_ctx->redis_prefix), cache_name)) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache get error, Redis reply error: %s (cache type: %s)",
		                    nxs_proc_get_name(&process),
		                    nxs_chat_srv_c_redis_get_error(&d_ctx->redis_ctx),
		                    cache_name);

		nxs_error(rc, NXS_CHAT_SRV_E_ERR, error);
	}

	switch(redis_reply->type) {

		case REDIS_REPLY_STRING:

			nxs_log_write_debug(
			        &process, "[%s]: db cache get: success (cache type: %s)", nxs_proc_get_name(&process), cache_name);

			nxs_string_char_ncpy(value, 0, (u_char *)redis_reply->str, (size_t)redis_reply->len);

			break;

		case REDIS_REPLY_NIL:

			/* value not found by specified key */

			nxs_log_write_debug(&process,
			                    "[%s]: db cache get: value does not exist (cache type: %s)",
			                    nxs_proc_get_name(&process),
			                    cache_name);

			nxs_error(rc, NXS_CHAT_SRV_E_EXIST, error);

		default:

			nxs_log_write_error(&process,
			                    "[%s]: db cache get error: unexpected Redis reply type (cache type: %s, expected type: %d, "
			                    "received type: %d)",
			                    nxs_proc_get_name(&process),
			                    cache_name,
			                    REDIS_REPLY_STRING,
			                    redis_reply->type);

			nxs_error(rc, NXS_CHAT_SRV_E_WARN, error);
	}

error:

	if(redis_reply != NULL) {

		freeReplyObject(redis_reply);
	}

	if(rc == NXS_CHAT_SRV_E_ERR) {

		nxs_chat_srv_c_redis_free(&d_ctx->redis_ctx);
	}

	return rc;
}

nxs_chat_srv_err_t
        nxs_chat_srv_d_db_cache_put(nxs_chat_srv_d_db_cache_t *d_ctx, nxs_chat_srv_d_db_cache_type_t cache_type, nxs_string_t *value)
{
	redisReply *       redis_reply;
	nxs_chat_srv_err_t rc;
	char *             cache_name;

	if(d_ctx == NULL || value == NULL) {

		return NXS_CHAT_SRV_E_PTR;
	}

	if((cache_name = nxs_chat_srv_d_db_cache_get_name(cache_type)) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache put error: unknown cache type (cache type id: %d)",
		                    nxs_proc_get_name(&process),
		                    cache_type);

		return NXS_CHAT_SRV_E_TYPE;
	}

	rc = NXS_CHAT_SRV_E_OK;

	if((redis_reply = nxs_chat_srv_c_redis_command(
	            &d_ctx->redis_ctx, "HSET %s %s %s", nxs_string_str(&d_ctx->redis_prefix), cache_name, nxs_string_str(value))) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache put error, Redis reply error: %s (cache type: %s)",
		                    nxs_proc_get_name(&process),
		                    nxs_chat_srv_c_redis_get_error(&d_ctx->redis_ctx),
		                    cache_name);

		nxs_error(rc, NXS_CHAT_SRV_E_ERR, error);
	}

	nxs_log_write_debug(&process, "[%s]: db cache put: success (cache type: %s)", nxs_proc_get_name(&process), cache_name);

error:

	if(redis_reply != NULL) {

		freeReplyObject(redis_reply);
	}

	if(rc == NXS_CHAT_SRV_E_ERR) {

		nxs_chat_srv_c_redis_free(&d_ctx->redis_ctx);
	}

	return rc;
}

nxs_chat_srv_err_t nxs_chat_srv_d_db_cache_del(nxs_chat_srv_d_db_cache_t *d_ctx, nxs_chat_srv_d_db_cache_type_t cache_type)
{
	redisReply *       redis_reply;
	nxs_chat_srv_err_t rc;
	char *             cache_name;

	if(d_ctx == NULL) {

		return NXS_CHAT_SRV_E_PTR;
	}

	if((cache_name = nxs_chat_srv_d_db_cache_get_name(cache_type)) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache del error: unknown cache type (cache type id: %d)",
		                    nxs_proc_get_name(&process),
		                    cache_type);

		return NXS_CHAT_SRV_E_TYPE;
	}

	rc = NXS_CHAT_SRV_E_OK;

	if((redis_reply = nxs_chat_srv_c_redis_command(
	            &d_ctx->redis_ctx, "HDEL %s %s", nxs_string_str(&d_ctx->redis_prefix), cache_name)) == NULL) {

		nxs_log_write_error(&process,
		                    "[%s]: db cache del error, Redis reply error: %s (cache type: %s)",
		                    nxs_proc_get_name(&process),
		                    nxs_chat_srv_c_redis_get_error(&d_ctx->redis_ctx),
		                    cache_name);

		nxs_error(rc, NXS_CHAT_SRV_E_ERR, error);
	}

	nxs_log_write_debug(&process, "[%s]: db cache del: success (cache type: %s)", nxs_proc_get_name(&process), cache_name);

error:

	if(redis_reply != NULL) {

		freeReplyObject(redis_reply);
	}

	if(rc == NXS_CHAT_SRV_E_ERR) {

		nxs_chat_srv_c_redis_free(&d_ctx->redis_ctx);
	}

	return rc;
}

/* Module internal (static) functions */

static char *nxs_chat_srv_d_db_cache_get_name(nxs_chat_srv_d_db_cache_type_t cache_type)
{
	size_t i;

	for(i = 0; cache_names[i].type != NXS_CHAT_SRV_D_DB_CACHE_TYPE_NONE; i++) {

		if(cache_names[i].type == cache_type) {

			return cache_names[i].name;
		}
	}

	return NULL;
}
