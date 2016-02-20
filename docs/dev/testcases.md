# Testcases TODO

## Exceptions

* base class extends RuntimeException
* base class has "errorInfo" property
* base class has getErrorInfo() method
* ConnectionException inherits from base class
* FunctionCallException inherits from base class
* "errorInfo" property is an array with at least "key", "code" and "message" if thrown from a method (use Connection() with invalid params)

## Connection

### Constants

* has TRACEL_LEVEL_(OFF|BRIEF|VERBOSE|FULL) constants with string values "0", "1", "2", "3"

### version() and rfcVersion()

* version() returns a string of format "X.Y.Z"
* rfcVersion() returns a string of format "X.Y.Z"

### \__construct()

* throws ConnectionException if given no parameters
* throws ConnectionException if given anything other than array
* throws ConnectionException if given an empty array ("No connection parameters given")
* throws ConnectionException if connection fails + sets "errorInfo" in exception ("Could not open connection")
* ONLINE returns Connection object if connection is OK

### close()

* ONLINE closes connection and returns true if connection was open
* ONLINE returns false if connection already closed
* ONLINE does not accept parameters

### attributes()

* ONLINE returns an array of connection attributes (test all properties) if connected
* ONLINE throws ConnectionException if connection already closed
* ONLINE does not accept parameters

### ping()

* ONLINE sends ping and returns true if connection open
* ONLINE throws ConnectionException if connection already closed
* ONLINE does not accept parameters

### getFunction()

* ONLINE throws ConnectionException if parameter is anything other than a string
* ONLINE throws FunctionCallException if the function does not exist
* ONLINE throws FunctionCallException if connection already closed
* ONLINE returns a RemoteFunction object if function lookup successful
* ONLINE RemoteFunction object contains "name" property with the function name and a property for each parameter with param info

### setIniPath()

* returns true if INI path set
* throws ConnectionException if parameter is anything other than a string

### reloeadIniFile()

* returns true if reload OK
* does not accept parameters

## RemoteFunction

### invoke() - test with FM's from STFC, STFE and MRFC

* ONLINE throws FunctionCallException if connection already closed
* ONLINE throws FunctionCallException if given anything other than an array
* ONLINE throws FunctionCallException if given a non-string key in parameter array
* ONLINE throws FunctionCallException if given a parameter that does not exist for function
* ONLINE can call RFC_PING with no parameters and return
* ONLINE returns expected values and handles TABLES for successful call to STFC_STRUCTURE
* ONLINE can handle CHANGING parameters for STFC_CHANGING
* ONLINE throws FunctionCallException for call to RFC_RAISE_ERROR and sets ABAP info in exception's "errorInfo"
* ONLINE does not return a value for a parameter that has been set inactive
* ONLINE does not send optional value on subsequent call if parameter has been set inactive for second call
* ONLINE throws FunctionCallException if not given string for CHAR parameter
* ONLINE throws FunctionCallException if not given string for DATE parameter
* ONLINE throws FunctionCallException if given incorrect format (<> 8 chars) for DATE parameter
* ONLINE throws FunctionCallException if not given string for TIME parameter
* ONLINE throws FunctionCallException if given incorrect format (<> 6 chars) for TIME parameter
* ONLINE throws FunctionCallException if not given string for BYTE parameter
* ONLINE throws FunctionCallException if given too long string for BYTE parameter
* ONLINE throws FunctionCallException if not given array for TABLE parameter
* ONLINE throws FunctionCallException if not given array for STRUCTURE parameter
* ONLINE throws FunctionCallException if not given string for NUM parameter
* ONLINE throws FunctionCallException if given too long for NUM parameter
* ONLINE throws FunctionCallException if not given double for FLOAT parameter
* ONLINE throws FunctionCallException if not given integer for INT parameter
* ONLINE throws FunctionCallException if not given integer for INT1 parameter
* ONLINE throws FunctionCallException if not given integer for INT2 parameter
* ONLINE throws FunctionCallException if given integer not between 0 and 255 for INT1 parameter
* ONLINE throws FunctionCallException if given integer not between -32767 and 32767 for INT2 parameter
* ONLINE throws FunctionCallException if not given string for STRING parameter
* ONLINE throws FunctionCallException if not given string for XSTRING parameter
* ONLINE throws FunctionCallException if given incorrect format (non-hex chars) for XSTRING parameter
* ONLINE throws FunctionCallException if setting an unknown field for TABLE parameter
* ONLINE throws FunctionCallException if setting an unknown field for STRUCTURE parameter

### setParameterActive()

* ONLINE throws FunctionCallException if parameters are not string and boolean
* ONLINE throws FunctionCallException if connection has been closed??
* ONLINE returns nothing if status change is OK

### isParameterActive()

* ONLINE throws FunctionCallException if parameter is not string
* ONLINE throw FunctionCallException if connection already closed??
* ONLINE returns true if parameter is active (default)
* ONLINE returns false if parameter was set inactive by setParameterActive before
* ONLINE returns true if parameter was set active by setParameterActive before
