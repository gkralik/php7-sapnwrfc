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

#ifndef RFC_PARAMETERS_H
#define RFC_PARAMETERS_H

unsigned int rfc_set_char_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_date_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_bcd_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_time_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_byte_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max);
unsigned int rfc_set_table_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_num_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max);
unsigned int rfc_set_float_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_int_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_int1_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_int2_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_structure_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_string_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
unsigned int rfc_set_xstring_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);

RFC_RC rfc_set_parameter_value(RFC_FUNCTION_HANDLE function_handle,
                               RFC_FUNCTION_DESC_HANDLE function_desc_handle,
                               zend_string *name,
                               zval *value);

#endif /* RFC_PARAMETERS_H */
