--TEST--
version() returns version string x.y.z
--SKIPIF--
<?php include __DIR__ . "/skipif.inc"; ?>
--FILE--
<?php
echo \SAPNWRFC\Connection::version();
--EXPECTREGEX--
\d\.\d\.\d(-.*)?
