--TEST--
Connection::__construct() throws exception if given anything other than array
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php
function testConnection($input) {
    try {
        new \SAPNWRFC\Connection($input);
        print "ok\n";
    } catch(\Exception $e) {
        print "invalid\n";
    }
}

testConnection('string');
testConnection(8);
testConnection(new \stdClass());
testConnection(false);
--EXPECT--
invalid
invalid
invalid
invalid
