--TEST--
\SAPNWRFC\Connection has constants for trace levels.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_OFF);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_BRIEF);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_VERBOSE);
var_dump(\SAPNWRFC\Connection::TRACE_LEVEL_FULL);
--EXPECT--
string(1) "0"
string(1) "1"
string(1) "2"
string(1) "3"
