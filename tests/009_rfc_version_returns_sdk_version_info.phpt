--TEST--
rfcVersion() returns SDK version string x.y.z
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
echo \SAPNWRFC\Connection::rfcVersion();
--EXPECTF--
%d.%d.%d
