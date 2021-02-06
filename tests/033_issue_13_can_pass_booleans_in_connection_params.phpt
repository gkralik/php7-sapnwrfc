--TEST--
Boolean parameters can be passed in connection options (eg trace => false)
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');

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
