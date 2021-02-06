--TEST--
version() returns version string x.y.z
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
echo \SAPNWRFC\Connection::version();
--EXPECTREGEX--
\d\.\d\.\d(-.*)?
