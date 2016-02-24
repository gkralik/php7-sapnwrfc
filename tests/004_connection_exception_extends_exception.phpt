--TEST--
SAPNWRFC\ConnectionException extends \SAPNWRFC\Exception
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$e = new \SAPNWRFC\ConnectionException;
var_dump($e instanceof \SAPNWRFC\Exception);
--EXPECT--
bool(true)
