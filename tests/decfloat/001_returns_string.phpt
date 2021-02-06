--TEST--
decfloat: returns string
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
skipif_custom_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/../sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('Z_PHPSAP_DECFLOAT_TEST');

$r = $f->invoke();
var_dump($r['ZDECF']);

--EXPECT--
string(7) "1.23456"
