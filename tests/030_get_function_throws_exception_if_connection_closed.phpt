--TEST--
getFunction() throws FunctionCallException if connection already closed.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
$c->close();

try {
    $c->getFunction('Z_I_DONT_EXIST');
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo 'ok';
}
--EXPECT--
ok
