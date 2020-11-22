--TEST--
reloadIniFile() returns true if reload OK.
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"; ?>
--FILE--
<?php
var_dump(\SAPNWRFC\Connection::reloadIniFile());
--EXPECT--
bool(true)
