--TEST--
close() closes the connection and returns true if the connection was open.
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

var_dump($c->close());
--EXPECT--
bool(true)
