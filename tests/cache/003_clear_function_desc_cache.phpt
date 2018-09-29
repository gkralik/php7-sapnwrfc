--TEST--
Clearing the function desc cache works.
--SKIPIF--
<?php include("tests/should_run_online_tests.inc"); ?>
--FILE--
<?php
use \SAPNWRFC\Connection;
use function \SAPNWRFC\clearFunctionDescCache;

$config = include "tests/sapnwrfc.config.inc";
$c = new Connection($config);

// lookup a function to warm the cache
$f1 = $c->getFunction('STFC_STRUCTURE');
$f2 = $c->getFunction('RFC_PING');

// get the connection's sysId
$sysId = $c->getAttributes()['sysId'];

// try to clear the cache
var_dump(clearFunctionDescCache('STFC_STRUCTURE'));
var_dump(clearFunctionDescCache('STFC_STRUCTURE', $sysId));
var_dump(clearFunctionDescCache('RFC_PING'));
var_dump(clearFunctionDescCache('RFC_PING', $sysId));

--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)