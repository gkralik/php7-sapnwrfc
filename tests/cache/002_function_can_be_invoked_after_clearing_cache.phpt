--TEST--
An existing Function can be called after the cache was cleared.
--SKIPIF--
<?php include __DIR__ . "/../skipif_no_online_tests.inc"; ?>
--FILE--
<?php
use \SAPNWRFC\Connection;
use function \SAPNWRFC\clearFunctionDescCache;

$config = include __DIR__ . "/../sapnwrfc.config.inc";;
$c = new Connection($config);

$f = $c->getFunction('RFC_PING');
var_dump($f->invoke());

clearFunctionDescCache('RFC_PING');

var_dump($f->invoke());
--EXPECT--
array(0) {
}
array(0) {
}