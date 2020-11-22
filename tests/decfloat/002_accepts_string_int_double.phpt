--TEST--
decfloat: accepts string, int or double
--SKIPIF--
<?php
include __DIR__ . "/../skipif_no_online_tests.inc";
include __DIR__ . "/../skipif_no_custom_tests.inc";
--FILE--
<?php
$config = require __DIR__ . "/../sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('Z_PHPSAP_DECFLOAT_TEST');

$paramSet = [
    "42" => 42,
    "1.234" => 1.234,
    "1.234E-12" => 1.234E-12,
    "2.345E67" => "2.345E67",
    "-2.345e+123" => "-2.345e+123"
];

foreach ($paramSet as $expected => $value) {
    $r = $f->invoke([
        'ZDECF16_IN' => $value,
        'ZDECF34_IN' => $value,
    ]);

    var_dump($r['ZDECF16_OUT'] == $expected);
    var_dump($r['ZDECF34_OUT'] == $expected);
}

--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)