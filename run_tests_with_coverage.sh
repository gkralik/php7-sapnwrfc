#!/bin/sh

# report path
REPORT_PATH="coverage_html"
# gcov info file
INFO_FILE="sapnwrfc_test.info"
# path to NW RFC SDK libraries
NWRFCSDK_PATH="/nwrfcsdk"
# enable gcov
CFLAGS="-g -O0 --coverage -fprofile-arcs -ftest-coverage"
LDFLAGS="-lgcov"
# make sure libtool does not remove gcov data
# (see https://www.gnu.org/software/libtool/manual/html_node/Link-mode.html)
EXTRA_LDFLAGS="-precious-files-regex \.gcno$"

# cleanup
rm -f $INFO_FILE
make clean
phpize --clean

set -e

# configure
phpize
./configure --with-sapnwrfc=$NWRFCSDK_PATH CFLAGS="$CFLAGS" CXXFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" EXTRA_LDFLAGS="$EXTRA_LDFLAGS"

# reset counters
lcov --directory . --zerocounters

# build and run tests
make test NO_INTERACTION=1

# collect gcov data and build html report
lcov --directory . --capture --output-file $INFO_FILE
lcov --remove $INFO_FILE "tests/*" "/usr/*" --output-file $INFO_FILE
rm -rf $REPORT_PATH
genhtml -o $REPORT_PATH -t "php7-sapnwrfc test coverage report" --num-spaces 4 $INFO_FILE
