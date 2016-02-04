--TEST--
Check for SAPNWRFC\FunctionCallException presence
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
try {
    throw new \SAPNWRFC\FunctionCallException('error');
} catch(\SAPNWRFC\FunctionCallException $e) {
    print $e->getMessage();
}
--EXPECT--
error
