# Make a release

- Update `PHP_SAPNWRFC_VERSION` in `php_sapnwrfc.h`
- Update `version` and `release` in `docs/conf.py`
- Update `CHANGELOG.md`
- Commit the changes: `git add . && git commit -m "Release version x.y.z"`
- Tag the version: `git tag -a x.y.z -m "Release version x.y.z"`
- Push changes and tag: `git push && git push --tags`
- Build and publish update docs: `scripts/publish_docs.sh`
- Create the Github release
