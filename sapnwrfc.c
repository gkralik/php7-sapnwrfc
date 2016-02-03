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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_sapnwrfc.h"
#include "ext/spl/spl_exceptions.h"

#include "sapnwrfc.h"

// class entries
zend_class_entry *sapnwrfc_connection_ce;
zend_class_entry *sapnwrfc_connection_exception_ce;
zend_class_entry *sapnwrfc_functioncall_exception_ce;

zend_object_handlers sapnwrfc_connection_ce_handlers;

// connection object
typedef struct _sapnwrfc_connection_object {
    RFC_CONNECTION_HANDLE *rfc_handle;
    zend_object zobj;
} sapnwrfc_connection_object;

// connection exception object
typedef struct _sapnwrfc_connection_exception_object {
    zend_object zobj;
} sapnwrfc_connection_exception_object;

// function call exception object
typedef struct _sapnwrfc_functioncall_exception_object {
    zend_object zobj;
} sapnwrfc_functioncall_exception_object;

// forward declaration of class methods
PHP_METHOD(Connection, version);
PHP_METHOD(Connection, rfcVersion);

// class method tables
static zend_function_entry sapnwrfc_connection_class_functions[] = {
    PHP_ME(Connection, version, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(Connection, rfcVersion, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_FE_END
};

// connection object handlers
static zend_object *sapnwrfc_connection_object_create(zend_class_entry *ce)
{
    sapnwrfc_connection_object *obj;
    obj= ecalloc(1, sizeof(obj) + zend_object_properties_size(ce));
    obj->rfc_handle = ecalloc(1, sizeof(RFC_CONNECTION_HANDLE));

    zend_object_std_init(&obj->zobj, ce);
    object_properties_init(&obj->zobj, ce);

    obj->zobj.handlers = &sapnwrfc_connection_ce_handlers;

    return &obj->zobj;
}

static void sapnwrfc_connection_object_destroy(zend_object *object)
{
    sapnwrfc_connection_object *obj;

    obj = (sapnwrfc_connection_object *)((char *)object - XtOffsetOf(sapnwrfc_connection_object, zobj));

    /* we could do something with obj->rfc_handle here (closing it?), but
       not free it here */

    /* call __destruct() from userland */
    zend_objects_destroy_object(object);
}

static void sapnwrfc_connection_object_free(zend_object *object)
{
    sapnwrfc_connection_object *obj;

    obj = (sapnwrfc_connection_object *)((char *)object - XtOffsetOf(sapnwrfc_connection_object, zobj));

    /* free the RFC handle */
    efree(obj->rfc_handle);

    /* call Zend's free handler, which will free the object properties */
    zend_object_std_dtor(object);
}

// Connection class methods
PHP_METHOD(Connection, version)
{
    char *version;
    int len;

    len = spprintf(&version, 0, "%s", PHP_SAPNWRFC_VERSION);

    RETURN_STRINGL(version, len);
}

PHP_METHOD(Connection, rfcVersion)
{
    char *version;
    int len;
    unsigned int major, minor, patch;

    RfcGetVersion(&major, &minor, &patch);

    len = spprintf(&version, 0, "%d.%d.%d", major, minor, patch);

    RETURN_STRINGL(version, len);
}


static void register_sapnwrfc_connection_object()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\Connection", sapnwrfc_connection_class_functions);
    sapnwrfc_connection_ce = zend_register_internal_class(&ce);

    /* create handler */
    sapnwrfc_connection_ce->create_object = sapnwrfc_connection_object_create;

    memcpy(&sapnwrfc_connection_ce_handlers, zend_get_std_object_handlers(), sizeof(sapnwrfc_connection_ce_handlers));

    /* free handler */
    sapnwrfc_connection_ce_handlers.free_obj = sapnwrfc_connection_object_free;
    /* dtor handler */
    sapnwrfc_connection_ce_handlers.dtor_obj = sapnwrfc_connection_object_destroy;
    /* declare the offset of the internal object */
    sapnwrfc_connection_ce_handlers.offset = XtOffsetOf(sapnwrfc_connection_object, zobj);
}

static void register_sapnwrfc_connection_exception_object()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\ConnectionException", NULL);
    sapnwrfc_connection_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    sapnwrfc_connection_exception_ce->ce_flags |= ZEND_ACC_FINAL;
}

static void register_sapnwrfc_functioncall_exception_object()
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "SAPNWRFC\\FunctionCallException", NULL);
    sapnwrfc_functioncall_exception_ce = zend_register_internal_class_ex(&ce, spl_ce_RuntimeException);
    sapnwrfc_functioncall_exception_ce->ce_flags |= ZEND_ACC_FINAL;
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sapnwrfc)
{
    register_sapnwrfc_connection_object();
    register_sapnwrfc_connection_exception_object();
    register_sapnwrfc_functioncall_exception_object();

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

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(sapnwrfc)
{
#if defined(COMPILE_DL_SAPNWRFC) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(sapnwrfc)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(sapnwrfc)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "sapnwrfc support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ sapnwrfc_functions[]
 *
 * Every user visible function must have an entry in sapnwrfc_functions[].
 */
const zend_function_entry sapnwrfc_functions[] = {
	PHP_FE_END	/* Must be the last line in sapnwrfc_functions[] */
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
