--TEST--
Lookup the same function multiple times.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/../sapnwrfc.config.inc');
$config['use_function_desc_cache'] = true;

$c = new \SAPNWRFC\Connection($config);

try {
    $f1 = $c->getFunction('RFC_PING');
    $f1->invoke([]);

    $f2 = $c->getFunction('RFC_PING');
    $f2->invoke([]);
} catch (\SAPNWRFC\FunctionCallException $ex) {
    echo $ex->getMessage() . PHP_EOL;
    var_dump($ex->getErrorInfo());
}
--EXPECT--
