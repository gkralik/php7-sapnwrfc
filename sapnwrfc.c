/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/spl/spl_exceptions.h"
#include "Zend/zend_exceptions.h"

#include "php_sapnwrfc.h"
#include "string_helper.h"
#include "rfc_parameters.h"
#include "exceptions.h"

#include "sapnwrfc.h"

// class entries
zend_class_entry *sapnwrfc_connection_ce;
zend_class_entry *sapnwrfc_function_ce;
extern zend_class_entry *sapnwrfc_exception_ce;
extern zend_class_entry *sapnwrfc_connection_exception_ce;
extern zend_class_entry *sapnwrfc_function_exception_ce;

// object handlers
zend_object_handlers sapnwrfc_connection_object_handlers;
zend_object_handlers sapnwrfc_function_object_handlers;

// connection object
typedef struct _sapnwrfc_connection_object {
    RFC_CONNECTION_HANDLE rfc_handle;
    RFC_CONNECTION_PARAMETER *rfc_login_params;
    int rfc_login_params_len;
    // used as the repository ID when clearing the cache
    zend_string *system_id;
    unsigned int use_function_desc_cache;
    zend_object zobj;
} sapnwrfc_connection_object;

// function object
typedef struct _sapnwrfc_function_object {
    RFC_CONNECTION_HANDLE rfc_handle;
    RFC_FUNCTION_DESC_HANDLE function_desc_handle;
    unsigned int parameter_count;
    HashTable *parameter_status;
    zend_string *name;
    zend_object zobj;
} sapnwrfc_function_object;

// helpers for accessing the internal objects
static inline sapnwrfc_connection_object *sapnwrfc_connection_object_fetch(zend_object *obj)
{
    return (sapnwrfc_connection_object *)((char *)obj - XtOffsetOf(sapnwrfc_connection_object, zobj));
}
#define SAPNWRFC_CONNECTION_OBJ_P(zv) SAPNWRFC_CONNECTION_OBJ(Z_OBJ_P(zv))
#define SAPNWRFC_CONNECTION_OBJ(zo) sapnwrfc_connection_object_fetch(zo)

static inline sapnwrfc_function_object *sapnwrfc_function_object_fetch(zend_object *obj)
{
    return (sapnwrfc_function_object *)((char *)obj - XtOffsetOf(sapnwrfc_function_object, zobj));
}
#define SAPNWRFC_FUNCTION_OBJ_P(zv) SAPNWRFC_FUNCTION_OBJ(Z_OBJ_P(zv))
#define SAPNWRFC_FUNCTION_OBJ(zo) sapnwrfc_function_object_fetch(zo)

// forward declaration of helper methods
unsigned int rfc_clear_function_desc_cache(zend_string *function_name, zend_string *repository_id);

// forward declaration of class methods
PHP_METHOD(Connection, __construct);
PHP_METHOD(Connection, getAttributes);
PHP_METHOD(Connection, ping);
PHP_METHOD(Connection, getFunction);
PHP_METHOD(Connection, getSSOTicket);
PHP_METHOD(Connection, close);
PHP_METHOD(Connection, setIniPath);
PHP_METHOD(Connection, reloadIniFile);
PHP_METHOD(Connection, setTraceDir);
PHP_METHOD(Connection, setTraceLevel);
PHP_METHOD(Connection, version);
PHP_METHOD(Connection, rfcVersion);

PHP_METHOD(RemoteFunction, invoke);
PHP_METHOD(RemoteFunction, setParameterActive);
PHP_METHOD(RemoteFunction, isParameterActive);
PHP_METHOD(RemoteFunction, getFunctionDescription);
PHP_METHOD(RemoteFunction, getName);


ZEND_BEGIN_ARG_INFO_EX(arginfo_Connection___construct, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, parameters, 0)
    ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_getAttributes, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_ping, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_Connection_getFunction, 0, 1, SAPNWRFC\\RemoteFunction, 0)
    ZEND_ARG_TYPE_INFO(0, functionName, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, invalidateCache, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_getSSOTicket, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_close, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Connection_setIniPath, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_reloadIniFile, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Connection_setTraceDir, 0, 1, _IS_BOOL, 1)
    ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Connection_setTraceLevel, 0, 1, _IS_BOOL, 1)
    ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_version, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_rfcVersion, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_invoke, 0, 0, IS_ARRAY, 0)
    ZEND_ARG_ARRAY_INFO(0, parameters, 0)
    ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_setParameterActive, 0, 2, IS_VOID, 0)
    ZEND_ARG_TYPE_INFO(0, parameterName, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, isActive, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_isParameterActive, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, parameterName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_getFunctionDescription, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_getName, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_clearFunctionDescCache, 0, 1, _IS_BOOL, 0)
    ZEND_ARG_TYPE_INFO(0, functionName, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, repositoryId, IS_STRING, 1)
ZEND_END_ARG_INFO()


// class method tables
static zend_function_entry sapnwrfc_connection_class_functions[] = {
    PHP_ME(Connection, __construct, arginfo_Connection___construct, ZEND_ACC_PUBLIC)
    PHP_ME(Connection, getAttributes, arginfo_Connection_getAttributes, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, ping, arginfo_Connection_ping, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, getFunction, arginfo_Connection_getFunction, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, getSSOTicket, arginfo_Connection_getSSOTicket, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, close, arginfo_Connection_close, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, setIniPath, arginfo_Connection_setIniPath, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, reloadIniFile, arginfo_Connection_reloadIniFile, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, setTraceDir, arginfo_Connection_setTraceDir, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, setTraceLevel, arginfo_Connection_setTraceLevel, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, version, arginfo_Connection_version, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, rfcVersion, arginfo_Connection_rfcVersion, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_FE_END
};

static zend_function_entry sapnwrfc_function_class_functions[] = {
    PHP_ME(RemoteFunction, invoke, arginfo_RemoteFunction_invoke, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(RemoteFunction, setParameterActive, arginfo_RemoteFunction_setParameterActive, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(RemoteFunction, isParameterActive, arginfo_RemoteFunction_isParameterActive, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(RemoteFunction, getFunctionDescription, arginfo_RemoteFunction_getFunctionDescription, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(RemoteFunction, getName, arginfo_RemoteFunction_getName, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_FE_END
};

// connection object handlers
static zend_object *sapnwrfc_connection_object_create(zend_class_entry *ce)
{
    sapnwrfc_connection_object *intern;

    intern = ecalloc(1, sizeof(sapnwrfc_connection_object) + zend_object_properties_size(ce));
    zend_object_std_init(&intern->zobj, ce);
    object_properties_init(&intern->zobj, ce);
    intern->zobj.handlers = &sapnwrfc_connection_object_handlers;

    return &intern->zobj;
}

static void sapnwrfc_connection_object_free(zend_object *object)
{
    RFC_ERROR_INFO error_info;
    sapnwrfc_connection_object *intern;
    int i;

    intern = SAPNWRFC_CONNECTION_OBJ(object);

    /* free the RFC handle */
    if(intern->rfc_handle) {
        RfcCloseConnection(intern->rfc_handle, &error_info);
        intern->rfc_handle = NULL;
    }

    intern->rfc_handle = NULL;

    // free login parameters
    if(intern->rfc_login_params) {
        for (i = 0; i < intern->rfc_login_params_len; i++) {
            free((char *)intern->rfc_login_params[i].name);
            free((char *)intern->rfc_login_params[i].value);
        }
        efree(intern->rfc_login_params);
    }

    // free the system_id
    if (intern->system_id) {
        zend_string_release(intern->system_id);
    }

    /* call Zend's free handler, which will free the object properties */
    zend_object_std_dtor(&intern->zobj);
}

// function object handlers
static zend_object *sapnwrfc_function_object_create(zend_class_entry *ce)
{
    sapnwrfc_function_object *intern;

    intern = ecalloc(1, sizeof(sapnwrfc_function_object) + zend_object_properties_size(ce));
    zend_object_std_init(&intern->zobj, ce);
    object_properties_init(&intern->zobj, ce);
    intern->zobj.handlers = &sapnwrfc_function_object_handlers;

    ALLOC_HASHTABLE(intern->parameter_status);

    return &intern->zobj;
}

static void sapnwrfc_function_object_free(zend_object *object)
{
    RFC_ERROR_INFO error_info;
    sapnwrfc_function_object *intern;

    intern = SAPNWRFC_FUNCTION_OBJ(object);

    if (intern->function_desc_handle) {
        (void) RfcDestroyFunctionDesc(intern->function_desc_handle, &error_info);
        intern->function_desc_handle = NULL;
    }

    intern->rfc_handle = NULL;
    intern->parameter_count = 0;

    zend_hash_destroy(intern->parameter_status);
    efree(intern->parameter_status);

    zend_string_release(intern->name);

    /* call Zend's free handler, which will free the object properties */
    zend_object_std_dtor(&intern->zobj);
}

static void sapnwrfc_connection_set_options(sapnwrfc_connection_object *intern, HashTable *options)
{
    zend_string *key;
    zval *val;

    // set defaults
    intern->use_function_desc_cache = 1;

    if (!options) {
        return;
    }

    ZEND_HASH_FOREACH_STR_KEY_VAL(options, key, val) {
        if (key) {
            if (strncasecmp(ZSTR_VAL(key), "use_function_desc_cache", strlen("use_function_desc_cache")) == 0) {
                convert_to_boolean(val);

                intern->use_function_desc_cache = zend_is_true(val);
            }
        }
    } ZEND_HASH_FOREACH_END();
}

static void sapnwrfc_open_connection(sapnwrfc_connection_object *intern, HashTable *connection_params)
{
    RFC_ERROR_INFO error_info;
    RFC_ATTRIBUTES attributes;
    RFC_RC rc;
    int i = 0;
    zend_string *key;
    zval *val;

    intern->rfc_login_params_len = zend_hash_num_elements(connection_params);

    intern->rfc_login_params = ecalloc(intern->rfc_login_params_len, sizeof(RFC_CONNECTION_PARAMETER));

    ZEND_HASH_FOREACH_STR_KEY_VAL(connection_params, key, val) {
        if (key) { // is string
            ZVAL_DEREF(val);
            convert_to_string_ex(val);

            // those are free'd in sapnwrfc_connection_object_free
            intern->rfc_login_params[i].name = zend_string_to_sapuc(key);
            intern->rfc_login_params[i].value = zval_to_sapuc(val);

            i++;
        }
    } ZEND_HASH_FOREACH_END();

    intern->rfc_handle = RfcOpenConnection(intern->rfc_login_params, intern->rfc_login_params_len, &error_info);

    if (!intern->rfc_handle) {
        sapnwrfc_throw_connection_exception(error_info, "Could not open connection");
    }

    // lookup the system ID. it is used as a key for the function desc cache
    rc = RfcGetConnectionAttributes(intern->rfc_handle, &attributes, &error_info);
    if (rc == RFC_OK && attributes.sysId != NULL) {
        intern->system_id = sapuc_to_zend_string(attributes.sysId);
    } else {
        intern->system_id = NULL;
    }
}

PHP_METHOD(Connection, __construct)
{
    sapnwrfc_connection_object *intern;
    zend_error_handling zeh;
    HashTable *connection_params;
    HashTable *options = NULL;
    long len;

    // get the connection parameters
    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "h|h", &connection_params, &options) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    len = zend_hash_num_elements(connection_params);
    if (len == 0) {
        zend_throw_exception(sapnwrfc_connection_exception_ce, "No connection parameters given", 0);

        return;
    }

    // get the connection object (we need access to the rfc_handle)
    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    // set connection options
    sapnwrfc_connection_set_options(intern, options);

    // open connection
    sapnwrfc_open_connection(intern, connection_params);
}

PHP_METHOD(Connection, getSSOTicket)
{
    sapnwrfc_connection_object *intern;
    zend_error_handling zeh;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    unsigned int buf_len = 1;
    SAP_UC *buf_sso_ticket;
    zend_string *sso_ticket;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    zend_parse_parameters_none();
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    if(intern->rfc_handle == NULL) {
        // no connection handle
        zend_throw_exception(sapnwrfc_connection_exception_ce, "Failed to retrieve SSO ticket: connection closed.", 0);

        RETURN_NULL();
    }

    // determine the required buffer size
    buf_sso_ticket = emalloc(1);
    rc = RfcGetPartnerSSOTicket(intern->rfc_handle, buf_sso_ticket, &buf_len, &error_info);
    if (rc != RFC_BUFFER_TOO_SMALL) {
        // this is unexpected
        efree(buf_sso_ticket);

        sapnwrfc_throw_connection_exception(error_info, "Failed to retrieve SSO ticket.");

        RETURN_NULL();
    }

    // resize the allocated buffer to buf_len (which is the required size including 
    // the terminating NUL-byte)
    buf_sso_ticket = erealloc(buf_sso_ticket, buf_len);

    // fetch the SSO ticket
    rc = RfcGetPartnerSSOTicket(intern->rfc_handle, buf_sso_ticket, &buf_len, &error_info);
    if (rc != RFC_OK) {
        efree(buf_sso_ticket);

        sapnwrfc_throw_connection_exception(error_info, "Failed to retrieve SSO ticket.");

        RETURN_NULL();
    }

    sso_ticket = sapuc_to_zend_string(buf_sso_ticket);
    efree(buf_sso_ticket);

    RETURN_STR(sso_ticket);
}

PHP_METHOD(Connection, close)
{
    sapnwrfc_connection_object *intern;
    zend_error_handling zeh;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    zend_parse_parameters_none();
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    if(intern->rfc_handle == NULL) {
        // no connection open, return false.
        RETURN_FALSE;
    }

    rc = RfcCloseConnection(intern->rfc_handle, &error_info);
    if (rc == RFC_OK) {
        intern->rfc_handle = NULL;

        RETURN_TRUE;
    }

    // we got an error, throw an exception with details
    sapnwrfc_throw_connection_exception(error_info, "Could not close connection");

    RETURN_NULL();
}

PHP_METHOD(Connection, getAttributes)
{
    sapnwrfc_connection_object *intern;
    zend_error_handling zeh;
    RFC_ATTRIBUTES attributes;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    zend_parse_parameters_none();
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());
    rc = RfcGetConnectionAttributes(intern->rfc_handle, &attributes, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Could not fetch connection attributes");

        RETURN_NULL();
    }

    array_init(return_value);
    add_assoc_str(return_value, "dest", sapuc_to_zend_string(attributes.dest));
    add_assoc_str(return_value, "host", sapuc_to_zend_string(attributes.host));
    add_assoc_str(return_value, "partnerHost", sapuc_to_zend_string(attributes.partnerHost));
    add_assoc_str(return_value, "sysNumber", sapuc_to_zend_string(attributes.sysNumber));
    add_assoc_str(return_value, "sysId", sapuc_to_zend_string(attributes.sysId));
    add_assoc_str(return_value, "client", sapuc_to_zend_string(attributes.client));
    add_assoc_str(return_value, "user", sapuc_to_zend_string(attributes.user));
    add_assoc_str(return_value, "language", sapuc_to_zend_string(attributes.language));
    add_assoc_str(return_value, "trace", sapuc_to_zend_string(attributes.trace));
    add_assoc_str(return_value, "isoLanguage", sapuc_to_zend_string(attributes.isoLanguage));
    add_assoc_str(return_value, "codepage", sapuc_to_zend_string(attributes.codepage));
    add_assoc_str(return_value, "partnerCodepage", sapuc_to_zend_string(attributes.partnerCodepage));
    add_assoc_str(return_value, "rfcRole", sapuc_to_zend_string(attributes.rfcRole));
    add_assoc_str(return_value, "type", sapuc_to_zend_string(attributes.type));
    add_assoc_str(return_value, "partnerType", sapuc_to_zend_string(attributes.partnerType));
    add_assoc_str(return_value, "rel", sapuc_to_zend_string(attributes.rel));
    add_assoc_str(return_value, "partnerRel", sapuc_to_zend_string(attributes.partnerRel));
    add_assoc_str(return_value, "kernelRel", sapuc_to_zend_string(attributes.kernelRel));
    add_assoc_str(return_value, "cpicConvId", sapuc_to_zend_string(attributes.cpicConvId));
    add_assoc_str(return_value, "progName", sapuc_to_zend_string(attributes.progName));
    add_assoc_str(return_value, "partnerBytesPerChar", sapuc_to_zend_string(attributes.partnerBytesPerChar));
    add_assoc_str(return_value, "partnerSystemCodepage", sapuc_to_zend_string(attributes.partnerSystemCodepage));
}

PHP_METHOD(Connection, ping)
{
    sapnwrfc_connection_object *intern;
    zend_error_handling zeh;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    zend_parse_parameters_none();
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());
    rc = RfcPing(intern->rfc_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to ping connection");

        RETURN_NULL();
    }

    RETURN_TRUE;
}

PHP_METHOD(Connection, getFunction)
{
    sapnwrfc_connection_object *intern;
    sapnwrfc_function_object *func_intern;
    zend_error_handling zeh;
    zend_string *function_name;
    zend_string *parameter_name;
    zval zv_true;
    unsigned i;

    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    RFC_FUNCTION_DESC_HANDLE function_desc_handle;
    RFC_PARAMETER_DESC parameter_desc;
    SAP_UC *function_name_u;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &function_name) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    // clear the function desc cache before looking up the function if requested
    if (!intern->use_function_desc_cache) {
        (void) rfc_clear_function_desc_cache(function_name, intern->system_id);
        // if clearing the cache did not work, we just try to continue anyway...
    }

    // get function description
    function_desc_handle = RfcGetFunctionDesc(intern->rfc_handle,
                (function_name_u = zend_string_to_sapuc(function_name)),
                &error_info);
    free((char *)function_name_u);

    if (function_desc_handle == NULL) {
        sapnwrfc_throw_function_exception(error_info, "Failed to lookup function %s", ZSTR_VAL(function_name));

        RETURN_NULL();
    }

    // create function entry object
    object_init_ex(return_value, sapnwrfc_function_ce);
    func_intern = SAPNWRFC_FUNCTION_OBJ_P(return_value);
    func_intern->rfc_handle = intern->rfc_handle;
    func_intern->function_desc_handle = function_desc_handle;
    func_intern->name = zend_string_copy(function_name);

    // add a 'name' property to the function object. this helps to identify the object
    // when dumping it with var_dump()
    add_property_str(return_value, "name", zend_string_copy(function_name));

    // get nr of parameters
    rc = RfcGetParameterCount(func_intern->function_desc_handle, &func_intern->parameter_count, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to get parameter count for function %s", ZSTR_VAL(func_intern->name));

        RETURN_NULL();
    }

    // initialize parameter status hash table
    zend_hash_init(func_intern->parameter_status, func_intern->parameter_count, NULL, NULL, 0);
    ZVAL_TRUE(&zv_true);

    for (i = 0; i < func_intern->parameter_count; i++) {
        // get parameter information
        rc = RfcGetParameterDescByIndex(func_intern->function_desc_handle, i, &parameter_desc, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter description for function %s", ZSTR_VAL(func_intern->name));

            RETURN_NULL();
        }

        // make the parameter active by default
        parameter_name = sapuc_to_zend_string(parameter_desc.name);
        zend_hash_add(func_intern->parameter_status, parameter_name, &zv_true);
        zend_string_release(parameter_name);
    }
}

PHP_METHOD(Connection, setIniPath)
{
    zend_error_handling zeh;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    zend_string *path;
    SAP_UC *path_u;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &path) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    rc = RfcSetIniPath((path_u = zend_string_to_sapuc(path)), &error_info);
    free((char *)path_u);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to set INI file path");

        RETURN_NULL();
    }

    RETURN_TRUE;
}

PHP_METHOD(Connection, reloadIniFile)
{
    zend_error_handling zeh;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, &zeh);
    zend_parse_parameters_none();
    zend_restore_error_handling(&zeh);

    rc = RfcReloadIniFile(&error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to reload INI file");

        RETURN_NULL();
    }

    RETURN_TRUE;
}

PHP_METHOD(Connection, setTraceDir)
{
    zend_error_handling zeh;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    zend_string *path;
    SAP_UC *path_u;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &path) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    rc = RfcSetTraceDir((path_u = zend_string_to_sapuc(path)), &error_info);
    free((char *)path_u);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to set trace directory");

        return;
    }
}

PHP_METHOD(Connection, setTraceLevel)
{
    zend_error_handling zeh;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    unsigned int level;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &level) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    if (level < 0 || level > 3) {
        zend_throw_exception(sapnwrfc_connection_exception_ce, "Failed to set trace level. Value out of range (expected 0 - 3)", 0);

        return;
    }

    rc = RfcSetTraceLevel(NULL, NULL, level, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to set trace level");

        return;
    }
}

// Connection class methods
PHP_METHOD(Connection, version)
{
    char *version;
    int len;

    zend_parse_parameters_none();

    len = spprintf(&version, 0, "%s", PHP_SAPNWRFC_VERSION);

    RETVAL_STRINGL(version, len);
    efree(version);
}

PHP_METHOD(Connection, rfcVersion)
{
    char *version;
    int len;
    unsigned int major, minor, patch;

    zend_parse_parameters_none();

    RfcGetVersion(&major, &minor, &patch);

    len = spprintf(&version, 0, "%d.%d.%d", major, minor, patch);

    RETVAL_STRINGL(version, len);
    efree(version);
}

PHP_METHOD(RemoteFunction, invoke)
{
    sapnwrfc_function_object *intern;
    zend_error_handling zeh;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    RFC_FUNCTION_HANDLE function_handle;
    RFC_PARAMETER_DESC parameter_desc;
    int is_active;
    unsigned int i = 0;
    HashTable *in_parameters_hash = NULL;
    HashTable *options_hash = NULL;
    zend_string *tmp;
    zend_string *key;
    zval *val;
    zval retval;
    SAP_UC *parameter_name_u;
    unsigned char rtrim_enabled = 0;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|hh", &in_parameters_hash, &options_hash) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    // create the function handle
    function_handle = RfcCreateFunction(intern->function_desc_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to create function handle");

        RETURN_NULL();
    }

    // set parameter status
    ZEND_HASH_FOREACH_STR_KEY_VAL(intern->parameter_status, key, val) {
        if (zend_is_true(val)) {
            continue;
        }

        // deactivate the parameter if requested
        rc = RfcSetParameterActive(function_handle, (parameter_name_u = zend_string_to_sapuc(key)), 0, &error_info);
        free((char *)parameter_name_u);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to deactivate parameter %s", ZSTR_VAL(key));

            RfcDestroyFunction(function_handle, &error_info);

            RETURN_NULL();
        }
    } ZEND_HASH_FOREACH_END();

    if (in_parameters_hash) {
        ZEND_HASH_FOREACH_STR_KEY_VAL(in_parameters_hash, key, val) {
            if (!key) { // not a string key
                zend_throw_exception(sapnwrfc_function_exception_ce, "All parameter keys must be strings", 0);

                RfcDestroyFunction(function_handle, &error_info);

                RETURN_NULL();
            }

            ZVAL_DEREF(val);

            // get parameter desc by name
            rc = RfcGetParameterDescByName(intern->function_desc_handle, (parameter_name_u = zend_string_to_sapuc(key)), &parameter_desc, &error_info);
            free((char *)parameter_name_u);

            if (rc != RFC_OK) {
                sapnwrfc_throw_function_exception(error_info, "Failed to get description for parameter %s", ZSTR_VAL(key));
                RfcDestroyFunction(function_handle, &error_info);

                RETURN_NULL();
            }

            // a parameter is provided, so make sure it is active
            rc = RfcSetParameterActive(function_handle, (parameter_name_u = zend_string_to_sapuc(key)), 1, &error_info);
            free((char *)parameter_name_u);
            if (rc != RFC_OK) {
                sapnwrfc_throw_function_exception(error_info, "Failed to activate parameter %s", ZSTR_VAL(key));

                RfcDestroyFunction(function_handle, &error_info);

                RETURN_NULL();
            }

            // set the parameter value
            switch(parameter_desc.direction) {
                case RFC_EXPORT:
                    break;
                case RFC_IMPORT:
                case RFC_CHANGING:
                case RFC_TABLES:
                    if (rfc_set_parameter_value(function_handle, intern->function_desc_handle, key, val) == RFC_SET_VALUE_ERROR) {
                        // setting the parameter failed; an exception has been thrown
                        RfcDestroyFunction(function_handle, &error_info);

                        RETURN_NULL();
                    }
                    break;
                default: // unknown direction
                    zend_throw_exception(sapnwrfc_function_exception_ce, "Internal error: unknown parameter direction", 0);

                    RfcDestroyFunction(function_handle, &error_info);

                    RETURN_NULL();
            }

        } ZEND_HASH_FOREACH_END();
    }

    // invoke the function
    rc = RfcInvoke(intern->rfc_handle, function_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to invoke function %s", ZSTR_VAL(intern->name));
        RfcDestroyFunction(function_handle, &error_info);

        RETURN_NULL();
    }

    // now get the return values
    array_init(return_value);

    // check for rtrim option
    if (options_hash) {
        zval *rtrim;
        if ((rtrim = zend_hash_str_find(options_hash, "rtrim", strlen("rtrim"))) != NULL) {
            convert_to_boolean(rtrim);
            rtrim_enabled = zend_is_true(rtrim);
        }
    }

    for (i = 0; i < intern->parameter_count; i++) {
        rc = RfcGetParameterDescByIndex(intern->function_desc_handle, i, &parameter_desc, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter description for function %s", ZSTR_VAL(intern->name));
            RfcDestroyFunction(function_handle, &error_info);

            RETURN_NULL();
        }

        // check if the parameter is active
        rc = RfcIsParameterActive(function_handle, parameter_desc.name, &is_active, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter status");
            RfcDestroyFunction(function_handle, &error_info);

            RETURN_NULL();
        }

        if (!is_active) {
            continue;
        }

        switch(parameter_desc.direction) {
            case RFC_IMPORT:
                break;
            case RFC_EXPORT:
            case RFC_CHANGING:
            case RFC_TABLES:
                tmp = sapuc_to_zend_string(parameter_desc.name);
                retval = rfc_get_parameter_value(function_handle, intern->function_desc_handle, tmp, rtrim_enabled);

                if (ZVAL_IS_NULL(&retval)) {
                    zend_string_release(tmp);
                    RfcDestroyFunction(function_handle, &error_info);
                    // getting the parameter failed; an exception has been thrown
                    RETURN_NULL();
                }

                add_assoc_zval(return_value, ZSTR_VAL(tmp), &retval);

                zend_string_release(tmp);
                break;
        }
    }

    // destroy the function handle
    RfcDestroyFunction(function_handle, &error_info);
}

PHP_METHOD(RemoteFunction, setParameterActive)
{
    sapnwrfc_function_object *intern;
    zend_error_handling zeh;
    zend_string *parameter_name;
    zend_bool parameter_active;
    zval tmp;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sb", &parameter_name, &parameter_active) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    ZVAL_BOOL(&tmp, parameter_active);
    zend_hash_update(intern->parameter_status, parameter_name, &tmp);
}

PHP_METHOD(RemoteFunction, isParameterActive)
{
    sapnwrfc_function_object *intern;
    zend_error_handling zeh;
    zend_string *parameter_name;
    zval *tmp;

    zend_replace_error_handling(EH_THROW, NULL, NULL);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &parameter_name) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    tmp = zend_hash_find(intern->parameter_status, parameter_name);

    if(tmp == NULL) {
        zend_throw_exception_ex(sapnwrfc_function_exception_ce, 0, "Failed to get status for parameter %s: invalid parameter name", ZSTR_VAL(parameter_name));

        RETURN_NULL();
    }

    RETURN_ZVAL(tmp, 1, 0);
}

PHP_METHOD(RemoteFunction, getFunctionDescription)
{
    sapnwrfc_function_object *intern;
    zend_error_handling zeh;
    zval parameter_description;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters_none() == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    if (rfc_describe_function_interface(intern->function_desc_handle, &parameter_description)) {
        zend_throw_exception(sapnwrfc_function_exception_ce, "Failed to get function interface description.", 0);

        return;
    }

    RETURN_ZVAL(&parameter_description, 1, 1);
}

PHP_METHOD(RemoteFunction, getName)
{
    zend_error_handling zeh;
    sapnwrfc_function_object *intern;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters_none() == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    RETURN_STR(intern->name);
}

static void register_sapnwrfc_connection_object()
{
    zend_class_entry ce;

    memcpy(&sapnwrfc_connection_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    sapnwrfc_connection_object_handlers.offset = XtOffsetOf(sapnwrfc_connection_object, zobj);
    sapnwrfc_connection_object_handlers.free_obj = sapnwrfc_connection_object_free;
    sapnwrfc_connection_object_handlers.clone_obj = NULL;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\Connection", sapnwrfc_connection_class_functions);
    ce.create_object = sapnwrfc_connection_object_create;
    sapnwrfc_connection_ce = zend_register_internal_class(&ce);

    zend_declare_class_constant_long(sapnwrfc_connection_ce, "TRACE_LEVEL_OFF", sizeof("TRACE_LEVEL_OFF") - 1, 0);
    zend_declare_class_constant_long(sapnwrfc_connection_ce, "TRACE_LEVEL_BRIEF", sizeof("TRACE_LEVEL_BRIEF") - 1, 1);
    zend_declare_class_constant_long(sapnwrfc_connection_ce, "TRACE_LEVEL_VERBOSE", sizeof("TRACE_LEVEL_VERBOSE") - 1, 2);
    zend_declare_class_constant_long(sapnwrfc_connection_ce, "TRACE_LEVEL_FULL", sizeof("TRACE_LEVEL_FULL") - 1, 3);
}

static void register_sapnwrfc_function_object()
{
    zend_class_entry ce;

    memcpy(&sapnwrfc_function_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    sapnwrfc_function_object_handlers.offset = XtOffsetOf(sapnwrfc_function_object, zobj);
    sapnwrfc_function_object_handlers.free_obj = sapnwrfc_function_object_free;
    sapnwrfc_function_object_handlers.clone_obj = NULL;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\RemoteFunction", sapnwrfc_function_class_functions);
    ce.create_object = sapnwrfc_function_object_create;
    sapnwrfc_function_ce = zend_register_internal_class(&ce);
    sapnwrfc_function_ce->ce_flags |= ZEND_ACC_FINAL;
}

unsigned int rfc_clear_function_desc_cache(zend_string *function_name, zend_string *repository_id)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *function_name_u = NULL;
    SAP_UC *repository_id_u = NULL;
    
    // TODO check the patchlevel to find out if we need the 6x \0 hack
    //      see SAP note 1818687 and https://archive.sap.com/discussions/thread/3328863

    function_name_u = zend_string_to_sapuc(function_name);

    // remove from the default repository
    rc = RfcRemoveFunctionDesc(NULL, function_name_u, &error_info);

    // if a repository ID was passed, use that
    // (usually the repository ID is the sysId)
    if (repository_id) {
        rc = RfcRemoveFunctionDesc(
            (repository_id_u = zend_string_to_sapuc(repository_id)), 
            function_name_u,
            &error_info);
        free((void *) repository_id_u);
    }

    free((void *) function_name_u);

    return rc == RFC_OK;
}

PHP_FUNCTION(clearFunctionDescCache)
{
    zend_error_handling zeh;
    zend_string *function_name;
    zend_string *repository_id = NULL;

    zend_replace_error_handling(EH_THROW, NULL, &zeh);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S|S", &function_name, &repository_id) == FAILURE) {
        zend_restore_error_handling(&zeh);

        return;
    }
    zend_restore_error_handling(&zeh);

    if (rfc_clear_function_desc_cache(function_name, repository_id)) {
        RETVAL_BOOL(1);
    } else {
        RETVAL_BOOL(0);
    }
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sapnwrfc)
{
    register_sapnwrfc_connection_object();
    register_sapnwrfc_function_object();

    sapnwrfc_register_exceptions();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sapnwrfc)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sapnwrfc)
{
    unsigned int major, minor, patch;
    char *version;

    RfcGetVersion(&major, &minor, &patch);
    spprintf(&version, 0, "%d.%d.%d", major, minor, patch);

    php_info_print_table_start();
    php_info_print_table_header(2, "sapnwrfc support", "enabled");
    php_info_print_table_row(2, "Version", PHP_SAPNWRFC_VERSION);
    php_info_print_table_row(2, "SAP NW RFC SDK", version);
    php_info_print_table_end();

    efree(version);
}
/* }}} */

/* {{{ sapnwrfc_functions[]
 *
 * Every user visible function must have an entry in sapnwrfc_functions[].
 */
const zend_function_entry sapnwrfc_functions[] = {
    ZEND_NS_FE("SAPNWRFC", clearFunctionDescCache, arginfo_clearFunctionDescCache)
    PHP_FE_END    /* Must be the last line in sapnwrfc_functions[] */
};
/* }}} */

/* {{{ sapnwrfc_module_entry
 */
zend_module_entry sapnwrfc_module_entry = {
    STANDARD_MODULE_HEADER,
    "sapnwrfc",
    sapnwrfc_functions,
    PHP_MINIT(sapnwrfc),
    PHP_MSHUTDOWN(sapnwrfc),
    NULL,
    NULL,
    PHP_MINFO(sapnwrfc),
    PHP_SAPNWRFC_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SAPNWRFC
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(sapnwrfc)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
