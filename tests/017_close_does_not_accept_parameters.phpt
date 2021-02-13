--TEST--
close() does not accept parameters.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);

try {
    $c->close('foobar');
} catch(\Throwable $t) {
    echo $t->getMessage() . PHP_EOL;
}
--EXPECTF--
SAPNWRFC\Connection::close() expects exactly 0 %s, %d given