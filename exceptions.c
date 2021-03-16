/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#include "php.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "exceptions.h"
#include "string_helper.h"

#include "sapnwrfc.h"

zend_class_entry *sapnwrfc_exception_ce;
zend_class_entry *sapnwrfc_connection_exception_ce;
zend_class_entry *sapnwrfc_function_exception_ce;

typedef struct _sapnwrfc_exception_object {
    zend_object *zobj;
} sapnwrfc_exception_object;

typedef struct _sapnwrfc_connection_exception_object {
    zend_object zobj;
} sapnwrfc_connection_exception_object;

typedef struct _sapnwrfc_function_exception_object {
    zend_object zobj;
} sapnwrfc_functioncall_exception_object;

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(arginfo_Exception_getErrorInfo, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

static zend_function_entry sapnwrfc_exception_class_functions[] = {
    PHP_ME(Exception, getErrorInfo, arginfo_Exception_getErrorInfo, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

void sapnwrfc_throw_connection_exception(RFC_ERROR_INFO error_info, char *msg, ...)
{
    va_list args;
    zend_string *message;
    zval info;
    zval ex;
    zend_error_handling zeh;

    va_start(args, msg);
    message = vstrpprintf(0, msg, args);
    va_end(args);

    array_init(&info);

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, &zeh);

    object_init_ex(&ex, sapnwrfc_connection_exception_ce);

    zend_update_property_string(sapnwrfc_connection_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "message", sizeof("message") - 1, ZSTR_VAL(message));
    zend_update_property_long(sapnwrfc_connection_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "code", sizeof("code") - 1, error_info.code);

    // populate errorInfo array
    add_assoc_long(&info, "code", error_info.code);
    add_assoc_str(&info, "key", sapuc_to_zend_string(error_info.key));
    add_assoc_str(&info, "message", sapuc_to_zend_string(error_info.message));

    switch(error_info.group) {
        case LOGON_FAILURE:                   // Error message raised when logon fails
        case COMMUNICATION_FAILURE:           // Problems with the network connection (or backend broke down and killed the connection)
        case EXTERNAL_RUNTIME_FAILURE:        // Problems in the RFC runtime of the external program (i.e "this" library)
            // no additional properties, just the generic one's from above
            break;
        case ABAP_APPLICATION_FAILURE:        // ABAP Exception raised in ABAP function modules
        case ABAP_RUNTIME_FAILURE:            // ABAP Message raised in ABAP function modules or in ABAP runtime of the backend (e.g Kernel)
        case EXTERNAL_APPLICATION_FAILURE:    // Problems in the external program (e.g in the external server implementation)
        case EXTERNAL_AUTHORIZATION_FAILURE:  // Problems raised in the authorization check handler provided by the external server implementation
            add_assoc_str(&info, "abapMsgClass", sapuc_to_zend_string(error_info.abapMsgClass));
            add_assoc_str(&info, "abapMsgType", sapuc_to_zend_string(error_info.abapMsgType));
            add_assoc_str(&info, "abapMsgNumber", sapuc_to_zend_string(error_info.abapMsgNumber));
            add_assoc_str(&info, "abapMsgV1", sapuc_to_zend_string(error_info.abapMsgV1));
            add_assoc_str(&info, "abapMsgV2", sapuc_to_zend_string(error_info.abapMsgV2));
            add_assoc_str(&info, "abapMsgV3", sapuc_to_zend_string(error_info.abapMsgV3));
            add_assoc_str(&info, "abapMsgV4", sapuc_to_zend_string(error_info.abapMsgV4));
            break;
        case RFC_OK: // LCOV_EXCL_START
            zend_error(E_ERROR, "Internal error: exception handler called for RFC_OK");
            zend_restore_error_handling(&zeh);
            zend_string_release(message);

            return;
            // LCOV_EXCL_STOP
        default:
            zend_error(E_ERROR, "Internal error: unknown error group");
            zend_restore_error_handling(&zeh);
            zend_string_release(message);

            return;
    }

    zend_update_property(sapnwrfc_connection_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "errorInfo", sizeof("errorInfo") - 1, &info);

    zval_ptr_dtor(&info);
    zend_string_release(message);

    zend_throw_exception_object(&ex);
    zend_restore_error_handling(&zeh);
}


void sapnwrfc_throw_function_exception_ex(char *msg, ...)
{
    va_list args;
    char *buf;

    va_start(args, msg);
    vspprintf(&buf, 0, msg, args);
    va_end(args);

    zend_throw_exception(sapnwrfc_function_exception_ce, buf, 0);

    efree(buf);
}

void sapnwrfc_throw_function_exception(RFC_ERROR_INFO error_info, char *msg, ...)
{
    va_list args;
    zend_string *message;
    zval info;
    zval ex;
    zend_error_handling zeh;

    va_start(args, msg);
    message = vstrpprintf(0, msg, args);
    va_end(args);

    array_init(&info);

    zend_replace_error_handling(EH_THROW, sapnwrfc_function_exception_ce, &zeh);

    object_init_ex(&ex, sapnwrfc_function_exception_ce);

    zend_update_property_string(sapnwrfc_function_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "message", sizeof("message") - 1, ZSTR_VAL(message));
    zend_update_property_long(sapnwrfc_function_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "code", sizeof("code") - 1, error_info.code);

    // populate errorInfo array
    add_assoc_long(&info, "code", error_info.code);
    add_assoc_str(&info, "key", sapuc_to_zend_string(error_info.key));
    add_assoc_str(&info, "message", sapuc_to_zend_string(error_info.message));

    switch(error_info.group) {
        case LOGON_FAILURE:                   // Error message raised when logon fails
        case COMMUNICATION_FAILURE:           // Problems with the network connection (or backend broke down and killed the connection)
        case EXTERNAL_RUNTIME_FAILURE:        // Problems in the RFC runtime of the external program (i.e "this" library)
            // no additional properties, just the generic one's from above
            break;
        case ABAP_APPLICATION_FAILURE:        // ABAP Exception raised in ABAP function modules
        case ABAP_RUNTIME_FAILURE:            // ABAP Message raised in ABAP function modules or in ABAP runtime of the backend (e.g Kernel)
        case EXTERNAL_APPLICATION_FAILURE:    // Problems in the external program (e.g in the external server implementation)
        case EXTERNAL_AUTHORIZATION_FAILURE:  // Problems raised in the authorization check handler provided by the external server implementation
            add_assoc_str(&info, "abapMsgClass", sapuc_to_zend_string(error_info.abapMsgClass));
            add_assoc_str(&info, "abapMsgType", sapuc_to_zend_string(error_info.abapMsgType));
            add_assoc_str(&info, "abapMsgNumber", sapuc_to_zend_string(error_info.abapMsgNumber));
            add_assoc_str(&info, "abapMsgV1", sapuc_to_zend_string(error_info.abapMsgV1));
            add_assoc_str(&info, "abapMsgV2", sapuc_to_zend_string(error_info.abapMsgV2));
            add_assoc_str(&info, "abapMsgV3", sapuc_to_zend_string(error_info.abapMsgV3));
            add_assoc_str(&info, "abapMsgV4", sapuc_to_zend_string(error_info.abapMsgV4));
            break;
        case RFC_OK: // LCOV_EXCL_START
            zend_error(E_ERROR, "Internal error: exception handler called for RFC_OK");
            zend_restore_error_handling(&zeh);

            zend_string_release(message);
            return;
            // LCOV_EXCL_STOP
        default:
            zend_error(E_ERROR, "Internal error: unknown error group");
            zend_restore_error_handling(&zeh);

            zend_string_release(message);
            return;
    }

    zend_update_property(sapnwrfc_function_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(ex), "errorInfo", sizeof("errorInfo") - 1, &info);

    zval_ptr_dtor(&info);
    zend_string_release(message);

    zend_throw_exception_object(&ex);
    zend_restore_error_handling(&zeh);
}

PHP_METHOD(Exception, getErrorInfo)
{
    zval tmp;
    zval *error_info;

    zend_parse_parameters_none();

    error_info = zend_read_property(sapnwrfc_exception_ce, SAPNWRFC_EXC_Z_OBJ_OR_ZVAL_P(getThis()), "errorInfo", sizeof("errorInfo") - 1, 0, &tmp);

    RETURN_ZVAL(error_info, 1, 0);
}

void sapnwrfc_register_exceptions()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\Exception", sapnwrfc_exception_class_functions);
    sapnwrfc_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    zend_declare_property_null(sapnwrfc_exception_ce, "errorInfo", sizeof("errorInfo") - 1, ZEND_ACC_PROTECTED);

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\ConnectionException", NULL);
    sapnwrfc_connection_exception_ce = zend_register_internal_class_ex(&ce, sapnwrfc_exception_ce);
    sapnwrfc_connection_exception_ce->ce_flags |= ZEND_ACC_FINAL;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\FunctionCallException", NULL);
    sapnwrfc_function_exception_ce = zend_register_internal_class_ex(&ce, sapnwrfc_exception_ce);
    sapnwrfc_function_exception_ce->ce_flags |= ZEND_ACC_FINAL;
}
