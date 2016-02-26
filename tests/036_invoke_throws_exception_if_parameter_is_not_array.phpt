--TEST--
invoke() accepts only array parameter.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

function test($f, $param) {
    try {
        $f->invoke($param);
        echo "fail\n";
    } catch(TypeError $e) {
        echo "ok\n";
    }
}

test($f, null);
test($f, "foobar");
test($f, new \stdClass);
test($f, 1);
test($f, 1.3);
--EXPECT--
ok
ok
ok
ok
ok
