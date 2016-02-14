# TODO

Not ordered by priority...

* Rename `FunctionEntry` to `RemoteFunction`
* Make sure all malloc'd `SAP_UC*` etc are free'd
* Test with a `DEBUG` and `ZTS` build.
* Add `arginfo`
* Organize the code ;)
* Change the handling of active/inactive parameters. Currently, the functon handle is created in `Connection::getFunction()` and `setParameterActive/isParameterActive` directly use `RfcSetParameterActive/RfcIsParameterActive`. This could be a problem when one fetches a function that hast optional parameters and uses it for subsequent calls -> if an optional parameter is given in the first call, but not in the second one, the optional parameter from the first call will be reused without the user expecting/wanting it.
A much better solution would be to use a `HashTable` or something similar in the function object that contains a mapping of `parameter_name => true|false`. All parameters would default to `true`. Then `setParameterActive/isParameterActive` would toggle the state in the mapping and the actual calls to `RfcSetParameterActive/RfcIsParameterActive` would happen by iterating over the `HashTable` just before calling `RfcInvoke`. This would eliminate the need to create the funtion handle when looking up the function and thus solve the aforementioned problem.
* Strip returned field values (ie remove the useless space padding)
