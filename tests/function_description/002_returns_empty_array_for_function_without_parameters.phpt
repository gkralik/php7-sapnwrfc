--TEST--
RemoteFunction::getFunctionDescription() returns empty array for functions without parameters.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php

$config = require(__DIR__ . '/../sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');
$desc = $f->getFunctionDescription();

var_dump(is_array($desc));
var_dump(empty($desc));

--EXPECT--
bool(true)
bool(true)