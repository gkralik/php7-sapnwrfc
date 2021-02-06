--TEST--
An existing Function can be called after the cache was cleared.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
use \SAPNWRFC\Connection;
use function \SAPNWRFC\clearFunctionDescCache;

$config = require(__DIR__ . '/../sapnwrfc.config.inc');
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