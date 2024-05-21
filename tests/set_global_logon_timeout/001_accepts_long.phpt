--TEST--
setGlobalLogonTimeout() does only accept a long parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php

function test(...$params) {
    try {
        \SAPNWRFC\Connection::setGlobalLogonTimeout(...$params);
        echo "ok\n";
    } catch(TypeError|ArgumentCountError $e) {
        echo "fail\n";
    }
}

test(60);
test("60");
test([]);
test();
--EXPECT--
ok
ok
fail
fail
