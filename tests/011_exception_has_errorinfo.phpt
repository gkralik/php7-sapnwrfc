--TEST--
Check if Exception has errorInfo property
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$ex = new \SAPNWRFC\Exception('foobar');

// is initialized to null
$v = $ex->errorInfo == null;
var_dump($v);
--EXPECT--
bool(true)
