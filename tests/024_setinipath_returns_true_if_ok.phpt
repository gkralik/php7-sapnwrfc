--TEST--
setIniPath() returns true if path is correct and INI file is loaded.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
chdir(dirname(__FILE__));
var_dump(\SAPNWRFC\Connection::setIniPath('.'));
--EXPECT--
bool(true)
