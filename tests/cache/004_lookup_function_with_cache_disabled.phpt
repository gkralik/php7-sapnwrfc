--TEST--
Looking up a function with disabled function desc cache works
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
use \SAPNWRFC\Connection;

$config = require(__DIR__ . '/../sapnwrfc.config.inc');
$c = new Connection($config, ['use_function_desc_cache' => false]);

$f = $c->getFunction('STFC_STRUCTURE');

\var_dump($f !== null);
--EXPECT--
bool(true)