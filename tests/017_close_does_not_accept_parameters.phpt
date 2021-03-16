--TEST--
close() does not accept parameters.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";

$c = new \SAPNWRFC\Connection($config);

try {
    $c->close('foobar');
} catch(\SAPNWRFC\ConnectionException $e) {
    echo "ok";
}
--EXPECT--
ok
