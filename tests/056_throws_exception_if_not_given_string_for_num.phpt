--TEST--
Throws FunctionCallException if not given string for RFC NUM.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
die('skip No suitable RFC to test.');
?>
--FILE--
<?php

--EXPECT--
