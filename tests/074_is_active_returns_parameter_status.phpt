--TEST--
isParameterActive() returns parameter status.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

var_dump($f->isParameterActive('IMPORTSTRUCT'));

$f->setParameterActive('IMPORTSTRUCT', false);
var_dump($f->isParameterActive('IMPORTSTRUCT'));

$f->setParameterActive('IMPORTSTRUCT', true);
var_dump($f->isParameterActive('IMPORTSTRUCT'));
--EXPECT--
bool(true)
bool(false)
bool(true)
