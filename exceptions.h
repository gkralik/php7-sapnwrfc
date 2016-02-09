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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

zend_class_entry *sapnwrfc_connection_exception_ce;
zend_class_entry *sapnwrfc_function_exception_ce;

typedef struct _sapnwrfc_connection_exception_object {
    zend_object zobj;
} sapnwrfc_connection_exception_object;

typedef struct _sapnwrfc_function_exception_object {
    zend_object zobj;
} sapnwrfc_functioncall_exception_object;

void sapnwrfc_throw_connection_exception_ex(char *msg, int code, zend_string *rfcKey, zend_string *rfcMessage);
void sapnwrfc_throw_connection_exception(char *msg, int code);

void sapnwrfc_throw_function_exception_ex(char *msg, int code, zend_string *rfcKey, zend_string *rfcMessage);
void sapnwrfc_throw_function_exception(char *msg, int code);

void sapnwrfc_register_exceptions();

#endif /* EXCEPTIONS_H */
