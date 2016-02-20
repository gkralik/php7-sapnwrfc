--TEST--
attributes() does not take arguments.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

try {
    $c->attributes('foobar');
} catch(\SAPNWRFC\ConnectionException $e) {
    echo 'ok';
}
--EXPECT--
ok
