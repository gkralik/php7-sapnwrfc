# Change Log
All notable changes to this project will be documented in this file.

## [Unreleased]
### Added
- Instructions for installing the SAP NW RFC SDK library
- Some additional tests (offline and online)
- Tests covering exceptions and `Connection` object

### Fixed
- `TRACE_LEVEL_*` contants are now strings; the long variants caused segfaults in `zval_to_sapuc()`
- Fix a segfault related to the `RemoteFunction::$name` property.

## [0.6.1] - 2016-02-16
### Added
- Readded some removed TSRM bits as pointed out by @krakjoe - thanks a lot!

### Fixed
- Properly initialize the "errorInfo" property in exceptions to prevent error on shutdown (Windows)

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

[Unreleased]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.1...HEAD
[0.6.1]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.0...0.6.1
[0.6.0]: https://github.com/gkralik/php7-sapnwrfc/compare/0.5.0...0.6.0
