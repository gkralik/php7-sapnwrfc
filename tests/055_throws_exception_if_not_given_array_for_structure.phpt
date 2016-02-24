--TEST--
Throws FunctionCallException if not given array for RFC STRUCTURE.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$params = [
    "IMPORTSTRUCT" => 'foobar', //< ERROR
];

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('RFCTABLE', false);
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
