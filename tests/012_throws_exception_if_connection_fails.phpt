--TEST--
Check if Connection throws ConnectionException if connection fails.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
new \SAPNWRFC\Connection([
    'foobar' => 'foobar',
]);
--EXPECTF--
Fatal error: Uncaught SAPNWRFC\ConnectionException%A
