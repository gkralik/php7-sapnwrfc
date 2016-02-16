--TEST--
Close returns false if connection already closed.
--SKIPIF--
<?php include("skipif_offline.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);
$c->close();
var_dump($c->close());
--EXPECT--
bool(false)
