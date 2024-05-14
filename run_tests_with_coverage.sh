#!/bin/sh

###
# Build and run tests with coverage.
#
# Environment variables:
#   - `NWRFCSDK_PATH`: must contain the path to the NW RFC SDK.
#   - `PHPIZE`: can be used to build for a different PHP version.
#   - `SAPNWRFC_ONLINE`: set to 1 to run online tests.
#
###

if [[ ! -d "${NWRFCSDK_PATH}" ]]; then
  echo "NWRFCSDK_PATH must be set to the SDK path."
  exit 1
fi

set -o xtrace

# phpize path
PHPIZE="${PHPIZE:-phpize}"

# report path
REPORT_PATH="coverage_html"
# gcov info file
INFO_FILE="sapnwrfc_test.info"

# enable gcov
CFLAGS="-g -O0 --coverage -fprofile-arcs -ftest-coverage"
LDFLAGS="--coverage -lgcov"
# make sure libtool does not remove gcov data
# (see https://www.gnu.org/software/libtool/manual/html_node/Link-mode.html)
EXTRA_LDFLAGS="-precious-files-regex \.gcno$"

# cleanup
rm -f $INFO_FILE
rm -rf $REPORT_PATH
make clean
$PHPIZE --clean

set -e

# configure
$PHPIZE
./configure --with-sapnwrfc=$NWRFCSDK_PATH CFLAGS="$CFLAGS" CXXFLAGS="$CFLAGS" LDFLAGS="$LDFLAGS" EXTRA_LDFLAGS="$EXTRA_LDFLAGS"

# reset counters
lcov --directory . --zerocounters

# build and run tests (allow test fails)
make test NO_INTERACTION=1 || /bin/true

# collect gcov data and build html report
lcov --capture --directory . \
     --no-external \
     --output-file $INFO_FILE

genhtml --output-directory $REPORT_PATH \
        --title "php-sapnwrfc coverage report" \
        --show-navigation \
        --legend \
        --num-spaces 4 \
        $INFO_FILE
