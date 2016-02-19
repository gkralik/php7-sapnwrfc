--TEST--
SAPNWRFC\Exception has getter for "errorInfo"
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump(method_exists($e, 'getErrorInfo'));
--EXPECT--
bool(true)
--XFAIL--
Not implemented yet.
