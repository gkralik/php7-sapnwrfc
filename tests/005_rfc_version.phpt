--TEST--
Check for SAPNWRFC\Connection::rfcVersion()
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::rfcVersion();
--EXPECTF--
%d.%d.%d
