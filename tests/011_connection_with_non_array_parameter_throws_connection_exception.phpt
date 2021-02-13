--TEST--
Connection with a non-array parameter throws.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
function testConnection($param) {
    try {
        $c = new \SAPNWRFC\Connection($param);
        return true;
    } catch(\Exception $e) { // PHP 7
        return false;
    } catch(\TypeError $e) { // PHP 8
        return false;
    }
}

var_dump(testConnection(null));
var_dump(testConnection('foobar'));
var_dump(testConnection(new \stdClass));
var_dump(testConnection(false));
var_dump(testConnection(0));
--EXPECT--
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
