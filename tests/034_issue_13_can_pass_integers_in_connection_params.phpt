--TEST--
Integer parameters can be passed in connection options (eg trace => 0)
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
        'trace'  => 0,
    ]));

    echo "ok";
    // should not produce a segfault
} catch(\Exception $e) {
    echo "fail";
} 
--EXPECT--
ok
