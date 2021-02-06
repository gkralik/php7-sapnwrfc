--TEST--
A function handle can be reused (ie called more than once).
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
$f->invoke([]);
$f->invoke([]);
$f->invoke([]);
--EXPECT--
