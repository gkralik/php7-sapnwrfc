--TEST--
ping() does not accept arguments.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
try {
    $c->ping('foobar');
} catch(\SAPNWRFC\ConnectionException $e) {
    echo 'ok';
}
--EXPECT--
ok
