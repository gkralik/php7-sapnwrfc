--TEST--
Returned CHAR value is right-trimmed when rtrim option enabled.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$params = [
    "IMPORTSTRUCT" => [
        'RFCFLOAT' => 1.23456789,
        'RFCCHAR1' => 'A',
        'RFCCHAR2' => 'BC',
        'RFCCHAR4' => 'DEFG',
        'RFCINT1' => 1,
        'RFCINT2' => 2,
        'RFCINT4' => 345,
        'RFCHEX3' => 'fgh',
        'RFCTIME' => '121120',
        'RFCDATE' => '20140101',
        'RFCDATA1' => '1DATA1',
        'RFCDATA2' => 'DATA222',
    ],
];

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('RFCTABLE', false);

$ret = $f->invoke($params, ['rtrim' => true]);

var_dump($ret['ECHOSTRUCT']['RFCDATA1'] == '1DATA1');
var_dump($ret['ECHOSTRUCT']['RFCDATA2'] == 'DATA222');

--EXPECT--
bool(true)
bool(true)