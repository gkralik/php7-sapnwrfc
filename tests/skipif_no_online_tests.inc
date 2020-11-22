<?php

if(!extension_loaded('sapnwrfc')) {
    die("skip sapnwrfc extension not loaded");
}

// Checks if we have a connection configuration in the current directory,
// enabling us to run tests against SAP system.
// The connection configuration is expected in a file `sapnwrfc.config.inc`.
// See `sapnwrfc.config.in.dist` for an example.

$configPath = __DIR__ . DIRECTORY_SEPARATOR . 'sapnwrfc.config.inc';

if (!file_exists($configPath)) {
    die('skip NO ONLINE TESTS: create configuration `sapnwrfc.config.inc` file to enable.');
}

$config = include $configPath;
if(!is_array($config)) {
    die('skip ONLINE TESTS: configuration file expected to return array.');
}
