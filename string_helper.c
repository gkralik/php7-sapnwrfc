/**
 * Copyright (c) 2016 - 2020 Gregor Kralik <g.kralik (at) gmail.com>
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
    SAP_UC *sapuc;
    unsigned sapuc_size, result_length = 0;

    sapuc_size = Z_STRLEN_P(zv) + 1;
    sapuc = callocU(1, sapuc_size);
    RfcUTF8ToSAPUC((RFC_BYTE *) Z_STRVAL_P(zv), Z_STRLEN_P(zv), sapuc, &sapuc_size,
            &result_length, &error_info);
    return sapuc;
}

SAP_UC *zend_string_to_sapuc(zend_string *str)
{
    RFC_ERROR_INFO error_info;
    SAP_UC *sapuc;
    unsigned sapuc_size, result_length = 0;

    sapuc_size = ZSTR_LEN(str) + 1;
    sapuc = callocU(1, sapuc_size);

    RfcUTF8ToSAPUC((RFC_BYTE *) ZSTR_VAL(str), ZSTR_LEN(str), sapuc,
            &sapuc_size, &result_length, &error_info);
    return sapuc;
}

zval sapuc_to_zval_len_ex(SAP_UC *str, unsigned len, unsigned char rtrim)
{
    RFC_ERROR_INFO error_info;
    unsigned utf8size, result_length;
    char *utf8;
    zval out;

    utf8size = len * 2 + 1;
    utf8 = calloc(1, utf8size);

    result_length = 0;
    RfcSAPUCToUTF8(str, len, (RFC_BYTE *)utf8, &utf8size, &result_length, &error_info);

    if (rtrim && result_length > 0) {
        int i = result_length-1;

        while (i >= 0 && isspace(utf8[i])) {
            i--;
        }

        utf8[i+1] = '\0';
        result_length = i+1;
    }

    ZVAL_STRINGL(&out, utf8, result_length);
    free(utf8);

    return out;
}

zend_string *sapuc_to_zend_string(SAP_UC *str)
{
    RFC_ERROR_INFO error_info;
    unsigned utf8size, result_length;
    char *utf8;
    zend_string *out;

    utf8size = strlenU(str) * 2 + 1;
    utf8 = calloc(1, utf8size);

    result_length = 0;
    RfcSAPUCToUTF8(str, strlenU(str), (RFC_BYTE *)utf8, &utf8size, &result_length, &error_info);

    out = zend_string_init(utf8, result_length, 0);
    free(utf8);

    return out;
}
