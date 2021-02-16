--TEST--
invoke() throws FunctionCallException given an invalid RFC parameter.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
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
