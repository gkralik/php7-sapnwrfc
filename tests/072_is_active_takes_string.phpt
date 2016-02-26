--TEST--
isParameterActive() accepts only a string argument.
--SKIPIF--
<?php include("should_run_online_tests.inc"); ?>
--FILE--
<?php
$config = include "sapnwrfc.config.inc";
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
test($f, 0);
test($f, []);
test($f, false);

--EXPECT--
ok
fail
fail
fail
