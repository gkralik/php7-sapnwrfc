--TEST--
getAttributes() returns an array of connection attributes.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);

$a = $c->getAttributes();

var_dump(is_array($a));
var_dump(array_key_exists("dest", $a));
var_dump(array_key_exists("host", $a));
var_dump(array_key_exists("partnerHost", $a));
var_dump(array_key_exists("sysNumber", $a));
var_dump(array_key_exists("sysId", $a));
var_dump(array_key_exists("client", $a));
var_dump(array_key_exists("user", $a));
var_dump(array_key_exists("language", $a));
var_dump(array_key_exists("trace", $a));
var_dump(array_key_exists("isoLanguage", $a));
var_dump(array_key_exists("codepage", $a));
var_dump(array_key_exists("partnerCodepage", $a));
var_dump(array_key_exists("rfcRole", $a));
var_dump(array_key_exists("type", $a));
var_dump(array_key_exists("partnerType", $a));
var_dump(array_key_exists("rel", $a));
var_dump(array_key_exists("partnerRel", $a));
var_dump(array_key_exists("kernelRel", $a));
var_dump(array_key_exists("cpicConvId", $a));
var_dump(array_key_exists("progName", $a));
var_dump(array_key_exists("partnerBytesPerChar", $a));
var_dump(array_key_exists("partnerSystemCodepage", $a));
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
bool(true)
bool(true)
bool(true)
