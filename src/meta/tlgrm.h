#ifndef _INCLUDE_NXS_CHAT_SRV_M_TLGRM_H
#define _INCLUDE_NXS_CHAT_SRV_M_TLGRM_H

/* See https://core.telegram.org/bots/api#available-types for details */

// clang-format off

typedef enum			nxs_chat_srv_m_tlgrm_chat_type_e		nxs_chat_srv_m_tlgrm_chat_type_t;
typedef enum			nxs_chat_srv_m_tlgrm_reply_markup_type_e	nxs_chat_srv_m_tlgrm_reply_markup_type_t;
typedef enum			nxs_chat_srv_m_tlgrm_parse_mode_e		nxs_chat_srv_m_tlgrm_parse_mode_t;
typedef enum			nxs_chat_srv_m_tlgrm_bttn_callback_type_e	nxs_chat_srv_m_tlgrm_bttn_callback_type_t;

typedef struct			nxs_chat_srv_m_tlgrm_update_s			nxs_chat_srv_m_tlgrm_update_t;
typedef struct			nxs_chat_srv_m_tlgrm_callback_query_s		nxs_chat_srv_m_tlgrm_callback_query_t;
typedef struct			nxs_chat_srv_m_tlgrm_message_s			nxs_chat_srv_m_tlgrm_message_t;
typedef struct			nxs_chat_srv_m_tlgrm_chat_s			nxs_chat_srv_m_tlgrm_chat_t;
typedef struct			nxs_chat_srv_m_tlgrm_user_s			nxs_chat_srv_m_tlgrm_user_t;
typedef struct			nxs_chat_srv_m_tlgrm_inl_keyboard_s		nxs_chat_srv_m_tlgrm_inl_keyboard_t;
typedef struct			nxs_chat_srv_m_tlgrm_inl_keybutton_s		nxs_chat_srv_m_tlgrm_inl_keybutton_t;
typedef struct			nxs_chat_srv_m_tlgrm_force_reply_s		nxs_chat_srv_m_tlgrm_force_reply_t;
typedef struct			nxs_chat_srv_m_tlgrm_bttn_callback_s		nxs_chat_srv_m_tlgrm_bttn_callback_t;

enum nxs_chat_srv_m_tlgrm_chat_type_e
{
	NXS_CHAT_SRV_M_TLGRM_CHAT_TYPE_NONE,
	NXS_CHAT_SRV_M_TLGRM_CHAT_TYPE_PRIVATE,
	NXS_CHAT_SRV_M_TLGRM_CHAT_TYPE_GROUP,
	NXS_CHAT_SRV_M_TLGRM_CHAT_TYPE_SUPERGROUP,
	NXS_CHAT_SRV_M_TLGRM_CHAT_TYPE_CHANNEL
};

enum nxs_chat_srv_m_tlgrm_reply_markup_type_e
{
	NXS_CHAT_SRV_M_TLGRM_REPLY_MARKUP_TYPE_NONE,
	NXS_CHAT_SRV_M_TLGRM_REPLY_MARKUP_TYPE_IKM,			/* InlineKeyboardMarkup */
	NXS_CHAT_SRV_M_TLGRM_REPLY_MARKUP_TYPE_RKM,			/* ReplyKeyboardMarkup */
	NXS_CHAT_SRV_M_TLGRM_REPLY_MARKUP_TYPE_RKR,			/* ReplyKeyboardRemove */
	NXS_CHAT_SRV_M_TLGRM_REPLY_MARKUP_TYPE_FR			/* ForceReply */
};

enum nxs_chat_srv_m_tlgrm_parse_mode_e
{
	NXS_CHAT_SRV_M_TLGRM_PARSE_MODE_TYPE_NONE,
	NXS_CHAT_SRV_M_TLGRM_PARSE_MODE_TYPE_MARKDOWN,
	NXS_CHAT_SRV_M_TLGRM_PARSE_MODE_TYPE_HTML
};

enum nxs_chat_srv_m_tlgrm_bttn_callback_type_e
{
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_NONE,
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_NEW_ISSUE,		/* create new issue */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_TO_ISSUE,		/* add comment to existing issue */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_CREATE_ISSUE,		/* create new issue */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_SELECT_PROJECT,		/* select project */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_SELECTED_PROJECT,	/* selected project */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_SELECT_PRIORITY,	/* select priority */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_SELECTED_PRIORITY,	/* selected priority */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_CHANGE_DESCRIPTION,	/* change issue description */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_SESSION_DESTROY,	/* destroy current session */
	NXS_CHAT_SRV_M_TLGRM_BTTN_CALLBACK_TYPE_BACK,			/* back to previous 'window' */
};

struct nxs_chat_srv_m_tlgrm_force_reply_s
{
	nxs_bool_t				_is_used;

	nxs_bool_t				force_reply;
};

struct nxs_chat_srv_m_tlgrm_inl_keybutton_s
{
	nxs_bool_t				_is_used;

	nxs_string_t				text;
	nxs_string_t				url;			/* Optional */
	nxs_string_t				callback_data;		/* Optional */
};

struct nxs_chat_srv_m_tlgrm_inl_keyboard_s
{
	nxs_bool_t				_is_used;

	nxs_array_t				inline_keyboard;	/* type: array of arrays nxs_chat_srv_m_tlgrm_inl_keybutton_t */
};

struct nxs_chat_srv_m_tlgrm_user_s
{
	nxs_bool_t				_is_used;

	size_t					id;
	nxs_string_t				first_name;
	nxs_string_t				last_name;		/* Optional */
	nxs_string_t				username;		/* Optional */
	nxs_string_t				language_code;		/* Optional */
};

struct nxs_chat_srv_m_tlgrm_chat_s
{
	nxs_bool_t				_is_used;

	size_t					id;
	nxs_string_t				username;		/* Optional */
	nxs_chat_srv_m_tlgrm_chat_type_t	type;
};

struct nxs_chat_srv_m_tlgrm_message_s
{
	nxs_bool_t				_is_used;

	size_t					message_id;
	nxs_chat_srv_m_tlgrm_user_t		from;			/* Optional */
	nxs_chat_srv_m_tlgrm_chat_t		chat;
	nxs_chat_srv_m_tlgrm_message_t		*reply_to_message;	/* Optional */
	nxs_string_t				text;			/* Optional */
};

struct nxs_chat_srv_m_tlgrm_callback_query_s
{
	nxs_bool_t				_is_used;

	nxs_string_t				id;
	nxs_chat_srv_m_tlgrm_user_t		from;
	nxs_chat_srv_m_tlgrm_message_t		message;		/* Optional */
	nxs_string_t				chat_instance;
	nxs_string_t				data;			/* Optional */
};

struct nxs_chat_srv_m_tlgrm_update_s
{
	nxs_bool_t				_is_used;

	size_t					update_id;
	nxs_chat_srv_m_tlgrm_message_t		message;		/* Optional */
	nxs_chat_srv_m_tlgrm_callback_query_t	callback_query;		/* Optional */
};

struct nxs_chat_srv_m_tlgrm_bttn_callback_s
{
	nxs_chat_srv_m_tlgrm_bttn_callback_type_t	type;
	size_t						object_id;
};

#endif /* _INCLUDE_NXS_CHAT_SRV_M_TLGRM_H */
