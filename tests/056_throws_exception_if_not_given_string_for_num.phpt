--TEST--
Throws FunctionCallException if not given string for RFC NUM.
--SKIPIF--
<?php include("should_run_online_tests.inc"); die("skip No suitable RFC to test."); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
--EXPECT--
