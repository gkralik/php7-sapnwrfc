--TEST--
setIniPath() does only accept a string parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php

function test($param) {
    try {
        \SAPNWRFC\Connection::setIniPath($param);
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
