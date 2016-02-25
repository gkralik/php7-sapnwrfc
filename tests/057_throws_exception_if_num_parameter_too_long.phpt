--TEST--
Throws FunctionCallException if RFC NUM parameter too long.
--SKIPIF--
<?php include("should_run_online_tests.inc"); die("skip No suitable RFC to test."); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
--EXPECT--
