--TEST--
Connection object is returned if connection is successful.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

echo 'ok';
--EXPECT--
ok
