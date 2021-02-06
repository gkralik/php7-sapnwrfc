--TEST--
Allow passing references as parameters.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$float = 1.23456789;
$char1 = 'A';
$char2 = 'BC';
$char4 = 'DEFG';
$int1 = 1;
$int2 = 2;
$int4 = 345;
$hex3 = 'fgh';
$time = '121120';
$date = '20160101';
$data1 = '1DATA1';
$data2 = 'DATA222';

$struct = [
    'RFCFLOAT' => &$float,
    'RFCCHAR1' => &$char1,
    'RFCCHAR2' => &$char2,
    'RFCCHAR4' => &$char4,
    'RFCINT1' => &$int1,
    'RFCINT2' => &$int2,
    'RFCINT4' => &$int4,
    'RFCHEX3' => &$hex3,
    'RFCTIME' => &$time,
    'RFCDATE' => &$date,
    'RFCDATA1' => &$data1,
    'RFCDATA2' => &$data2,
];

$table = [
    &$struct
];

$params = [
    "IMPORTSTRUCT" => &$struct,
    "RFCTABLE" => &$table,
];

$f = $c->getFunction("STFC_STRUCTURE");

try {
    $f->invoke($params);
    echo "ok";
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo $e->getMessage();
}
--EXPECT--
ok
