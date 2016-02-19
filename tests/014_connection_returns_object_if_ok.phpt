--TEST--
Connection object is returned if connection is successful.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

echo 'ok';
--EXPECT--
ok
