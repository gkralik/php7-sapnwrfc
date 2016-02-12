/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2015 Gregor Kralik                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Gregor Kralik <g.kralik@gmail.com>                           |
  +----------------------------------------------------------------------+
*/

#include "sapnwrfc.h"

#ifndef STRING_HELPER_H_
#define STRING_HELPER_H_

SAP_UC *zval_to_sapuc(zval *zv);
SAP_UC *zend_string_to_sapuc(zend_string *str);

zval sapuc_to_zval_len(SAP_UC *str, unsigned len);
zend_string *sapuc_to_zend_string(SAP_UC *str);

#endif /* STRING_HELPER_H_ */
