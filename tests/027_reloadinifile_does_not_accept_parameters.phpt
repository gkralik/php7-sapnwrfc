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
} catch(\SAPNWRFC\ConnectionException $e) {
    echo 'ok';
}
--EXPECT--
ok
