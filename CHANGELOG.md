# Change Log
All notable changes to this project will be documented in this file.

## [Unreleased]
### Changed
- Update build instructions for Windows (#90)

## [2.0.0-beta2] - 2021-12-05
### Added
- Add `Connection::getSSOTicket()` to retrieve SSO ticket from connection (#34).

## [2.0.0-beta1] - 2021-09-09
This is a major release with breaking changes. For details, see changes below
marked with **BC break**.

### Changed
- Re-organize tests (skip conditions, environment variables)
- Throw `\Exception` or `\TypeError` for parameter parsing errors (instead of `\SAPNWRFC\Exception`) **BC break**
- Throw `\TypeError` if wrong type is passed for an RFC field **BC break**
- Add support for PHP 8.0
- Map RFC type BCD to string **BC break**
- Add support for `RFCTYPE_INT8`
### Removed
- Remove support for PHP < 7.2

## [1.4.0] - 2021-01-13
This is a major release with breaking changes. For details, see changes below
marked with **BC break**.

### Added
- Support for building with SAP NW RFC SDK 7.50 (#69)
- Support for building with clang
- Windows builds: support passing search path via `--with-sapnwrfc=`
- Windows builds: search for includes in `C:\nwrfcsdk` and `C:\nwrfcsdk_750` by default
- Add `RemoteFunction::getFunctionDescription()` to retrieve a function's metadata (#79)
- Add `RemoteFunction::getName()` retrieve a function's name
- Add support for `RFCTYPE_DECF16` and `RFCTYPE_DECF34` (#99)
### Changed
- use `zend_restore_error_handling()` to restore previous error handling
### Removed
- Drop support for building with SAP NW RFC SDK < 7.50 **BC break**
- Remove the `RemoteFunction` properties (parameter description) **BC break**
### Fixed
- Fix a memory leak in `PHP_MINFO_FUNCTION(sapnwrfc)`: free `version`
- Fix memory corruption when converting SAPUC strings to/from zval/zend_string (#101)

## [1.3.0] - 2019-02-23
### Added
- Add optional `$options` parameter to `Connection::__construct()`
- Connnection constructor accepts `use_function_desc_cache` option (defaults to `true`)
- `Connection::getFunction()` clears the function desc cache if `use_function_desc_cache` set to `false` before looking up the function
- Add `\SAPNWRFC\clearFunctionDescCache($functionName, $repositoryId)` function
### Changed
- Update documentation: fix link to sapnwrfc.ini settings, give saprouter example

## [1.2.1] - 2018-03-08
### Fixed
- Disable `rtrim` option by default (BC)

## [1.2.0] - 2018-03-04
### Added
- Allow `rtrim` option for `RemoteFunction::invoke()` to unify string handling (enabled by default)
- Add scripts/publish_docs.sh
- Add scripts/bump_version.php
- Support for PHP 7.2
- Custom make targets `extclean` and `extdistclean` to remove intermediary build artefacts
- Add new documentation

## [1.1.3] - 2017-10-21
### Fixed
- Fix compilation with NW RFC SDK versions < 7.20

## [1.1.2] - 2017-03-30
### Fixed
- Fix segfault when returning empty strings

## [1.1.1] - 2016-09-20
### Fixed
- Windows build: fix syntax error

## [1.1.0] - 2016-09-16
### Changed
- Include parameter name in exception messages for TABLE parameters
- Allow `int` to be passed for `FLOAT` parameters
- Allow passing parameters by reference
- Add script to generate test coverage data
- Add new screenshots to the NW RFC SDK installation guide
- Add a release date for version 1.0.0 in the Changelog
- CS fixes

## [1.0.0] - 2016-04-01
### Changed
- `Exception::$errorInfo` is now protected
- `attributes()` is now `getAttributes()`
- Test handling simplified for testing against a live system

## [0.7.0] - 2016-02-29
### Added
- Version information in phpinfo() (#12)
- Windows build instructions (#8, #10)
- A lot more tests
- `getErrorInfo()` for exception classes (#14)
- Argument info and types to enable reflection and type safety
- Improve parameter handling (#15)
- `setTraceDir()` and `setTraceLevel()` for setting the trace directory and level (#17)

### Changed
- `TRACE_LEVEL_*` constants are now integers

### Fixed
- Fixed a segfault when passing non-string values in connection parameters


## [0.6.2] - 2016-02-20
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

[Unreleased]: https://github.com/gkralik/php7-sapnwrfc/compare/2.0.0-beta2...HEAD
[2.0.0-beta2]: https://github.com/gkralik/php7-sapnwrfc/compare/2.0.0-beta1...2.0.0-beta2
[2.0.0-beta1]: https://github.com/gkralik/php7-sapnwrfc/compare/1.4.0...2.0.0-beta1
[1.4.0]: https://github.com/gkralik/php7-sapnwrfc/compare/1.3.0...1.4.0
[1.3.0]: https://github.com/gkralik/php7-sapnwrfc/compare/1.2.1...1.3.0
[1.2.1]: https://github.com/gkralik/php7-sapnwrfc/compare/1.2.0...1.2.1
[1.2.0]: https://github.com/gkralik/php7-sapnwrfc/compare/1.1.3...1.2.0
[1.1.3]: https://github.com/gkralik/php7-sapnwrfc/compare/1.1.2...1.1.3
[1.1.2]: https://github.com/gkralik/php7-sapnwrfc/compare/1.1.1...1.1.2
[1.1.1]: https://github.com/gkralik/php7-sapnwrfc/compare/1.1.0...1.1.1
[1.1.0]: https://github.com/gkralik/php7-sapnwrfc/compare/1.0.0...1.1.0
[1.0.0]: https://github.com/gkralik/php7-sapnwrfc/compare/0.7.0...1.0.0
[0.7.0]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.2...0.7.0
[0.6.2]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.1...0.6.2
[0.6.1]: https://github.com/gkralik/php7-sapnwrfc/compare/0.6.0...0.6.1
[0.6.0]: https://github.com/gkralik/php7-sapnwrfc/compare/0.5.0...0.6.0