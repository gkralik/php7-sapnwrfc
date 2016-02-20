--TEST--
getFunction() returns a RemoteFunction object if function exists.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
var_dump($f instanceof \SAPNWRFC\RemoteFunction);
--EXPECT--
bool(true)
