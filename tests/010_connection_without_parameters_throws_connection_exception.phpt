--TEST--
Connection without parameters throws.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
try {
    $c = new \SAPNWRFC\Connection();
} catch(\Throwable $t) {
    echo $t->getMessage() . PHP_EOL;
}
--EXPECTF--
SAPNWRFC\Connection::__construct() expects at least 1 %s, %d given
