--TEST--
decfloat: returns string
--SKIPIF--
<?php
include __DIR__ . "/../skipif_no_online_tests.inc";
include __DIR__ . "/../skipif_no_custom_tests.inc";
?>
--FILE--
<?php
$config = require __DIR__ . "/../sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('Z_PHPSAP_DECFLOAT_TEST');

$r = $f->invoke();
var_dump($r['ZDECF']);

--EXPECT--
string(7) "1.23456"
