--TEST--
Throws FunctionCallException if given invalid format for RFC XSTRING parameter.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$params = [
    "ABAP_XSTRING" => "DEADBEEF_N",
];

$f = $c->getFunction("RFC_METADATA_TEST");
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok\n";
}
--EXPECT--
ok
