--TEST--
A function handle can be reused (ie called more than once).
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
$f->invoke([]);
$f->invoke([]);
$f->invoke([]);
--EXPECT--
