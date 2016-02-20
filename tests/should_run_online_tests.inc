<?php

require 'skipif.inc';

$path = dirname(__FILE__);

if (!isset($_ENV["RUN_ONLINE_TESTS"]) || (int)$_ENV["RUN_ONLINE_TESTS"] != 1) {
    die('skip Online tests not enabled (use RUN_ONLINE_TESTS=1 env var)');
}

if (!file_exists($path . DIRECTORY_SEPARATOR .'sapnwrfc.config.inc')) {
    die('skip No configuration file (sapnwrfc.config.inc) provided');
}

$config = include $path . DIRECTORY_SEPARATOR . 'sapnwrfc.config.inc';
if(!is_array($config)) {
    die('skip Configuration file (sapnwrfc.config.inc) given, but is not an array');
}
