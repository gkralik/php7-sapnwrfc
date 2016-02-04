--TEST--
Check for SAPNWRFC\ConnectionException presence
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
try {
    throw new \SAPNWRFC\ConnectionException('error');
} catch(\SAPNWRFC\ConnectionException $e) {
    print $e->getMessage();
}
--EXPECT--
error
