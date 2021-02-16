--TEST--
Throws FunctionCallException if setting unkown field for RFC TABLE.
--SKIPIF--
<?php include __DIR__ . "/skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
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
