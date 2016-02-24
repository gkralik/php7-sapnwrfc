--TEST--
A function handle can be reused (ie called more than once).
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
$f->invoke([]);
$f->invoke([]);
$f->invoke([]);
--EXPECT--
