# TODO

Not ordered by priority...

* Rename `FunctionEntry` to `RemoteFunction`
* Make sure all malloc'd `SAP_UC*` etc are free'd
* Make sure all resources are free'd correctly (eg. what about `zend_string_release?`)
* Add `arginfo`
* Organize the code ;)
* Make exception factories easier to use (pass in `RFC_ERROR_INFO` and do the heavy lifting in there instead of scattering the same code all over the place) and check if there are more fields from the error info struct that might be interesting to the end user. `RfcGetRcAsString` might come in handy there also.
* Make exception messages more useful: include the parameter name where it makes sense etc.
* Change the handling of active/inactive parameters. Currently, the functon handle is created in `Connection::getFunction()` and `setParameterActive/isParameterActive` directly use `RfcSetParameterActive/RfcIsParameterActive`. This could be a problem when one fetches a function that hast optional parameters and uses it for subsequent calls -> if an optional parameter is given in the first call, but not in the second one, the optional parameter from the first call will be reused without the user expecting/wanting it.
A much better solution would be to use a `HashTable` or something similar in the function object that contains a mapping of `parameter_name => true|false`. All parameters would default to `true`. Then `setParameterActive/isParameterActive` would toggle the state in the mapping and the actual calls to `RfcSetParameterActive/RfcIsParameterActive` would happen by iterating over the `HashTable` just before calling `RfcInvoke`. This would eliminate the need to create the funtion handle when looking up the function and thus solve the aforementioned problem.
* Strip returned field values (ie remove the useless space padding)
