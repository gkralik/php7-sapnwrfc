--TEST--
isParameterActive() returns parameter status.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
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
