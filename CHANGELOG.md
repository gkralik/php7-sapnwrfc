# Change Log
All notable changes to this project will be documented in this file.

## [Unreleased]
### Added
- Vagrant configuration for testing/debugging

## Changed
- Better exceptions: new base class and consistent exception messages
- Throw base exception class instead of generic Exception
- Rename class `FunctionEntry` to `RemoteFunction`
- Use MIT license instead of PHP license

## Fixed
- Memory leaks releated to zend_string handling throughout the extension

## 0.5.0 - 2016-02-13
### Added
- Initial working release of the extension

[Unreleased]: https://github.com/gkralik/php7-sapnwrfc/compare/0.5.0...HEAD
