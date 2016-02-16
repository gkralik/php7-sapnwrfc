--TEST--
Close closes the connection if open and returns true.
--SKIPIF--
<?php include("skipif_offline.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);
var_dump($c->close());
--EXPECT--
bool(true)
