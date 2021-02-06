--TEST--
invoke() can handle CHANGING parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_CHANGING');
$result = $f->invoke([
    'START_VALUE' => 0,
    'COUNTER' => 1,
]);

var_dump($result['COUNTER']);
var_dump($result['RESULT']);
--EXPECT--
int(2)
int(1)
