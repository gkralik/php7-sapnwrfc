--TEST--
isParameterActive() accepts only a string argument.
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
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
