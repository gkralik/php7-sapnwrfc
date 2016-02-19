--TEST--
version() returns version string x.y.z
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::version();
--EXPECTF--
%d.%d.%d
