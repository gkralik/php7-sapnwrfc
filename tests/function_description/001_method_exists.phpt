--TEST--
RemoteFunction::getFunctionDescription() exists
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
?>
--FILE--
<?php

var_dump(method_exists('\SAPNWRFC\RemoteFunction', 'getFunctionDescription'));

--EXPECT--
bool(true)