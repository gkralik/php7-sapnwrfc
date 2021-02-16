--TEST--
Throws FunctionCallException if not given string for RFC STRING parameter.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
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
