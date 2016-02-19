--TEST--
close() returns false if connection was already closed.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);
$c->close();
var_dump($c->close());
--EXPECT--
bool(false)
