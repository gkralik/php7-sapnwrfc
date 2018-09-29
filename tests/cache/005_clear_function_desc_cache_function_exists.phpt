--TEST--
clearFunctionDescCache function exists.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
\var_dump(function_exists('\SAPNWRFC\clearFunctionDescCache'));
--EXPECT--
bool(true)