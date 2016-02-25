--TEST--
Throws FunctionCallException if not given string for RFC STRING parameter.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$params = [
    "ABAP_STRING" => "foobar",
];

$f = $c->getFunction("RFC_METADATA_TEST");
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok\n";
}
--EXPECT--
ok
