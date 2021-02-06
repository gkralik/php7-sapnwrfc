--TEST--
Throws FunctionCallException if RFC NUM parameter too long.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
die('skip No suitable RFC to test.');
?>
--FILE--
<?php
--EXPECT--
