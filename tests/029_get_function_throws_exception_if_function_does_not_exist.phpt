--TEST--
getFunction() throws FunctionCallException if function does not exist.
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

try {
    $c->getFunction('Z_I_DONT_EXIST');
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo 'ok';
}
--EXPECT--
ok
