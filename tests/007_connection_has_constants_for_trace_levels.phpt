--TEST--
SAPNWRFC\Connection has constants for trace levels.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_OFF);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_BRIEF);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_VERBOSE);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_FULL);
--EXPECT--
int(0)
int(1)
int(2)
int(3)
