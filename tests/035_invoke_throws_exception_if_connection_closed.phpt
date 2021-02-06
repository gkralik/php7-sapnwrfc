--TEST--
invoke() throws FunctionCallException if connection closed.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$func = $c->getFunction('RFC_PING');
$c->close();

try {
    $func->invoke([]);
    echo "fail";
} catch(\SAPNWRFC\FunctionCallException $e) {
    echo "ok";
}
--EXPECT--
ok
