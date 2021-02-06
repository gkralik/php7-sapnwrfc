--TEST--
invoke() accepts only array parameter.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/sapnwrfc.config.inc');
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

function test($f, $param) {
    try {
        $f->invoke($param);
        echo "fail\n";
    } catch(TypeError $e) {
        echo "ok\n";
    }
}

test($f, null);
test($f, "foobar");
test($f, new \stdClass);
test($f, 1);
test($f, 1.3);
--EXPECT--
ok
ok
ok
ok
ok
