#!/usr/bin/env bash

set -e

# build the docs
cd docs
make clean html
cd ..

# switch to branch gh-pages and update the docs
git checkout gh-pages

# remove everything _except_: .git and the docs folder (which contains
# the generated docs)
find . -maxdepth 1 ! -path . -and ! -name .git -and ! -name docs -exec rm -r {} \;

# make sure the .nojekyll file is there
touch .nojekyll

# move the generated docs
mv ./docs/_build/html/* ./
rm -rf ./docs

# add to repo
git add -A
git commit -m "updated docs"
git push origin gh-pages

# switch back to master
git checkout master