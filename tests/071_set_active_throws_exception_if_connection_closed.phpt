--TEST--
setParameterActive() throws FunctionCallException if connection is closed.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
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
