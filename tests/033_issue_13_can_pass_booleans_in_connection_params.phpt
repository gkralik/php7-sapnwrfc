--TEST--
Boolean parameters can be passed in connection options (eg trace => false)
--SKIPIF--
<?php include "should_run_online_tests.inc"; ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";

try {
    $c = new \SAPNWRFC\Connection(array_merge($config, [
        'trace'  => false,
    ]));

    echo "ok";
    // should not produce a segfault
} catch(\Exception $e) {
    echo "fail";
} 
--EXPECT--
ok
