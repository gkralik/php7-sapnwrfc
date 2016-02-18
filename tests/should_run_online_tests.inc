<?php

require 'skipif.inc';

if (!isset($_ENV["RUN_ONLINE_TESTS"]) || (int)$_ENV["RUN_ONLINE_TESTS"] != 1) {
    die("skip Online tests not enabled (use RUN_ONLINE_TESTS env var)");
}

$config = include "sapnwrfc.config.inc";
if(!is_array($config)) {
    die("skip Config given, but is not an array");
}
