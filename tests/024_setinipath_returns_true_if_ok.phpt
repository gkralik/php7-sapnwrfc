--TEST--
setIniPath() returns true if path is correct and INI file is loaded.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
chdir(dirname(__FILE__));
var_dump(\SAPNWRFC\Connection::setIniPath('.'));
--EXPECT--
bool(true)
