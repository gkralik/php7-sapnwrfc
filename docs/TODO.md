# TODO

* FunctionEntry: "parameters" property to hold all params
* make sure all dynamically malloc'd SAP_UC* are free'd
* FunctionEntry::invoke()
* refactor code: split out classes, exceptions, etc.
* pass error_info to sapnwrfc_throw_exception_ex() instead of just some items
  can use it to call RfcGetRcAsString() and include the RC, etc in the exception
* customize exception message to include eg. the parameter name (when
    fetching the parameter description fails), etc.
* use SAP_DATE_LN and SAP_TIME_LN
* create the function in invoke?? if creating early, subsequent calls would have
  the old parameter info -> problem?
  but if created in invoke() we need another way to handle active/inactive params
  OR use a param on invoke to specify if we want to keep the function. if not, recreate
  the function at the end of invoke()
  **OR** when looking up the function, save a map of parameters with activation status == true
  then, setParameterActive would just change the map, isParameterActive would query the map
  and invoke would just iterate over the map and call RfcSetParameterActive on all of them
  could we use HashTable for that??? or a plain zend_array??
