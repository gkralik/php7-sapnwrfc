--TEST--
RemoteFunction::getName() returns the function's name.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

var_dump(method_exists($f, 'getName'));
var_dump($f->getName());
--EXPECT--
bool(true)
string(14) "STFC_STRUCTURE"
