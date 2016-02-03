--TEST--
Check for SAPNWRFC\ConnectionException presence
--SKIPIF--
<?php if (!extension_loaded("sapnwrfc")) print "skip"; ?>
--FILE--
<?php
try {
    throw new \SAPNWRFC\ConnectionException('error');
} catch(\SAPNWRFC\ConnectionException $e) {
    print $e->getMessage();
}
--EXPECT--
error
