--TEST--
setTraceDir() does only accept a string parameter.
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"); ?>
--FILE--
<?php

function test($param) {
    try {
        \SAPNWRFC\Connection::setTraceDir($param);
        echo "ok\n";
    } catch(TypeError $e) {
        echo "fail\n";
    }
}

test('.');
test([]);
test(new \stdClass);
--EXPECT--
ok
fail
fail
