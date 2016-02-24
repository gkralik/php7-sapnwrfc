--TEST--
invoke() throws FunctionCallException on ABAP error and sets "errorInfo" in exception.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('RFC_RAISE_ERROR');

try {
    $f->invoke([]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    var_dump(is_array($e->errorInfo));
    var_dump($e->errorInfo["code"]);
    var_dump($e->errorInfo["abapMsgClass"]);
    var_dump($e->errorInfo["abapMsgType"]);
    var_dump($e->errorInfo["abapMsgNumber"]);
}
--EXPECT--
bool(true)
int(4)
string(2) "SR"
string(1) "E"
string(3) "006"
