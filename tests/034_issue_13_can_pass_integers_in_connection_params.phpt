--TEST--
Integer parameters can be passed in connection options (eg trace => 0)
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";

try {
    $c = new \SAPNWRFC\Connection(array_merge($config, [
        'trace'  => 0,
    ]));

    echo "ok";
    // should not produce a segfault
} catch(\Exception $e) {
    echo "fail";
} 
--EXPECT--
ok
