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

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_sapnwrfc_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_sapnwrfc_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "sapnwrfc", arg);

	RETURN_STR(strg);
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(sapnwrfc)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(sapnwrfc)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
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
	PHP_FE(confirm_sapnwrfc_compiled,	NULL)		/* For testing, remove later. */
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
