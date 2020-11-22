--TEST--
getAttributes() throws ConnectionException if connection already closed.
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$c->close();

try {
    $c->getAttributes();
} catch(\SAPNWRFC\ConnectionException $e) {
    echo 'ok';
}
--EXPECT--
ok
