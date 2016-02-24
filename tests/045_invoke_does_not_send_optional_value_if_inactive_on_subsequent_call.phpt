--TEST--
invoke() does not send optional value on subsequent call if parameter inactive.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_RAISE_ERROR');

try {
    $f->invoke([
        'MESSAGETYPE' => 'W',
    ]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    var_dump($e->errorInfo["abapMsgType"]);
}

try {
    $f->setParameterActive('MESSAGETYPE', false);
    $f->invoke([]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    var_dump($e->errorInfo["abapMsgType"]);
}
--EXPECT--
string(1) "W"
string(1) "E"
