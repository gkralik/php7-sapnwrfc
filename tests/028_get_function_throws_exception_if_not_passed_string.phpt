--TEST--
getFunction() accepts only string parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

function test($c, $param) {
    try {
        $c->getFunction($param);
        echo "ok\n";
    } catch(TypeError $e) {
        echo "fail\n";
    } catch(\SAPNWRFC\FunctionCallException $e) {
        echo "fail_lookup\n";
    }
}

test($c, 'RFC_PING');
test($c, 0);
test($c, []);
test($c, new \stdClass);
--EXPECT--
ok
fail_lookup
fail
fail
