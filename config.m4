dnl Copyright (c) 2016 - 2021 Gregor Kralik <g.kralik (at) gmail.com>
dnl
dnl This source code is licensed under the MIT license found in the
dnl LICENSE file in the root directory of this source tree.
dnl
dnl Author: Gregor Kralik <g.kralik@gmail.com>

dnl config.m4 for extension sapnwrfc

PHP_ARG_WITH(sapnwrfc, for SAP NW RFC support,
dnl Make sure that the comment is aligned:
[  --with-sapnwrfc         Include SAP NW RFC support])

if test "$PHP_SAPNWRFC" != "no"; then
	dnl # --with-sapnwrfc -> check with-path
	SEARCH_PATH="/usr/sap/nwrfcsdk /usr/local/sap/nwrfcsdk /usr/local/nwrfcsdk /opt/nwrfcsdk"
	SEARCH_FOR="/include/sapnwrfc.h"
	if test -r $PHP_SAPNWRFC/$SEARCH_FOR; then # path given as parameter
		SAPNWRFC_DIR=$PHP_SAPNWRFC
	else # search default path list
		AC_MSG_CHECKING([for sapnwrfc files in default path])
		for i in $SEARCH_PATH ; do
			if test -r $i/$SEARCH_FOR; then
				SAPNWRFC_DIR=$i
				AC_MSG_RESULT(found in $i)
			 fi
		 done
	fi

	if test -z "$SAPNWRFC_DIR"; then
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Please install the SAP NW RFC SDK - missing sapnwrfc.h])
	fi

	# add include path
	SAPNWRFC_INCLUDE_DIR=$SAPNWRFC_DIR/include
	PHP_ADD_INCLUDE($SAPNWRFC_INCLUDE_DIR)

	SDK_LIB_NAMES="sapnwrfc sapucum"
	SDK_LIB_SUFFIX=".so"

	case $host_alias in
		*darwin*)
			SDK_LIB_SUFFIX=".dylib"
			;;
	esac

	# check for libraries
	for f in $SDK_LIB_NAMES ; do
		AC_MSG_CHECKING([for lib$f$SDK_LIB_SUFFIX])

		if test ! -f $SAPNWRFC_DIR/lib/lib$f$SDK_LIB_SUFFIX; then
			AC_MSG_RESULT([not found])
			AC_MSG_ERROR([SAP NW RFC shared library lib$f$SDK_LIB_SUFFIX missing])
		fi

		AC_MSG_RESULT([found])
		PHP_ADD_LIBRARY_WITH_PATH($f, $SAPNWRFC_DIR/lib, SAPNWRFC_SHARED_LIBADD)
	done

	PHP_SUBST(SAPNWRFC_SHARED_LIBADD)

	# check for uchar.h
	AC_CHECK_HEADER([uchar.h], [], [
		AC_MSG_NOTICE([using bundled uchar.h])
		PHP_ADD_INCLUDE(ext)
	])

	# check for RfcGetPartnerSSOTicket
	# not needed, has always been available
	#AC_CHECK_FUNC([RfcGetPartnerSSOTicket], [
	#		AC_DEFINE([HAVE_RFC_GET_PARTNER_SSO_TICKET], [1], [Define to 1 if RfcGetPartnerSSOTicket is available])
	#	]
	#)
	# set up CFLAGS
	PHP_SAPNWRFC_CFLAGS="-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -std=gnu11 -DSAPwithUNICODE -Wall"

	PHP_BUILD_SHARED()

	PHP_NEW_EXTENSION(sapnwrfc, sapnwrfc.c exceptions.c string_helper.c rfc_parameters.c, $ext_shared,, $PHP_SAPNWRFC_CFLAGS)
	PHP_ADD_MAKEFILE_FRAGMENT()		
fi
