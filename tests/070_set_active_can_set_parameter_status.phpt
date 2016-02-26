--TEST--
setParameterActive() can set parameter status.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');
$f->setParameterActive('IMPORTSTRUCT', false);
$f->setParameterActive('RFCTABLE', false);

$r = $f->invoke([]);

var_dump(array_key_exists('RFCTABLE', $r));
$f->setParameterActive('RFCTABLE', true);

$r = $f->invoke([
    'RFCTABLE' => [],
]);
var_dump(array_key_exists('RFCTABLE', $r));
--EXPECT--
bool(false)
bool(true)
