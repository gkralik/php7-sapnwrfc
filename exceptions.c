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

void sapnwrfc_throw_connection_exception_ex(char *msg, int code, zend_string *rfcKey, zend_string *rfcMessage)
{
    zval connection_exception;
    zend_string *exception_message;

    exception_message = zend_string_init(msg, strlen(msg), 0);

    TSRMLS_FETCH();

    zend_replace_error_handling(EH_THROW, zend_ce_exception, NULL);

    object_init_ex(&connection_exception, sapnwrfc_connection_exception_ce);
    zend_update_property_string(sapnwrfc_connection_exception_ce, &connection_exception, "message", sizeof("message") - 1, ZSTR_VAL(exception_message) TSRMLS_CC);
    zend_update_property_long(sapnwrfc_connection_exception_ce, &connection_exception, "code", sizeof("code") - 1, code TSRMLS_CC);
    zend_update_property_string(sapnwrfc_connection_exception_ce, &connection_exception, "rfcKey", sizeof("rfcKey") - 1, ZSTR_VAL(rfcKey) TSRMLS_CC);
    zend_update_property_string(sapnwrfc_connection_exception_ce, &connection_exception, "rfcMessage", sizeof("rfcMessage") - 1, ZSTR_VAL(rfcMessage) TSRMLS_CC);

    zend_throw_exception_object(&connection_exception TSRMLS_CC);

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

void sapnwrfc_throw_connection_exception(char *msg, int code)
{
    sapnwrfc_throw_connection_exception_ex(msg, code,
        zend_string_init("", strlen(""), 0),
        zend_string_init("", strlen(""), 0));
}

void sapnwrfc_throw_function_exception_ex(char *msg, int code, zend_string *rfcKey, zend_string *rfcMessage)
{
    zval function_exception;
    zend_string *exception_message;

    exception_message = zend_string_init(msg, strlen(msg), 0);

    TSRMLS_FETCH();

    zend_replace_error_handling(EH_THROW, zend_ce_exception, NULL);

    object_init_ex(&function_exception, sapnwrfc_function_exception_ce);
    zend_update_property_string(sapnwrfc_function_exception_ce, &function_exception, "message", sizeof("message") - 1, ZSTR_VAL(exception_message) TSRMLS_CC);
    zend_update_property_long(sapnwrfc_function_exception_ce, &function_exception, "code", sizeof("code") - 1, code TSRMLS_CC);
    zend_update_property_string(sapnwrfc_function_exception_ce, &function_exception, "rfcKey", sizeof("rfcKey") - 1, ZSTR_VAL(rfcKey) TSRMLS_CC);
    zend_update_property_string(sapnwrfc_function_exception_ce, &function_exception, "rfcMessage", sizeof("rfcMessage") - 1, ZSTR_VAL(rfcMessage) TSRMLS_CC);

    zend_throw_exception_object(&function_exception TSRMLS_CC);

    zend_replace_error_handling(EH_NORMAL, NULL, NULL);
}

void sapnwrfc_throw_function_exception(char *msg, int code)
{
    sapnwrfc_throw_function_exception_ex(msg, code,
        zend_string_init("", strlen(""), 0),
        zend_string_init("", strlen(""), 0));
}

static void sapnwrfc_register_connection_exception_object()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\ConnectionException", NULL);
    sapnwrfc_connection_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    sapnwrfc_connection_exception_ce->ce_flags |= ZEND_ACC_FINAL;
    zend_declare_property_string(sapnwrfc_connection_exception_ce, "rfcKey", sizeof("rfcKey") - 1, "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(sapnwrfc_connection_exception_ce, "rfcMessage", sizeof("rfcMessage") - 1, "", ZEND_ACC_PUBLIC);
}

static void sapnwrfc_register_function_exception_object()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\FunctionCallException", NULL);
    sapnwrfc_function_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    sapnwrfc_function_exception_ce->ce_flags |= ZEND_ACC_FINAL;
    zend_declare_property_string(sapnwrfc_function_exception_ce, "rfcKey", sizeof("rfcKey") - 1, "", ZEND_ACC_PUBLIC);
    zend_declare_property_string(sapnwrfc_function_exception_ce, "rfcMessage", sizeof("rfcMessage") - 1, "", ZEND_ACC_PUBLIC);
}

void sapnwrfc_register_exceptions()
{
    sapnwrfc_register_connection_exception_object();
    sapnwrfc_register_function_exception_object();
}
