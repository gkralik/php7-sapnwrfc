--TEST--
Check for \SAPNWRFC\Exception presence.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
try {
    throw new \SAPNWRFC\Exception('error');
} catch(\SAPNWRFC\Exception $e) {
    print $e->getMessage();
}
--EXPECT--
error
