--TEST--
SAPNWRFC\FunctionCallException extends \SAPNWRFC\Exception
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"; ?>
--FILE--
<?php
$e = new \SAPNWRFC\FunctionCallException;
var_dump($e instanceof \SAPNWRFC\Exception);
--EXPECT--
bool(true)
