--TEST--
close() closes the connection and returns true if the connection was open.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);

var_dump($c->close());
--EXPECT--
bool(true)
