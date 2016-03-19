<?php

require 'skipif.inc';

$path = dirname(__FILE__);

if (!file_exists($path . DIRECTORY_SEPARATOR .'sapnwrfc.config.inc')) {
    die('skip DISABLED. Create configuration file to enable');
}

$config = include $path . DIRECTORY_SEPARATOR . 'sapnwrfc.config.inc';
if(!is_array($config)) {
    die('skip Configuration file given, but is not an array');
}
