--TEST--
Throws FunctionCallException if not given string for RFC XSTRING parameter.
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
    "ABAP_XSTRING" => "foobar",
];

$f = $c->getFunction("RFC_METADATA_TEST");
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok\n";
}
--EXPECT--
ok
