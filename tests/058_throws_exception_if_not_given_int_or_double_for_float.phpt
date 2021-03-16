--TEST--
Throws TypeError if given wrong type for RFC FLOAT parameter.
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
        'RFCFLOAT' => '1.23456789', //< ERROR
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

$f->invoke($params);

--EXPECTF--
Fatal error: Uncaught TypeError: Failed to set %s parameter "%s". Expected %s, %s given in %s.php:%d
Stack trace:
#0 %s(%d): SAPNWRFC\RemoteFunction->invoke(Array)
#1 {main}
  thrown in %s.php on line %d