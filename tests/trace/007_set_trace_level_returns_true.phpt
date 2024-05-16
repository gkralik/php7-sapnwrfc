--TEST--
setTraceDir() returns true.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php

$ret = \SAPNWRFC\Connection::setTraceLevel(\SAPNWRFC\Connection::TRACE_LEVEL_VERBOSE);
var_dump($ret);
--EXPECT--
bool(true)
