--TEST--
close() does not accept parameters.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

try {
    $c->close('foobar');
} catch(\SAPNWRFC\ConnectionException $e) {
    echo "ok";
}
--EXPECT--
ok
