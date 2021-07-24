--TEST--
Returns string for RFC type BCD
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_custom_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction("Z_PHPSAP_BCD_TEST1");

var_dump($f->invoke(['ZMENGE13_IN' => '123.456'])['ZMENGE13_OUT']);
var_dump($f->invoke(['ZMENGE13_IN' => 456.789])['ZMENGE13_OUT']);

--EXPECT--
string(7) "123.456"
string(7) "456.789"
