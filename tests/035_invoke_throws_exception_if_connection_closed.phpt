--TEST--
invoke() throws FunctionCallException if connection closed.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$func = $c->getFunction('RFC_PING');
$c->close();

try {
    $func->invoke([]);
    echo "fail";
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
