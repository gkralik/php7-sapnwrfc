--TEST--
setTraceDir() throws ConnectionException if path does not exist.
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"); ?>
--FILE--
<?php

try {
    \SAPNWRFC\Connection::setTraceDir('/this/path/does/not/exist');
    echo "ok\n";
} catch(\SAPNWRFC\ConnectionException $e) {
    echo "fail\n";
}
--EXPECT--
fail
