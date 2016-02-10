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

#include "exceptions.h"
#include "string_helper.h"
#include "rfc_parameters.h"

#include "sapnwrfc.h"


rfc_set_value_return_t rfc_set_char_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set char parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);
    rc = RfcSetChars(h, name, value_u, strlenU(value_u), &error_info);
    free((char *)value_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set char parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_date_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;
    RFC_DATE value_date;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set date parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_STRLEN_P(value) != 8) {
        sapnwrfc_throw_function_exception_ex("Failed to set date parameter: invalid format",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);
    memcpy((char *)value_date, (char *)value_u, 16);
    free((char *)value_u);

    rc = RfcSetDate(h, name, value_date, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set date parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_bcd_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set BCD parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);
    rc = RfcSetString(h, name, value_u, strlenU(value_u), &error_info);
    free((char *)value_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set BCD parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_time_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;
    RFC_TIME value_time;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set time parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_STRLEN_P(value) != 6) {
        sapnwrfc_throw_function_exception_ex("Failed to set time parameter: invalid format",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);
    memcpy((char *)value_time, (char *)value_u, 12);
    free((char *)value_u);

    rc = RfcSetTime(h, name, value_time, &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set time parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_byte_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set byte parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_STRLEN_P(value) > max) {
        sapnwrfc_throw_function_exception_ex("Failed to set byte parameter: too long",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetBytes(h, name, (SAP_RAW *)Z_STRVAL_P(value), Z_STRLEN_P(value), &error_info);
    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set byte parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_table_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_ERROR_INFO error_info;
    RFC_STRUCTURE_HANDLE table_row;
    HashTable *value_hash;
    zend_string *key;
    zval *val;

    if (Z_TYPE_P(value) != IS_ARRAY) {
        sapnwrfc_throw_function_exception_ex("Failed to set table parameter: expected array",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_hash = Z_ARRVAL_P(value);
    ZEND_HASH_FOREACH_STR_KEY_VAL(value_hash, key, val) {
        table_row = RfcAppendNewRow(h, &error_info);
        if (table_row == NULL) {
            sapnwrfc_throw_function_exception_ex("Failed to append table row",
                                                 error_info.code,
                                                 sapuc_to_zend_string(error_info.key),
                                                 sapuc_to_zend_string(error_info.message));
            return RFC_SET_VALUE_ERROR;
        }

        if (rfc_set_table_row(table_row, val) == RFC_SET_VALUE_ERROR) {
            // or in rfc_set_table_row()?
            sapnwrfc_throw_function_exception_ex("Failed to set table row",
                                                 error_info.code,
                                                 sapuc_to_zend_string(error_info.key),
                                                 sapuc_to_zend_string(error_info.message));
            return RFC_SET_VALUE_ERROR;
        }
    } ZEND_HASH_FOREACH_END();

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_num_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value, unsigned max)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set num parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_STRLEN_P(value) > max) {
        sapnwrfc_throw_function_exception_ex("Failed to set num parameter: too long",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);

    rc = RfcSetNum(h, name, (RFC_NUM *)value_u, strlenU(value_u), &error_info);
    free((char *)value_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set num parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_float_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_DOUBLE) {
        sapnwrfc_throw_function_exception_ex("Failed to set float parameter: expected double",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetFloat(h, name, (RFC_FLOAT)Z_DVAL_P(value), &error_info);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set float parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_int_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_LONG) {
        sapnwrfc_throw_function_exception_ex("Failed to set int parameter: expected long",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetInt(h, name, (RFC_INT)Z_LVAL_P(value), &error_info);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set int parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_int1_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_LONG) {
        sapnwrfc_throw_function_exception_ex("Failed to set int1 parameter: expected long",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_LVAL_P(value) > 255) {
        sapnwrfc_throw_function_exception_ex("Failed to set int1 parameter: too big (>255)",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetInt1(h, name, (RFC_INT1)Z_LVAL_P(value), &error_info);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set int1 parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_int2_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_LONG) {
        sapnwrfc_throw_function_exception_ex("Failed to set int2 parameter: expected long",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    if (Z_LVAL_P(value) > 65535) {
        sapnwrfc_throw_function_exception_ex("Failed to set int2 parameter: too big (>65535)",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetInt2(h, name, (RFC_INT2)Z_LVAL_P(value), &error_info);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set int2 parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_structure_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    zend_error(E_ERROR, "RFCTYPE_STRUCTURE not implemented\n");
    return RFC_SET_VALUE_ERROR;
}

rfc_set_value_return_t rfc_set_string_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    SAP_UC *value_u;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set string parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_u = zval_to_sapuc(value);
    rc = RfcSetString(h, name, value_u, strlenU(value_u), &error_info);
    free((char *)value_u);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set string parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_xstring_value(DATA_CONTAINER_HANDLE h, SAP_UC *name, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;

    if (Z_TYPE_P(value) != IS_STRING) {
        sapnwrfc_throw_function_exception_ex("Failed to set xstring parameter: expected string",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    rc = RfcSetXString(h, name, (SAP_RAW *)Z_STRVAL_P(value), Z_STRLEN_P(value), &error_info);

    if (rc != RFC_OK) {
        sapnwrfc_throw_function_exception_ex("Failed to set xstring parameter",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_table_row(RFC_STRUCTURE_HANDLE row, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    RFC_FIELD_DESC field_desc;
    RFC_TYPE_DESC_HANDLE type_desc_handle;
    SAP_UC * field_name_u;
    HashTable *value_hash;
    zend_string *str_index;
    ulong num_key;
    zval *val;

    if (Z_TYPE_P(value) != IS_ARRAY) {
        sapnwrfc_throw_function_exception_ex("Failed to set table row: expected array",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    type_desc_handle = RfcDescribeType(row, &error_info);
    if (type_desc_handle == NULL) {
        sapnwrfc_throw_function_exception_ex("Failed to get row type",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));
        return RFC_SET_VALUE_ERROR;
    }

    value_hash = Z_ARRVAL_P(value);

    ZEND_HASH_FOREACH_KEY_VAL(value_hash, num_key, str_index, val) {
        if (!str_index) { // not string
            sapnwrfc_throw_function_exception("All parameter keys must be strings.", 0);
            return RFC_SET_VALUE_ERROR;
        }

        rc = RfcGetFieldDescByName(type_desc_handle, (field_name_u = zend_string_to_sapuc(str_index)), &field_desc, &error_info);
        if (rc != RFC_OK) {
            free((char *)field_name_u);
            sapnwrfc_throw_function_exception_ex("Failed to get field description",
                                                 error_info.code,
                                                 sapuc_to_zend_string(error_info.key),
                                                 sapuc_to_zend_string(error_info.message));
            return RFC_SET_VALUE_ERROR;
        }

        memcpy(field_desc.name, field_name_u, sizeof(RFC_ABAP_NAME)); // RFC_CHAR [30+1]
        free((char *)field_name_u);

        if (rfc_set_field_value(row, field_desc, val) == RFC_SET_VALUE_ERROR) {
            sapnwrfc_throw_function_exception_ex("Failed to set field value",
                                                 error_info.code,
                                                 sapuc_to_zend_string(error_info.key),
                                                 sapuc_to_zend_string(error_info.message));
            return RFC_SET_VALUE_ERROR;
        }
    } ZEND_HASH_FOREACH_END();

    return RFC_SET_VALUE_OK;
}

rfc_set_value_return_t rfc_set_field_value(DATA_CONTAINER_HANDLE h, RFC_FIELD_DESC field_desc, zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    RFC_TABLE_HANDLE table_handle;
    int ret = RFC_SET_VALUE_OK;

    switch(field_desc.type) {
        case RFCTYPE_CHAR:
            ret = rfc_set_char_value(h, field_desc.name, value);
            break;
        case RFCTYPE_DATE:
            ret = rfc_set_date_value(h, field_desc.name, value);
            break;
        case RFCTYPE_BCD:
            ret = rfc_set_bcd_value(h, field_desc.name, value);
            break;
        case RFCTYPE_TIME:
            ret = rfc_set_time_value(h, field_desc.name, value);
            break;
        case RFCTYPE_BYTE:
            ret = rfc_set_byte_value(h, field_desc.name, value, field_desc.nucLength);
            break;
        case RFCTYPE_TABLE:
            rc = RfcGetTable(h, field_desc.name, &table_handle, &error_info);
            if (rc != RFC_OK) {
                sapnwrfc_throw_function_exception_ex("Failed to get table handle",
                                                     error_info.code,
                                                     sapuc_to_zend_string(error_info.key),
                                                     sapuc_to_zend_string(error_info.message));

                return RFC_SET_VALUE_ERROR;
            }

            ret = rfc_set_table_value(table_handle, field_desc.name, value);
            break;
        case RFCTYPE_NUM:
            ret = rfc_set_num_value(h, field_desc.name, value, field_desc.nucLength);
            break;
        case RFCTYPE_FLOAT:
            ret = rfc_set_float_value(h, field_desc.name, value);
            break;
        case RFCTYPE_INT:
            ret = rfc_set_int_value(h, field_desc.name, value);
            break;
        case RFCTYPE_INT1:
            ret = rfc_set_int1_value(h, field_desc.name, value);
            break;
        case RFCTYPE_INT2:
            ret = rfc_set_int2_value(h, field_desc.name, value);
            break;
        case RFCTYPE_STRUCTURE:
            ret = rfc_set_structure_value(h, field_desc.name, value);
            break;
        case RFCTYPE_STRING:
            ret = rfc_set_string_value(h, field_desc.name, value);
            break;
        case RFCTYPE_XSTRING:
            ret = rfc_set_xstring_value(h, field_desc.name, value);
            break;
        default:
            zend_error(E_ERROR, "Unknown parameter type\n");
            ret = RFC_SET_VALUE_ERROR;
    }

    return ret;
}

rfc_set_value_return_t rfc_set_parameter_value(RFC_FUNCTION_HANDLE function_handle,
                               RFC_FUNCTION_DESC_HANDLE function_desc_handle,
                               zend_string *name,
                               zval *value)
{
    RFC_RC rc = RFC_OK;
    RFC_ERROR_INFO error_info;
    RFC_PARAMETER_DESC parameter_desc;
    RFC_TABLE_HANDLE table_handle;
    SAP_UC *parameter_name_u;
    int ret = RFC_SET_VALUE_OK;

    // TODO if value is empty, skip

    rc = RfcGetParameterDescByName(function_desc_handle,
                                   (parameter_name_u = zend_string_to_sapuc(name)),
                                   &parameter_desc,
                                   &error_info);

    if (rc != RFC_OK) {
        free((char *)parameter_name_u);

        sapnwrfc_throw_function_exception_ex("Failed to get parameter description",
                                             error_info.code,
                                             sapuc_to_zend_string(error_info.key),
                                             sapuc_to_zend_string(error_info.message));

        return RFC_SET_VALUE_ERROR;
    }

    switch(parameter_desc.type) {
        case RFCTYPE_CHAR:
            ret = rfc_set_char_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_DATE:
            ret = rfc_set_date_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_BCD:
            ret = rfc_set_bcd_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_TIME:
            ret = rfc_set_time_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_BYTE:
            ret = rfc_set_byte_value(function_handle, parameter_name_u, value, parameter_desc.nucLength);
            break;
        case RFCTYPE_TABLE:
            rc = RfcGetTable(function_handle, parameter_name_u, &table_handle, &error_info);
            if (rc != RFC_OK) {
                free((char *)parameter_name_u);

                sapnwrfc_throw_function_exception_ex("Failed to get table handle",
                                                     error_info.code,
                                                     sapuc_to_zend_string(error_info.key),
                                                     sapuc_to_zend_string(error_info.message));

                return RFC_SET_VALUE_ERROR;
            }

            ret = rfc_set_table_value(table_handle, parameter_name_u, value);
            break;
        case RFCTYPE_NUM:
            ret = rfc_set_num_value(function_handle, parameter_name_u, value, parameter_desc.nucLength);
            break;
        case RFCTYPE_FLOAT:
            ret = rfc_set_float_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_INT:
            ret = rfc_set_int_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_INT1:
            ret = rfc_set_int1_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_INT2:
            ret = rfc_set_int2_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_STRUCTURE:
            ret = rfc_set_structure_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_STRING:
            ret = rfc_set_string_value(function_handle, parameter_name_u, value);
            break;
        case RFCTYPE_XSTRING:
            ret = rfc_set_xstring_value(function_handle, parameter_name_u, value);
            break;
        default:
            zend_error(E_ERROR, "Unknown parameter type\n");
            ret = RFC_SET_VALUE_ERROR;
    }

    free((char *)parameter_name_u);
    return ret;
}

zval *rfc_get_parameter_value(RFC_FUNCTION_HANDLE function_handle,
                               RFC_FUNCTION_DESC_HANDLE function_desc_handle,
                               zend_string *name)
{
}
