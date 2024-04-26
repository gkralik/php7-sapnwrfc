--TEST--
RemoteFunction::getFunctionDescription() returns function interface as array.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php

$config = require(__DIR__ . '/../sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');
$desc = $f->getFunctionDescription();

foreach ($desc as $name => $_) {
    var_dump($name);
}

$resptextDesc = $desc['RESPTEXT'];

var_dump($resptextDesc['name'] === 'RESPTEXT');
var_dump($resptextDesc['type'] === 'RFCTYPE_CHAR');
// description is 'Exporting response message' or 'Exporting response text' depending on the system,
// so don't compare the value or the test might fail
var_dump(is_string($resptextDesc['description']));
var_dump($resptextDesc['direction'] === 'RFC_EXPORT');
var_dump(is_long($resptextDesc['ucLength']));
var_dump(is_long($resptextDesc['nucLength']));
var_dump($resptextDesc['decimals'] === 0);
var_dump($resptextDesc['default'] === '');
var_dump($resptextDesc['optional'] === false);
var_dump(isset($resptextDesc['typedef']));

--EXPECT--
string(10) "ECHOSTRUCT"
string(8) "RESPTEXT"
string(12) "IMPORTSTRUCT"
string(8) "RFCTABLE"
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(false)