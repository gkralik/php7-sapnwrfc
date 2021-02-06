--TEST--
Connection constructor takes options hash as second parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
use \SAPNWRFC\Connection;

$config = require(__DIR__ . '/../sapnwrfc.config.inc');
$c = new Connection($config, ['use_function_desc_cache' => false]);

echo "ok";
--EXPECT--
ok