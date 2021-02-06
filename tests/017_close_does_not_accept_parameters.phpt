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
} catch(\SAPNWRFC\ConnectionException $e) {
    echo "ok";
}
--EXPECT--
ok
