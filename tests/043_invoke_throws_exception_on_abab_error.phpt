--TEST--
invoke() throws FunctionCallException on ABAP error and sets "errorInfo" in exception.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('RFC_RAISE_ERROR');

try {
    $f->invoke([]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    $errorInfo = $e->getErrorInfo();
    var_dump(is_array($errorInfo));
    var_dump($errorInfo["code"]);
    var_dump($errorInfo["abapMsgClass"]);
    var_dump($errorInfo["abapMsgType"]);
    var_dump($errorInfo["abapMsgNumber"]);
}
--EXPECT--
bool(true)
int(4)
string(2) "SR"
string(1) "E"
string(3) "006"
