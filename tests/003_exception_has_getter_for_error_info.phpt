--TEST--
SAPNWRFC\Exception has getter for "errorInfo"
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"; ?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump(method_exists($e, 'getErrorInfo'));
var_dump($e->getErrorInfo() === null);
--EXPECT--
bool(true)
bool(true)
