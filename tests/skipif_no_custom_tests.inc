<?php

$runCustomTests = getenv('ENABLE_CUSTOM_ABAP_TESTS') === '1';

if (!$runCustomTests) {
    die('skip NO CUSTOM TESTS: set up custom function modules and pass env ENABLE_CUSTOM_ABAP_TESTS=1');
}