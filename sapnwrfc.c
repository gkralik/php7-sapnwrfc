/**
 * Copyright (c) 2016 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik@gmail.com>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "php_sapnwrfc.h"
#include "exceptions.h"
#include "string_helper.h"
#include "rfc_parameters.h"

#include "sapnwrfc.h"

// class entries
zend_class_entry *sapnwrfc_connection_ce;
zend_class_entry *sapnwrfc_function_ce;

// object handlers
zend_object_handlers sapnwrfc_connection_object_handlers;
zend_object_handlers sapnwrfc_function_object_handlers;

// connection object
typedef struct _sapnwrfc_connection_object {
    RFC_CONNECTION_HANDLE rfc_handle;
    RFC_CONNECTION_PARAMETER *rfc_login_params;
    int rfc_login_params_len;
    zend_object zobj;
} sapnwrfc_connection_object;

// function object
typedef struct _sapnwrfc_function_object {
    RFC_CONNECTION_HANDLE rfc_handle;
    RFC_FUNCTION_HANDLE function_handle;
    RFC_FUNCTION_DESC_HANDLE function_desc_handle;
    unsigned int parameter_count;
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

// forward declaration of class methods
PHP_METHOD(Connection, __construct);
PHP_METHOD(Connection, attributes);
PHP_METHOD(Connection, ping);
PHP_METHOD(Connection, getFunction);
PHP_METHOD(Connection, close);
PHP_METHOD(Connection, setIniPath);
PHP_METHOD(Connection, reloadIniFile);
PHP_METHOD(Connection, version);
PHP_METHOD(Connection, rfcVersion);

PHP_METHOD(RemoteFunction, invoke);
PHP_METHOD(RemoteFunction, setParameterActive);
PHP_METHOD(RemoteFunction, isParameterActive);

// arginfo
//ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(name, IS_VOID, NULL, 0)
//ZEND_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null)

ZEND_BEGIN_ARG_INFO_EX(arginfo_Connection___construct, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_attributes, IS_ARRAY, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_ping, _IS_BOOL, NULL, 0)
ZEND_END_ARG_INFO()

// NOTE: strangeley, the macro is defined with class_name, not #class_name. enclose in quotes to mitigate
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Connection_getFunction, 0, 1, IS_OBJECT, "SAPNWRFC\\RemoteFunction", 0)
    ZEND_ARG_TYPE_INFO(0, functionName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_close, _IS_BOOL, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_Connection_setIniPath, 0, 1, _IS_BOOL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_reloadIniFile, _IS_BOOL, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_version, IS_STRING, NULL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Connection_rfcVersion, IS_STRING, NULL, 0)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_invoke, 0, 1, IS_ARRAY, NULL, 0)
    ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_setParameterActive, 0, 2, IS_VOID, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, parameterName, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, isActive, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_RemoteFunction_isParameterActive, 0, 1, _IS_BOOL, NULL, 0)
    ZEND_ARG_TYPE_INFO(0, parameterName, IS_STRING, 0)
ZEND_END_ARG_INFO()


// class method tables
static zend_function_entry sapnwrfc_connection_class_functions[] = {
    PHP_ME(Connection, __construct, arginfo_Connection___construct, ZEND_ACC_PUBLIC)
    PHP_ME(Connection, attributes, arginfo_Connection_attributes, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, ping, arginfo_Connection_ping, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, getFunction, arginfo_Connection_getFunction, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, close, arginfo_Connection_close, ZEND_ACC_PUBLIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, setIniPath, arginfo_Connection_setIniPath, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, reloadIniFile, arginfo_Connection_reloadIniFile, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, version, arginfo_Connection_version, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_ME(Connection, rfcVersion, arginfo_Connection_rfcVersion, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC | ZEND_ACC_HAS_RETURN_TYPE)
    PHP_FE_END
};

static zend_function_entry sapnwrfc_function_class_functions[] = {
    PHP_ME(RemoteFunction, invoke, arginfo_RemoteFunction_invoke, ZEND_ACC_PUBLIC)
    PHP_ME(RemoteFunction, setParameterActive, arginfo_RemoteFunction_setParameterActive, ZEND_ACC_PUBLIC)
    PHP_ME(RemoteFunction, isParameterActive, arginfo_RemoteFunction_isParameterActive, ZEND_ACC_PUBLIC)
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

    intern = SAPNWRFC_CONNECTION_OBJ(object);

    /* free the RFC handle */
    if(intern->rfc_handle) {
        RfcCloseConnection(intern->rfc_handle, &error_info);
        intern->rfc_handle = NULL;
    }

    intern->rfc_handle = NULL;

    // free login parameters
    if(intern->rfc_login_params) {
        for(int i = 0; i < intern->rfc_login_params_len; i++) {
            free((char *)intern->rfc_login_params[i].name);
            free((char *)intern->rfc_login_params[i].value);
        }
        efree(intern->rfc_login_params);
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

    if (intern->function_handle) {
        (void) RfcDestroyFunction(intern->function_handle, &error_info);
        intern->function_handle = NULL;
    }

    intern->rfc_handle = NULL;
    intern->parameter_count = 0;

    zend_string_release(intern->name);

    /* call Zend's free handler, which will free the object properties */
    zend_object_std_dtor(&intern->zobj);
}

static void sapnwrfc_open_connection(sapnwrfc_connection_object *intern, zval *connection_params)
{
    RFC_ERROR_INFO error_info;
    HashTable *connection_params_hash;
    int i = 0;
    zend_string *key;
    zval *val;

    connection_params_hash = Z_ARRVAL_P(connection_params);
    intern->rfc_login_params_len = zend_hash_num_elements(connection_params_hash);

    intern->rfc_login_params = ecalloc(intern->rfc_login_params_len, sizeof(RFC_CONNECTION_PARAMETER));

    ZEND_HASH_FOREACH_STR_KEY_VAL(connection_params_hash, key, val) {
        if (key) { // is string
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
}

PHP_METHOD(Connection, __construct)
{
    sapnwrfc_connection_object *intern;
    zval *connection_params;
    long len;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);

    // get the connection parameters
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &connection_params) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    len = zend_hash_num_elements(Z_ARRVAL_P(connection_params));
    if (len == 0) {
        zend_error(E_WARNING, "No connection parameters given");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    // get the connection object (we need access to the rfc_handle)
    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    // open connection
    // TODO inline?
    sapnwrfc_open_connection(intern, connection_params);

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

PHP_METHOD(Connection, close)
{
    sapnwrfc_connection_object *intern;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    zend_parse_parameters_none();

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    if(intern->rfc_handle == NULL) {
        // no connection open, return false.
        RETURN_FALSE;
    }

    rc = RfcCloseConnection(intern->rfc_handle, &error_info);
    if (rc == RFC_OK) {
        intern->rfc_handle = NULL;

        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_TRUE;
    }

    // we got an error, throw an exception with details
    sapnwrfc_throw_connection_exception(error_info, "Could not close connection");

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
    RETURN_NULL();
}

PHP_METHOD(Connection, attributes)
{
    sapnwrfc_connection_object *intern;
    RFC_ATTRIBUTES attributes;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    zend_parse_parameters_none();

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());
    rc = RfcGetConnectionAttributes(intern->rfc_handle, &attributes, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Could not fetch connection attributes");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
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

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

PHP_METHOD(Connection, ping)
{
    sapnwrfc_connection_object *intern;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    zend_parse_parameters_none();

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());
    rc = RfcPing(intern->rfc_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to ping connection");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
    RETURN_TRUE;
}

PHP_METHOD(Connection, getFunction)
{
    sapnwrfc_connection_object *intern;
    sapnwrfc_function_object *func_intern;
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    RFC_FUNCTION_DESC_HANDLE function_desc_handle;
    zend_string *function_name;
    zend_string *tmp;
    SAP_UC *function_name_u;
    RFC_PARAMETER_DESC parameter_desc;
    zval parameter_description;
    unsigned i;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &function_name) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    intern = SAPNWRFC_CONNECTION_OBJ_P(getThis());

    // get function description
    function_desc_handle = RfcGetFunctionDesc(intern->rfc_handle,
                (function_name_u = zend_string_to_sapuc(function_name)),
                &error_info);
    free((char *)function_name_u);

    if (function_desc_handle == NULL) {
        sapnwrfc_throw_function_exception(error_info, "Failed to lookup function %s", ZSTR_VAL(function_name));
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    // create function entry object
    object_init_ex(return_value, sapnwrfc_function_ce);
    func_intern = SAPNWRFC_FUNCTION_OBJ_P(return_value);
    func_intern->rfc_handle = intern->rfc_handle;
    func_intern->function_desc_handle = function_desc_handle;
    func_intern->name = zend_string_copy(function_name);

    add_property_str(return_value, "name", zend_string_copy(function_name));

    // get nr of parameters
    rc = RfcGetParameterCount(func_intern->function_desc_handle, &func_intern->parameter_count, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to get parameter count for function %s", ZSTR_VAL(func_intern->name));
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    for (i = 0; i < func_intern->parameter_count; i++) {
        // get parameter information
        rc = RfcGetParameterDescByIndex(func_intern->function_desc_handle, i, &parameter_desc, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter description for function %s", ZSTR_VAL(func_intern->name));
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        array_init(&parameter_description);

        add_assoc_str(&parameter_description, "type", sapuc_to_zend_string((SAP_UC *)RfcGetTypeAsString(parameter_desc.type)));
        add_assoc_str(&parameter_description, "direction", sapuc_to_zend_string((SAP_UC *)RfcGetDirectionAsString(parameter_desc.direction)));
        add_assoc_str(&parameter_description, "description", sapuc_to_zend_string(parameter_desc.parameterText));
        add_assoc_bool(&parameter_description, "optional", parameter_desc.optional);
        add_assoc_str(&parameter_description, "defaultValue", sapuc_to_zend_string(parameter_desc.defaultValue));

        tmp = sapuc_to_zend_string(parameter_desc.name);
        add_property_zval(return_value, ZSTR_VAL(tmp), &parameter_description);
        zend_string_release(tmp);

        zval_ptr_dtor(&parameter_description);
    }

    // create the function handle
    func_intern->function_handle = RfcCreateFunction(func_intern->function_desc_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to create function handle");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

PHP_METHOD(Connection, setIniPath)
{
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;
    zend_string *path;
    SAP_UC *path_u;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &path) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    rc = RfcSetIniPath((path_u = zend_string_to_sapuc(path)), &error_info);
    free((char *)path_u);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to set INI file path");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
    RETURN_TRUE;
}

PHP_METHOD(Connection, reloadIniFile)
{
    RFC_ERROR_INFO error_info;
    RFC_RC rc = RFC_OK;

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);
    zend_parse_parameters_none();

    rc = RfcReloadIniFile(&error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_connection_exception(error_info, "Failed to reload INI file");
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
    RETURN_TRUE;
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
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    RFC_PARAMETER_DESC parameter_desc;
    int is_active;
    unsigned int i = 0;
    zval *in_parameters;
    HashTable *in_parameters_hash;
    zend_string *tmp;
    zend_string *key;
    zval *val;
    zval retval;
    SAP_UC *parameter_name_u;

    zend_replace_error_handling(EH_THROW, sapnwrfc_function_exception_ce, NULL);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &in_parameters) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    in_parameters_hash = Z_ARRVAL_P(in_parameters);

    ZEND_HASH_FOREACH_STR_KEY_VAL(in_parameters_hash, key, val) {
        if (!key) {
            // not a string key
            zend_error(E_WARNING, "All parameter keys must be strings");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        // get parameter desc by name
        rc = RfcGetParameterDescByName(intern->function_desc_handle, (parameter_name_u = zend_string_to_sapuc(key)), &parameter_desc, &error_info);
        free((char *)parameter_name_u);

        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get description for parameter %s", ZSTR_VAL(key));
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        // check if the parameter is active
        rc = RfcIsParameterActive(intern->function_handle, parameter_desc.name, &is_active, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get status of parameter %s", ZSTR_VAL(key));
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        if (is_active == 0) {
            continue;
        }

        // set the parameter value
        switch(parameter_desc.direction) {
            case RFC_EXPORT:
                break;
            case RFC_IMPORT:
            case RFC_CHANGING:
            case RFC_TABLES:
                if (rfc_set_parameter_value(intern->function_handle, intern->function_desc_handle, key, val) == RFC_SET_VALUE_ERROR) {
                    // setting the parameter failed; an exception has been thrown
                    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
                    RETURN_NULL();
                }
                break;
            default:
                // unknown direction
                zend_error(E_WARNING, "Unknown parameter direction");
                zend_replace_error_handling(EH_NORMAL, NULL, NULL);
                RETURN_NULL();
        }

    } ZEND_HASH_FOREACH_END();

    // invoke the function
    rc = RfcInvoke(intern->rfc_handle, intern->function_handle, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to invoke function %s", ZSTR_VAL(intern->name));
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    // now get the return values
    array_init(return_value);

    for (i = 0; i < intern->parameter_count; i++) {
        rc = RfcGetParameterDescByIndex(intern->function_desc_handle, i, &parameter_desc, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter description for function %s", ZSTR_VAL(intern->name));
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        // check if the parameter is active
        rc = RfcIsParameterActive(intern->function_handle, parameter_desc.name, &is_active, &error_info);
        if (rc != RFC_OK) {
            sapnwrfc_throw_function_exception(error_info, "Failed to get parameter status");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            RETURN_NULL();
        }

        if (is_active == 0) {
            continue;
        }

        switch(parameter_desc.direction) {
            case RFC_IMPORT:
                break;
            case RFC_EXPORT:
            case RFC_CHANGING:
            case RFC_TABLES:
                tmp = sapuc_to_zend_string(parameter_desc.name);
                retval = rfc_get_parameter_value(intern->function_handle, intern->function_desc_handle, tmp);

                if (ZVAL_IS_NULL(&retval)) {
                    zend_string_release(tmp);
                    // getting the parameter failed; an exception has been thrown
                    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
                    RETURN_NULL();
                }

                add_assoc_zval(return_value, ZSTR_VAL(tmp), &retval);

                zend_string_release(tmp);
                break;
        }
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

PHP_METHOD(RemoteFunction, setParameterActive)
{
    sapnwrfc_function_object *intern;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    zend_string *parameter_name;
    zend_bool parameter_active;
    SAP_UC *parameter_name_u;

    zend_replace_error_handling(EH_THROW, sapnwrfc_function_exception_ce, NULL);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sb", &parameter_name, &parameter_active) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    rc = RfcSetParameterActive(intern->function_handle, (parameter_name_u = zend_string_to_sapuc(parameter_name)), parameter_active, &error_info);
    free((char *)parameter_name_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to set status for parameter %s", parameter_name);
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

PHP_METHOD(RemoteFunction, isParameterActive)
{
    sapnwrfc_function_object *intern;
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    zend_string *parameter_name;
    SAP_UC *parameter_name_u;
    int is_active;

    zend_replace_error_handling(EH_THROW, sapnwrfc_function_exception_ce, NULL);

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &parameter_name) == FAILURE) {
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        return;
    }

    intern = SAPNWRFC_FUNCTION_OBJ_P(getThis());

    rc = RfcIsParameterActive(intern->function_handle, (parameter_name_u = zend_string_to_sapuc(parameter_name)), &is_active, &error_info);
    free((char *)parameter_name_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception(error_info, "Failed to get status for parameter %s", ZSTR_VAL(parameter_name));
        zend_replace_error_handling(EH_NORMAL, NULL, NULL);
        RETURN_NULL();
    }

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);

    if (is_active) {
        RETURN_TRUE;
    }

    RETURN_FALSE;
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
}
/* }}} */

/* {{{ sapnwrfc_functions[]
 *
 * Every user visible function must have an entry in sapnwrfc_functions[].
 */
const zend_function_entry sapnwrfc_functions[] = {
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
