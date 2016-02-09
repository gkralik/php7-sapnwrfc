# TODO

* FunctionEntry: "parameters" property to hold all params
* make sure all dynamically malloc'd SAP_UC* are free'd
* FunctionEntry::invoke()
* refactor code: split out classes, exceptions, etc.
* pass error_info to sapnwrfc_throw_exception_ex() instead of just some items
  can use it to call RfcGetRcAsString() and include the RC, etc in the exception
* customize exception message to include eg. the parameter name (when
    fetching the parameter description fails), etc.
