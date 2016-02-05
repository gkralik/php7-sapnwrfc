--TEST--
Check for \SAPNWRFC\FunctionEntry presence
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
var_dump(new \SAPNWRFC\FunctionEntry());
--EXPECT--
object(SAPNWRFC\FunctionEntry)#1 (0) {
}
