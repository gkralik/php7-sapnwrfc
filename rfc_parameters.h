/**
 * Copyright (c) 2016 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik@gmail.com>
 */

#ifndef _RFC_PARAMETERS_H
#define _RFC_PARAMETERS_H

typedef enum { RFC_SET_VALUE_ERROR, RFC_SET_VALUE_OK} rfc_set_value_return_t;

rfc_set_value_return_t rfc_set_char_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_date_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_time_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_byte_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max);
rfc_set_value_return_t rfc_set_table_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_num_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max);
rfc_set_value_return_t rfc_set_float_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_int_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_int1_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_int2_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_structure_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_string_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);
rfc_set_value_return_t rfc_set_xstring_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value);

rfc_set_value_return_t rfc_set_table_row(RFC_STRUCTURE_HANDLE row, zval *value);
rfc_set_value_return_t rfc_set_field_value(DATA_CONTAINER_HANDLE, RFC_FIELD_DESC field_desc, zval *value);

rfc_set_value_return_t rfc_set_parameter_value(RFC_FUNCTION_HANDLE function_handle,
                               RFC_FUNCTION_DESC_HANDLE function_desc_handle,
                               zend_string *name,
                               zval *value);


zval rfc_get_char_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, unsigned len);
zval rfc_get_date_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_time_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_byte_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, unsigned len);
zval fc_get_table_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_num_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, unsigned len);
zval rfc_get_float_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_int_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_int1_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_int2_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_structure_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_string_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);
zval rfc_get_xstring_value(DATA_CONTAINER_HANDLE h, SAP_UC *name);

zval rfc_get_table_line(RFC_STRUCTURE_HANDLE line);
zval rfc_get_field_value(RFC_STRUCTURE_HANDLE h, RFC_FIELD_DESC field_desc);

zval rfc_get_parameter_value(RFC_FUNCTION_HANDLE function_handle,
                               RFC_FUNCTION_DESC_HANDLE function_desc_handle,
                               zend_string *name);

#endif /* _RFC_PARAMETERS_H */
