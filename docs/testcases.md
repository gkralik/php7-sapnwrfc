# Testcases TODO

## `\SAPNWRFC\Connection`

* new Connection() -> exception
* new Connection([]) -> exception
* new Connection(...anything that's not an array...) -> exception
* new Connection([params]) (ONLINE) -> OK
* close() on closed connection -> returns false;
* close() on open connection -> returns true or exception??


## Notes

* each function/method must parse parameters. use zend_parse_parameters_none() if not params.
* use zend_register_class_alias_ex to help migrate old code? would alias the classes to the old names
