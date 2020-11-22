--TEST--
RemoteFunction::invoke() takes optional $options array
--SKIPIF--
<?php include(__DIR__ . "/skipif_no_online_tests.inc"); ?>
--FILE--
<?php

$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);

$f = $c->getFunction('RFC_PING');

function test($f, $param) {
    try {
        $f->invoke([], $param);
    } catch(Throwable $t) {
        echo get_class($t), ": ", $t->getMessage(), "\n";
    }
}

$f->invoke([]);
test($f, []);
test($f, null);
test($f, 'foobar');
test($f, new \stdClass);
test($f, false);
test($f, 0);

--EXPECTF--
TypeError: Argument 2 passed to SAPNWRFC\RemoteFunction::invoke() must be of the type array, %s given
TypeError: Argument 2 passed to SAPNWRFC\RemoteFunction::invoke() must be of the type array, %s given
TypeError: Argument 2 passed to SAPNWRFC\RemoteFunction::invoke() must be of the type array, %s given
TypeError: Argument 2 passed to SAPNWRFC\RemoteFunction::invoke() must be of the type array, %s given
TypeError: Argument 2 passed to SAPNWRFC\RemoteFunction::invoke() must be of the type array, %s given