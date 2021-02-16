--TEST--
invoke() can handle CHANGING parameter.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
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
