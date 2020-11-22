--TEST--
Connection constructor takes options hash as second parameter.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
use \SAPNWRFC\Connection;

$config = include __DIR__ . "/../sapnwrfc.config.inc";
$c = new Connection($config, ['use_function_desc_cache' => false]);

echo "ok";
--EXPECT--
ok