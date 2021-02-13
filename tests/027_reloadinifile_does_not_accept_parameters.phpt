--TEST--
reloadIniFile() does not accept parameters.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
try {
    \SAPNWRFC\Connection::reloadIniFile('foo');
} catch(\Throwable $t) {
    echo $t->getMessage() . PHP_EOL;
}
--EXPECTF--
SAPNWRFC\Connection::reloadIniFile() expects exactly 0 %s, %d given