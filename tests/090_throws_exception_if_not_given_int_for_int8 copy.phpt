--TEST--
Throws TypeError if not given integer for RFC INT8 parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
//skipif_online_tests_disabled();
die('skip No suitable RFC to test.');
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$params = [
];

$f = $c->getFunction("XXX");

$f->invoke($params);

--EXPECTF--
Fatal error: Uncaught TypeError: Failed to set %s parameter "%s". Expected %s, %s given in %s.php:%d
Stack trace:
#0 %s(%d): SAPNWRFC\RemoteFunction->invoke(Array)
#1 {main}
  thrown in %s.php on line %d