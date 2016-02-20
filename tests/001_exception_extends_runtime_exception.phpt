--TEST--
SAPNWRFC\Exception extends \RuntimeException
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump($e instanceof \RuntimeException);
--EXPECT--
bool(true)
