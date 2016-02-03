--TEST--
Check for SAPNWRFC\Connection::version()
--SKIPIF--
<?php if (!extension_loaded("sapnwrfc")) print "skip"; ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::version();
--EXPECTF--
%d.%d.%d
