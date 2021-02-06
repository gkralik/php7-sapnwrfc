--TEST--
close() returns false if connection was already closed.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);
$c->close();
var_dump($c->close());
--EXPECT--
bool(false)
