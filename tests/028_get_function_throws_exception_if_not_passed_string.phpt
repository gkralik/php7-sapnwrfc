--TEST--
getFunction() throws ConnectionException if parameter is not string.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

function test($c, $param) {
    try {
        $f = $c->getFunction($param);
        echo "ok\n";
    } catch(\SAPNWRFC\ConnectionException $e) {
        echo "fail\n";
    }
}

test($c, 'RFC_PING');
test($c, []);
test($c, new \stdClass);
--EXPECT--
ok
fail
fail
