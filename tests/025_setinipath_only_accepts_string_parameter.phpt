--TEST--
setIniPath() does only accept a string parameter.
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
function test($param) {
    try {
        \SAPNWRFC\Connection::setIniPath($param);
        echo "ok\n";
    } catch(\SAPNWRFC\ConnectionException $e) {
        echo "fail\n";
    }
}

test('.');
test(0);
test(false);
test([]);
test(new \stdClass);
test(1.1);
--EXPECT--
ok
fail
fail
fail
fail
fail
--XFAIL--
Seems like bool and int and double get coerced to a string...
