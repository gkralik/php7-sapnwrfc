--TEST--
setParameterActive() throws FunctionCallException if connection is closed.
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

try {
    $f = $c->getFunction('RFC_STRUCTURE');
    $c->close();
    $f->setParameterActive('IMPORTSTRUCT', false);
    echo "fail";
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
