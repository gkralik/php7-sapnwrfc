--TEST--
setTraceLevel() does only accept a long parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php

function test($param) {
    try {
        \SAPNWRFC\Connection::setTraceLevel($param);
        echo "ok\n";
    } catch(TypeError $e) {
        echo "fail\n";
    }
}

test(0);
test(1);
test(2);
test(3);
test(\SAPNWRFC\Connection::TRACE_LEVEL_VERBOSE);
test([]);
test(new \stdClass);
--EXPECT--
ok
ok
ok
ok
ok
fail
fail
