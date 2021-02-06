--TEST--
getFunction() returns a RemoteFunction object if function exists.
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
var_dump($f instanceof \SAPNWRFC\RemoteFunction);
--EXPECT--
bool(true)
