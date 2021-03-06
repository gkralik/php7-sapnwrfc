--TEST--
Throws TypeError if not given array for RFC STRUCTURE.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$params = [
    "IMPORTSTRUCT" => 'foobar', //< ERROR
];

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('RFCTABLE', false);

$f->invoke($params);

--EXPECTF--
Fatal error: Uncaught TypeError: Failed to set %s parameter "%s". Expected %s, %s given in %s.php:%d
Stack trace:
#0 %s(%d): SAPNWRFC\RemoteFunction->invoke(Array)
#1 {main}
  thrown in %s.php on line %d