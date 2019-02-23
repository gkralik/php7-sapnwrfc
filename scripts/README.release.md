# Make a release

```
$ git checkout -b release-x.y.z master
$ php scripts/bump_version.php x.y.z
update changelog for release
$ php scripts/bump_version x.y.z
$ git add .
$ git commit -m "..."
$ git tag -a x.y.z -m "..."
$ git checkout master
$ git merge release-x.y.z
$ git push
$ git push --tags
$ scripts/publish_docs.sh
create github release
```

commit/tag template:
    release x.y.z
    
    Changes:
      - ...
      