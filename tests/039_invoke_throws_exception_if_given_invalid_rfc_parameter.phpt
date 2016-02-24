--TEST--
invoke() throws FunctionCallException given an invalid RFC parameter.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('STFC_CONNECTION');

try {
    $f->invoke([
        'IDONTEXIST' => 'foobar',
    ]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
