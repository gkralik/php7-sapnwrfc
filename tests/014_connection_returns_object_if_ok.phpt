--TEST--
Connection object is returned if connection is successful.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);

echo 'ok';
--EXPECT--
ok
