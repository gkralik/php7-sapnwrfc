--TEST--
clearFunctionDescCache function exists.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php
\var_dump(function_exists('\SAPNWRFC\clearFunctionDescCache'));
--EXPECT--
bool(true)