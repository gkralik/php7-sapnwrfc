--TEST--
SAPNWRFC\Exception has private "errorInfo" property
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump(property_exists($e, 'errorInfo'));

$r = new ReflectionClass($e);
var_dump($r->getProperty('errorInfo')->isPrivate());

--EXPECT--
bool(true)
bool(true)
