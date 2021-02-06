--TEST--
RemoteFunction::getFunctionDescription() returns typedef for structures/tables.
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

$importstructDesc = $desc['IMPORTSTRUCT'];

var_dump($importstructDesc['name']);
var_dump($importstructDesc['type']);
var_dump($importstructDesc['description']);
var_dump($importstructDesc['direction']);
var_dump(is_long($importstructDesc['ucLength']));
var_dump(is_long($importstructDesc['nucLength']));
var_dump($importstructDesc['decimals']);
var_dump($importstructDesc['default']);
var_dump($importstructDesc['optional']);
var_dump(is_array($importstructDesc['typedef']));

var_dump(count($importstructDesc['typedef']));

$firstField = $importstructDesc['typedef']['RFCFLOAT'];
var_dump($firstField['name']);
var_dump($firstField['type']);
var_dump(is_long($firstField['nucLength']));
var_dump(is_long($firstField['nucOffset']));
var_dump(is_long($firstField['ucLength']));
var_dump(is_long($firstField['ucOffset']));
var_dump($firstField['decimals']);
var_dump(isset($firstField['typedef']));

$rfctableDesc = $desc['RFCTABLE'];
var_dump(is_array($rfctableDesc));
var_dump(count($rfctableDesc['typedef']));

--EXPECT--
string(12) "IMPORTSTRUCT"
string(17) "RFCTYPE_STRUCTURE"
string(19) "Importing structure"
string(10) "RFC_IMPORT"
bool(true)
bool(true)
int(0)
string(0) ""
bool(false)
bool(true)
int(12)
string(8) "RFCFLOAT"
string(13) "RFCTYPE_FLOAT"
bool(true)
bool(true)
bool(true)
bool(true)
int(16)
bool(false)
bool(true)
int(12)
