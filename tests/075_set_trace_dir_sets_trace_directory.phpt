--TEST--
setTraceDir() sets trace directory.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$dir = __DIR__ . DIRECTORY_SEPARATOR . 'traces';

if(!is_dir($dir)) {
    mkdir($dir);
}

\SAPNWRFC\Connection::setTraceDir($dir);

$config = require(__DIR__ . '/sapnwrfc.config.inc');
$config['trace'] = \SAPNWRFC\Connection::TRACE_LEVEL_FULL;
$c = new \SAPNWRFC\Connection($config);
$f = $c->getFunction('RFC_PING');
$f->invoke([]);

// make sure there is a trace file in our trace dir
$files = glob($dir . DIRECTORY_SEPARATOR . 'rfc*.trc');
var_dump(count($files) > 0);

--CLEAN--
<?php
$dir = __DIR__ . DIRECTORY_SEPARATOR . 'traces';

// remove trace files
$files = glob($dir . DIRECTORY_SEPARATOR . '*.trc');
if(count($files) > 0) {
    array_map(function($f) {
        unlink($f);
    }, $files);
}

rmdir($dir);
--EXPECT--
bool(true)
