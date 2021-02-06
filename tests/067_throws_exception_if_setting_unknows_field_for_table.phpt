--TEST--
Throws FunctionCallException if setting unkown field for RFC TABLE.
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
    "RFCTABLE" => [
        'UNKOWN_FIELD' => 'foobar', //< ERROR
    ],
];

$f = $c->getFunction("STFC_STRUCTURE");
$f->setParameterActive('IMPORTSTRUCT', false);
try {
    $f->invoke($params);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
