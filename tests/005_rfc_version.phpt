--TEST--
Check for SAPNWRFC\Connection::rfcVersion()
--SKIPIF--
<?php if (!extension_loaded("sapnwrfc")) print "skip"; ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::rfcVersion();
--EXPECTF--
%d.%d.%d
