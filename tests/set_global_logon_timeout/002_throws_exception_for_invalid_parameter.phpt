--TEST--
setGlobalLogonTimeout() throws ConnectionException if given an invalid timeout value.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php

function test($param) {
    try {
        \SAPNWRFC\Connection::setGlobalLogonTimeout($param);
        echo "ok\n";
    } catch(\SAPNWRFC\ConnectionException $e) {
        echo "fail\n";
    }
}

test(-1);
test(0);
test(1);
test(60);
test(3600);
test(3601);
--EXPECT--
fail
fail
ok
ok
ok
fail
