#!/usr/bin/env bash

set -e

# change to project root
cd "$(dirname $(readlink -f $0))/.."

# clone gh-pages into temporary directory
git clone --branch gh-pages git@github.com:gkralik/php7-sapnwrfc.git docs_tmp

# build docs
make -C docs clean html

# upate docs
rsync -rv --delete --exclude=.git --exclude=.buildinfo docs/_build/html/ docs_tmp/

# make sure the .nojekyll file is there
touch docs_tmp/.nojekyll

# add to repo
set +e
git -C docs_tmp add -A && \
git -C docs_tmp commit -m "updated docs" && \
git -C docs_tmp push origin gh-pages

# remove temporary directory
rm -rf docs_tmp
