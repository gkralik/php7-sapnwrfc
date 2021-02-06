--TEST--
SAPNWRFC\Exception extends \RuntimeException
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
$e = new \SAPNWRFC\Exception;
var_dump($e instanceof \RuntimeException);
--EXPECT--
bool(true)
