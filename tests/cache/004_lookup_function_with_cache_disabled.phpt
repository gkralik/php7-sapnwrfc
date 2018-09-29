--TEST--
Looking up a function with disabled function desc cache works
--SKIPIF--
<?php include(__DIR__ . "/../should_run_online_tests.inc"); ?>
--FILE--
<?php
use \SAPNWRFC\Connection;

$config = include __DIR__ . "/../sapnwrfc.config.inc";
$c = new Connection($config, ['use_function_desc_cache' => false]);

$f = $c->getFunction('STFC_STRUCTURE');

\var_dump($f !== null);
--EXPECT--
bool(true)