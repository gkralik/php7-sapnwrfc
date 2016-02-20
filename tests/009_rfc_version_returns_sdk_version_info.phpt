--TEST--
rfcVersion() returns SDK version string x.y.z
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::rfcVersion();
--EXPECTF--
%d.%d.%d
