/**
 * Copyright (c) 2016 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#include "sapnwrfc.h"

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

zend_class_entry *sapnwrfc_exception_ce;
zend_class_entry *sapnwrfc_connection_exception_ce;
zend_class_entry *sapnwrfc_function_exception_ce;

PHP_METHOD(Exception, getErrorInfo);

void sapnwrfc_throw_connection_exception(RFC_ERROR_INFO error_info, char *msg, ...);
void sapnwrfc_throw_function_exception(RFC_ERROR_INFO error_info, char *msg, ...);

void sapnwrfc_register_exceptions();

#endif /* _EXCEPTIONS_H */
