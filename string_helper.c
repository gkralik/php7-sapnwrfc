/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#include "php.h"
#include "sapnwrfc.h"


SAP_UC *zval_to_sapuc(zval *zv)
{
    RFC_ERROR_INFO error_info;
    SAP_UC *uc_str;
    unsigned int uc_str_size;
    unsigned int result_len = 0;

    uc_str_size = Z_STRLEN_P(zv) + 1;
    uc_str = (SAP_UC *)mallocU(uc_str_size);
    memsetU(uc_str, 0, uc_str_size);

    RfcUTF8ToSAPUC((RFC_BYTE *)Z_STRVAL_P(zv), Z_STRLEN_P(zv), uc_str, &uc_str_size, &result_len, &error_info);

    return uc_str;
}

SAP_UC *zend_string_to_sapuc(zend_string *str)
{

    zval zv;

    ZVAL_STR(&zv, str);

    return zval_to_sapuc(&zv);
}

zval sapuc_to_zval_len_ex(SAP_UC *uc_str, unsigned int uc_str_len, unsigned char rtrim)
{
    RFC_ERROR_INFO error_info;
    unsigned int utf8_size;
    unsigned int result_len = 0;
    char *utf8;
    zval zv;

    // try with 5 bytes per unicode character
    utf8_size = uc_str_len * 5 + 1;
    utf8 = (char *)malloc(utf8_size);
    utf8[0] = '\0';

    RfcSAPUCToUTF8(uc_str, uc_str_len, (RFC_BYTE *)utf8, &utf8_size, &result_len, &error_info);

    if (error_info.code != RFC_OK) {
        // buffer was too small
        free(utf8);

        ZVAL_NULL(&zv);
        return zv;
    }

    if (rtrim && result_len > 0) {
        int i = result_len-1;

        while (i >= 0 && isspace(utf8[i])) {
            i--;
        }

        utf8[i+1] = '\0';
        result_len = i+1;
    }

    ZVAL_STRINGL(&zv, utf8, result_len);
    free(utf8);

    return zv;

    // XXX: checking for RFC_BUFFER_TOO_SMALL and using the returned required size does not work
    //      -> even when calling RfcSAPUCToUTF8() with the returned lenght it always returns
    //         RFC_BUFFER_TOO_SMALL with an even bigger size requirement... ??
}

zend_string *sapuc_to_zend_string(SAP_UC *uc_str)
{
    zval zv;
    zend_string *out;

    unsigned uc_str_len = strlenU(uc_str);

    zv = sapuc_to_zval_len_ex(uc_str, uc_str_len, 0);

    out = zend_string_init(Z_STRVAL(zv), Z_STRLEN(zv), 0);
    zval_ptr_dtor(&zv); // release the zval

    return out;
}
