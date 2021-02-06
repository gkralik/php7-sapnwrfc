--TEST--
invoke() throws FunctionCallException given an invalid RFC parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('STFC_CONNECTION');

try {
    $f->invoke([
        'IDONTEXIST' => 'foobar',
    ]);
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
