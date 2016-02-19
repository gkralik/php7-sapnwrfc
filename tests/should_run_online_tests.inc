<?php

require 'skipif.inc';

if (!isset($_ENV["RUN_ONLINE_TESTS"]) || (int)$_ENV["RUN_ONLINE_TESTS"] != 1) {
    die('skip Online tests not enabled (use RUN_ONLINE_TESTS=1 env var)');
}

if (!file_exists('sapnwrfc.config.inc')) {
    die('skip No configuration file (sapnwrfc.config.inc) provided');
}

$config = include 'sapnwrfc.config.inc';
if(!is_array($config)) {
    die('skip Configuration file (sapnwrfc.config.inc) given, but is not an array');
}
