--TEST--
Function handle can be unset and looked up again.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/../sapnwrfc.config.inc');

$c = new \SAPNWRFC\Connection($config);
$sysId = $c->getAttributes()['sysId'];

try {
    // repeated lookup fails if unset happens and cache is not cleared (sysId!!!)

    $f1 = $c->getFunction('RFC_PING');
    $f1->invoke([]);

    unset($f1); // unset the first

    \SAPNWRFC\clearFunctionDescCache('RFC_PING', $sysId);

    $f2 = $c->getFunction('RFC_PING');
    $f2->invoke([]);

} catch (\SAPNWRFC\FunctionCallException $ex) {
    echo $ex->getMessage() . PHP_EOL;
    var_dump($ex->getErrorInfo());

    //CALL_FUNCTION_NOT_FOUND
}
--EXPECT--
