--TEST--
RemoteFunction::getName() returns the function's name.
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

var_dump(method_exists($f, 'getName'));
var_dump($f->getName());
--EXPECT--
bool(true)
string(14) "STFC_STRUCTURE"
