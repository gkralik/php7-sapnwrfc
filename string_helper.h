/**
 * Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Author: Gregor Kralik <g.kralik (at) gmail.com>
 */

#include "sapnwrfc.h"

#ifndef _STRING_HELPER_H
#define _STRING_HELPER_H

SAP_UC *zval_to_sapuc(zval *zv);
SAP_UC *zend_string_to_sapuc(zend_string *str);

zval sapuc_to_zval_len_ex(SAP_UC *str, unsigned len, unsigned char rtrim);
zend_string *sapuc_to_zend_string(SAP_UC *str);

#define sapuc_to_zval_len(str, len) \
    sapuc_to_zval_len_ex(str, len, 0)

#endif /* _STRING_HELPER_H */
