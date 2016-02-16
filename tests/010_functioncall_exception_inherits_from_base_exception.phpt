--TEST--
Check if FunctionCallException inherits from Exception
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$ex = new \SAPNWRFC\FunctionCallException('foobar');

var_dump($ex instanceof Exception);
--EXPECT--
bool(true)
