--TEST--
invoke() does not return a value for an inactive parameter.
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
