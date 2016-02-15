dnl Copyright (c) 2016 Gregor Kralik <g.kralik (at) gmail.com>
dnl
dnl This source code is licensed under the MIT license found in the
dnl LICENSE file in the root directory of this source tree.
dnl
dnl Author: Gregor Kralik <g.kralik@gmail.com>

dnl config.m4 for extension sapnwrfc

dnl
dnl PHP_ADD_SOURCES_X(source-path, sources[, special-flags[, target-var[, shared[, special-post-flags]]]])
dnl
dnl Overwrites the PHP provided PHP_ADD_SOURCES_X.
dnl This is necessary because SAP NW RFC requires some additional steps to
dnl be taken during compile time.
dnl See SAP notes 763741 and 1056696 for details.
dnl
dnl The code is mostly the same as in
dnl https://github.com/piersharding/php-sapnwrfc/blob/9874b77ffc878c0330d560d82d3d50eaa843b828/config.m4
dnl
AC_DEFUN([PHP_ADD_SOURCES_X],[
	dnl relative to source- or build-directory?
	dnl ac_srcdir/ac_bdir include trailing slash
	case $1 in
	""[)] ac_srcdir="$abs_srcdir/"; unset ac_bdir; ac_inc="-I. -I$abs_srcdir" ;;
	/*[)] ac_srcdir=`echo "$1"|cut -c 2-`"/"; ac_bdir=$ac_srcdir; ac_inc="-I$ac_bdir -I$abs_srcdir/$ac_bdir" ;;
	*[)] ac_srcdir="$abs_srcdir/$1/"; ac_bdir="$1/"; ac_inc="-I$ac_bdir -I$ac_srcdir" ;;
	esac

	dnl how to build .. shared or static?
	ifelse($5,yes,_PHP_ASSIGN_BUILD_VARS(shared),_PHP_ASSIGN_BUILD_VARS(php))

	dnl iterate over the sources
	old_IFS=[$]IFS
	for ac_src in $2; do
		dnl remove the suffix
		IFS=.
		set $ac_src
		ac_obj=[$]1
		IFS=$old_IFS

		dnl append to the array which has been dynamically chosen at m4 time
		$4="[$]$4 [$]ac_bdir[$]ac_obj.lo"

		dnl set the flags needed for compiling a SAP NW RFC application
		dnl NOTE: these are for a linux environment
		nwrfc_extra_flags="-std=c99 -DNDEBUG -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -DSAPonUNIX -DSAPwithUNICODE -D__NO_MATH_INLINES -DSAPwithTHREADS -DSAPonLIN -minline-all-stringops -g -fno-strict-aliasing -fno-omit-frame-pointer -fexceptions -funsigned-char -Wall -Wno-uninitialized -Wno-long-long -Wcast-align -pthread -fPIC"

		dnl the SAP NW RFC SDK requires a preprocessing step for unicode things
		dnl refer to the SAP notes given above for details
		shared_c_pre_1='rm -f $<.ii $<.i && $(CC) -E '
		shared_c_pre_2=' $< -o $<.ii && perl ./scripts/u16lit.pl -le $<.ii && $(LIBTOOL) --mode=compile $(CC) '
		nwrfc_ac_comp="$shared_c_pre_1 $3 $ac_inc $b_c_meta $nwrfc_extra_flags $shared_c_pre_2 $3 $ac_inc $b_c_meta $nwrfc_extra_flags -c $ac_srcdir$ac_src.i -o $ac_bdir$ac_obj.$b_lo $6$b_c_post"

		dnl choose the right compiler/flags/etc. for the source-file
		case $ac_src in
			*.c[)] ac_comp="$nwrfc_ac_comp" ;;
			*.s[)] ac_comp="$b_c_pre $3 $ac_inc $b_c_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_c_post" ;;
			*.S[)] ac_comp="$b_c_pre $3 $ac_inc $b_c_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_c_post" ;;
			*.cpp|*.cc|*.cxx[)] ac_comp="$b_cxx_pre $3 $ac_inc $b_cxx_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_cxx_post" ;;
		esac

		dnl create a rule for the object/source combo
		dnl NOTE: $ac_comp MUST be indented with a TAB - make is picky ;)
		cat >>Makefile.objects<<EOF
$ac_bdir[$]ac_obj.lo: $ac_srcdir[$]ac_src
	$ac_comp
EOF
	done
])

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
	PHP_ADD_INCLUDE($SAPNWRFC_DIR/include)

	# check for library
	if test ! -f $SAPNWRFC_DIR/lib/libsapnwrfc.so; then
		AC_MSG_ERROR(SAP NW RFC shared library libsapnwrfc.so missing)
	fi
	PHP_ADD_LIBRARY_WITH_PATH(sapnwrfc, $SAPNWRFC_DIR/lib, SAPNWRFC_SHARED_LIBADD)
	PHP_ADD_LIBRARY_WITH_PATH(sapucum, $SAPNWRFC_DIR/lib, SAPNWRFC_SHARED_LIBADD)

	PHP_SUBST(SAPNWRFC_SHARED_LIBADD)

	PHP_BUILD_SHARED()

	PHP_NEW_EXTENSION(sapnwrfc, sapnwrfc.c exceptions.c string_helper.c rfc_parameters.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
