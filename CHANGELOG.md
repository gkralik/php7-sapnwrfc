# Change Log
All notable changes to this project will be documented in this file.

## [Unreleased]

## [0.6.0] - 2016-02-15
### Added
- Vagrant configuration for testing/debugging
- Stub file for code completion in IDEs
- Class constants for trace levels

### Changed
- Better exceptions: new base class and consistent exception messages
- Throw base exception class instead of generic Exception
- Rename class `FunctionEntry` to `RemoteFunction`
- Use MIT license instead of PHP license
- Update some of the documentation to reflect current development state

### Fixed
- Memory leaks related to zend_string handling throughout the extension
- Memory leaks related to SAP_UC* handling throughout the extension

### Removed
- References to TSRM; they are not needed anymore in PHP7

## 0.5.0 - 2016-02-13
### Added
- Initial working release of the extension

[Unreleased]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.0...HEAD
[0.6.0]: https://github.com/gkralik/php7-sapnwrfc/compare/0.5.0...0.6.0
