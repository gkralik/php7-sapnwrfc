--TEST--
Check for SAPNWRFC\Connection::version()
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::version();
--EXPECTF--
%d.%d.%d
