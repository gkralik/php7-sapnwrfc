--TEST--
Throws FunctionCallException if not given string for RFC TIME.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
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
        'RFCTIME' => 121120, //< ERROR
        'RFCDATE' => '010116',
        'RFCDATA1' => '1DATA1',
        'RFCDATA2' => 'DATA222',
    ],
];

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('RFCTABLE', false);
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
