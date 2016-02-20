--TEST--
ping() returns true if connection is open.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

var_dump($c->ping());
--EXPECT--
bool(true)
