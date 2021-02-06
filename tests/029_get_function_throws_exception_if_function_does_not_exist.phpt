--TEST--
getFunction() throws FunctionCallException if function does not exist.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

try {
    $c->getFunction('Z_I_DONT_EXIST');
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo 'ok';
}
--EXPECT--
ok
