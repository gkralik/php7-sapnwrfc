/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#ifndef _PHP_SAPNWRFC_H
#define _PHP_SAPNWRFC_H

extern zend_module_entry sapnwrfc_module_entry;
#define phpext_sapnwrfc_ptr &sapnwrfc_module_entry

#define PHP_SAPNWRFC_VERSION "2.0.0-beta2"
#ifdef PHP_WIN32
#    define PHP_SAPNWRFC_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#    define PHP_SAPNWRFC_API __attribute__ ((visibility("default")))
#else
#    define PHP_SAPNWRFC_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define SAPNWRFC_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(sapnwrfc, v)

#if defined(ZTS) && defined(COMPILE_DL_SAPNWRFC)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif    /* _PHP_SAPNWRFC_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
