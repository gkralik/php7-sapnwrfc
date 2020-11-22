--TEST--
Connection with empty array throws ConnectionException
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"); ?>
--FILE--
<?php
try {
    $c = new \SAPNWRFC\Connection([]);
} catch(\SAPNWRFC\ConnectionException $e) {
    echo 'ok';
}
--EXPECT--
ok
