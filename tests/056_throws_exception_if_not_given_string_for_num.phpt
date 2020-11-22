--TEST--
Throws FunctionCallException if not given string for RFC NUM.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; die("skip No suitable RFC to test."); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
--EXPECT--
