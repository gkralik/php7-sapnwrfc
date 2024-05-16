--TEST--
setTraceDir() returns true.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php

$ret = \SAPNWRFC\Connection::setTraceDir(sys_get_temp_dir());
var_dump($ret);
--EXPECT--
bool(true)
