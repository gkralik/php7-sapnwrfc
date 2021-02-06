--TEST--
SAPNWRFC\ConnectionException extends \SAPNWRFC\Exception
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
$e = new \SAPNWRFC\ConnectionException;
var_dump($e instanceof \SAPNWRFC\Exception);
--EXPECT--
bool(true)
