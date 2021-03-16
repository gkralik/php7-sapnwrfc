--TEST--
Throws FunctionCallException if integer is out of range (0 - 255) for RFC INT1.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('RFCTABLE', false);
try {
    $f->invoke([
        "IMPORTSTRUCT" => [
            'RFCFLOAT' => 1.23456789,
            'RFCCHAR1' => 'A',
            'RFCCHAR2' => 'BC',
            'RFCCHAR4' => 'DEFG',
            'RFCINT1' => -1, //< ERROR
            'RFCINT2' => 2,
            'RFCINT4' => 345,
            'RFCHEX3' => 'fgh',
            'RFCTIME' => '121120',
            'RFCDATE' => '20140101',
            'RFCDATA1' => '1DATA1',
            'RFCDATA2' => 'DATA222',
        ],
    ]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok\n";
}

try {
    $f->invoke([
        "IMPORTSTRUCT" => [
            'RFCFLOAT' => 1.23456789,
            'RFCCHAR1' => 'A',
            'RFCCHAR2' => 'BC',
            'RFCCHAR4' => 'DEFG',
            'RFCINT1' => 256, //< ERROR
            'RFCINT2' => 2,
            'RFCINT4' => 345,
            'RFCHEX3' => 'fgh',
            'RFCTIME' => '121120',
            'RFCDATE' => '20140101',
            'RFCDATA1' => '1DATA1',
            'RFCDATA2' => 'DATA222',
        ],
    ]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok\n";
}
--EXPECT--
ok
ok
