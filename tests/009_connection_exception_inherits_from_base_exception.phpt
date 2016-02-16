--TEST--
Check if ConnectionException inherits from Exception
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$ex = new \SAPNWRFC\ConnectionException('foobar');

var_dump($ex instanceof Exception);
--EXPECT--
bool(true)
