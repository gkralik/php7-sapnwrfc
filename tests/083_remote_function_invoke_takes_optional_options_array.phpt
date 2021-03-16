--TEST--
RemoteFunction::invoke() takes optional $options array
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php

$config = require(__DIR__ . '/sapnwrfc.config.inc');
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
TypeError: %s must be of type array, null given
TypeError: %s must be of type array, string given
TypeError: %s must be of type array, stdClass given
TypeError: %s must be of type array, bool given
TypeError: %s must be of type array, int given