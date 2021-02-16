--TEST--
close() returns false if connection was already closed.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);
$c->close();
var_dump($c->close());
--EXPECT--
bool(false)
