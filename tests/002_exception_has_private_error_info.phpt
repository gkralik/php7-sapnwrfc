--TEST--
SAPNWRFC\Exception has private "errorInfo" property
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump(property_exists($e, 'errorInfo'));

$r = new ReflectionClass($e);
var_dump($r->getProperty('errorInfo')->isProtected());

--EXPECT--
bool(true)
bool(true)
