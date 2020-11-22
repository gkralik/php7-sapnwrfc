--TEST--
RemoteFunction::getFunctionDescription() returns empty array for functions without parameters.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php

$config = require __DIR__ . '/../sapnwrfc.config.inc';
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
$desc = $f->getFunctionDescription();

var_dump(is_array($desc));
var_dump(empty($desc));

--EXPECT--
bool(true)
bool(true)