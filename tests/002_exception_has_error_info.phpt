--TEST--
SAPNWRFC\Exception has "errorInfo" property
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump(property_exists($e, 'errorInfo'));
--EXPECT--
bool(true)
