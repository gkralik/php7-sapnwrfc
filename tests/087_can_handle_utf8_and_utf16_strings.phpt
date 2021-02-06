--TEST--
UTF-8 and UTF-16 strings are handled correctly.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = include 'sapnwrfc.config.inc';
$c = new \SAPNWRFC\Connection($config);


$f = $c->getFunction('SCP_STRING_ECHO');

$ret1 = $f->invoke(['IMP' => '😃']);

$rainbowFlagUTF16 = (string)0xD83CDFF3FE0F200DD83CDF08;
$ret2 = $f->invoke(['IMP' => $rainbowFlagUTF16]); // rainbow flag

var_dump($ret1['EXP'] === '😃');
var_dump($ret2['EXP'] === $rainbowFlagUTF16);

--EXPECT--
bool(true)
bool(true)
