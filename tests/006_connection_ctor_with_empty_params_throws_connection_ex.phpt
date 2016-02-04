--TEST--
Connection::__construct() throws ConnectionException when given empty connection params array
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
new \SAPNWRFC\Connection([]);
--EXPECTF--
Fatal error: Uncaught SAPNWRFC\ConnectionException: No connection parameters given%A
