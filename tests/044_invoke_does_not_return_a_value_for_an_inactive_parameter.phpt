--TEST--
invoke() does not return a value for an inactive parameter.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_CHANGING');
$f->setParameterActive('RESULT', false);
var_dump($f->isParameterActive('RESULT'));

$result = $f->invoke([
    'START_VALUE' => 0,
    'COUNTER' => 1,
]);

var_dump($result['COUNTER']);
var_dump(array_key_exists('RESULT', $result));

--EXPECT--
bool(false)
int(2)
bool(false)
