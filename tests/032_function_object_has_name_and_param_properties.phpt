--TEST--
RemoteFunction object has name and parameter properties.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

var_dump(property_exists($f, "name"));
var_dump(trim($f->name));
var_dump(property_exists($f, "IMPORTSTRUCT"));
var_dump(is_array($f->IMPORTSTRUCT));
var_dump(property_exists($f, "RFCTABLE"));
var_dump(is_array($f->RFCTABLE));
--EXPECT--
bool(true)
string(14) "STFC_STRUCTURE"
bool(true)
bool(true)
bool(true)
bool(true)
