/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Gregor Kralik <g.kralik@gmail.com                            |
  +----------------------------------------------------------------------+
*/

#include "php.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "exceptions.h"
#include "string_helper.h"

#include "sapnwrfc.h"


void sapnwrfc_throw_connection_exception(RFC_ERROR_INFO error_info, char *msg, ...)
{
    va_list args;
    zend_string *message;
    zval info;
    zval ex;

    va_start(args, msg);
    message = vstrpprintf(0, msg, args);
    va_end(args);

    array_init(&info);

    zend_replace_error_handling(EH_THROW, sapnwrfc_connection_exception_ce, NULL);

    object_init_ex(&ex, sapnwrfc_connection_exception_ce);
    zend_update_property_string(sapnwrfc_connection_exception_ce, &ex, "message", sizeof("message") - 1, ZSTR_VAL(message) TSRMLS_CC);
    zend_update_property_long(sapnwrfc_connection_exception_ce, &ex, "code", sizeof("code") - 1, error_info.code TSRMLS_CC);

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
        case RFC_OK:
            zend_error(E_ERROR, "Internal error: exception handler called for RFC_OK");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            zend_string_release(message);
            return;
        default:
            zend_error(E_ERROR, "Internal error: unknown error group");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            zend_string_release(message);
            return;
    }

    zend_update_property(sapnwrfc_connection_exception_ce, &ex, "errorInfo", sizeof("errorInfo") - 1, &info TSRMLS_CC);

    zend_throw_exception_object(&ex TSRMLS_CC);

    zval_ptr_dtor(&info);
    zend_string_release(message);

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

void sapnwrfc_throw_function_exception(RFC_ERROR_INFO error_info, char *msg, ...)
{
    va_list args;
    zend_string *message;
    zval info;
    zval ex;

    va_start(args, msg);
    message = vstrpprintf(0, msg, args);
    va_end(args);

    array_init(&info);

    zend_replace_error_handling(EH_THROW, sapnwrfc_function_exception_ce, NULL);

    object_init_ex(&ex, sapnwrfc_function_exception_ce);
    zend_update_property_string(sapnwrfc_function_exception_ce, &ex, "message", sizeof("message") - 1, ZSTR_VAL(message) TSRMLS_CC);
    zend_update_property_long(sapnwrfc_function_exception_ce, &ex, "code", sizeof("code") - 1, error_info.code TSRMLS_CC);

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
        case RFC_OK:
            zend_error(E_ERROR, "Internal error: exception handler called for RFC_OK");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            zend_string_release(message);
            return;
        default:
            zend_error(E_ERROR, "Internal error: unknown error group");
            zend_replace_error_handling(EH_NORMAL, NULL, NULL);
            zend_string_release(message);
            return;
    }

    zend_update_property(sapnwrfc_function_exception_ce, &ex, "errorInfo", sizeof("errorInfo") - 1, &info TSRMLS_CC);

    zend_throw_exception_object(&ex TSRMLS_CC);

    zval_ptr_dtor(&info);
    zend_string_release(message);

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

void sapnwrfc_register_exceptions()
{
    zend_class_entry ce;
    zval error_info;

    //array_init(&error_info);
    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\Exception", NULL);
    sapnwrfc_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    zend_declare_property(sapnwrfc_exception_ce, "errorInfo", sizeof("errorInfo") - 1, &error_info, ZEND_ACC_PUBLIC);

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\ConnectionException", NULL);
    sapnwrfc_connection_exception_ce = zend_register_internal_class_ex(&ce, sapnwrfc_exception_ce);
    sapnwrfc_connection_exception_ce->ce_flags |= ZEND_ACC_FINAL;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\FunctionCallException", NULL);
    sapnwrfc_function_exception_ce = zend_register_internal_class_ex(&ce, sapnwrfc_exception_ce);
    sapnwrfc_function_exception_ce->ce_flags |= ZEND_ACC_FINAL;
}
