/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#include "sapnwrfc.h"

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#if PHP_VERSION_ID >= 80000
#   define SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(x) Z_OBJ(x)
#   define SAPNWRFC_EXC_Z_OBJ_OR_ZVAL_P(x) Z_OBJ_P(x)
#else
#   define SAPNWRFC_EXC_Z_OBJ_OR_ZVAL(x) &x
#   define SAPNWRFC_EXC_Z_OBJ_OR_ZVAL_P(x) x
#endif

PHP_METHOD(Exception, getErrorInfo);

void sapnwrfc_throw_connection_exception(RFC_ERROR_INFO error_info, char *msg, ...);
void sapnwrfc_throw_function_exception_ex(char *msg, ...);
void sapnwrfc_throw_function_exception(RFC_ERROR_INFO error_info, char *msg, ...);

void sapnwrfc_register_exceptions();

#endif /* _EXCEPTIONS_H */
