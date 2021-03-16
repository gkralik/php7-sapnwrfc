--TEST--
setParameterActive() takes a string and a boolean argument.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('STFC_STRUCTURE');

function test($f, $p1, $p2) {
    try {
        $f->setParameterActive($p1, $p2);
        echo "ok\n";
    } catch(TypeError $e) {
        echo "fail\n";
    }
}

test($f, "IMPORTSTRUCT", false);
test($f, "IMPORTSTRUCT", []);

test($f, "RFCTABLE", true);
test($f, ["one", "two"], false);
--EXPECT--
ok
fail
ok
fail
