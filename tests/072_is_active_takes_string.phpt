--TEST--
isParameterActive() accepts only a string argument.
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

function test($f, $p1) {
    try {
        $f->isParameterActive($p1);
        echo "ok\n";
    } catch(TypeError $e) {
        echo "fail\n";
    }
}

test($f, "IMPORTSTRUCT");
test($f, []);

--EXPECT--
ok
fail
