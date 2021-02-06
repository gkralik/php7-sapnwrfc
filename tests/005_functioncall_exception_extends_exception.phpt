--TEST--
SAPNWRFC\FunctionCallException extends \SAPNWRFC\Exception
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
$e = new \SAPNWRFC\FunctionCallException;
var_dump($e instanceof \SAPNWRFC\Exception);
--EXPECT--
bool(true)
