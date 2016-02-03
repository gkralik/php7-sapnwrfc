--TEST--
Check for SAPNWRFC\FunctionCallException presence
--SKIPIF--
<?php if (!extension_loaded("sapnwrfc")) print "skip"; ?>
--FILE--
<?php
try {
    throw new \SAPNWRFC\FunctionCallException('error');
} catch(\SAPNWRFC\FunctionCallException $e) {
    print $e->getMessage();
}
--EXPECT--
error
