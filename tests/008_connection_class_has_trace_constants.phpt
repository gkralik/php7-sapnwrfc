--TEST--
Connection class has constants for trace levels
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::TRACE_LEVEL_OFF . "\n";
echo \SAPNWRFC\Connection::TRACE_LEVEL_BRIEF . "\n";
echo \SAPNWRFC\Connection::TRACE_LEVEL_VERBOSE . "\n";
echo \SAPNWRFC\Connection::TRACE_LEVEL_FULL . "\n";
--EXPECT--
0
1
2
3
