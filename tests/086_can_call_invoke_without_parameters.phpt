--TEST--
Can call invoke() without parameters
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
$config = include __DIR__ .  "/sapnwrfc.config.inc";
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('RFC_PING');

var_dump($f->invoke());
--EXPECT--
array(0) {
}
