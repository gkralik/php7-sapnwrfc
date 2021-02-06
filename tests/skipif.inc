<?php

if(!extension_loaded('sapnwrfc')) {
    die('skip sapnwrfc extension not loaded');
}

/**
 * Skip test if online tests are disabled.
 *
 * To enable online tests, pass an environment variable SAPNWRFC_ONLINE=1
 * and create the configuration file `sapnwrfc.config.inc`.
 * See `sapnwrfc.config.inc.dist` for an example.
 */
function skipif_online_tests_disabled() {
    $enableOnline = getenv('SAPNWRFC_ONLINE') === '1';

    if (!$enableOnline) {
        die('skip Online tests disabled. Set SAPNWRFC_ONLINE=1 to enable');
    }

    if (!file_exists(__DIR__ . DIRECTORY_SEPARATOR . 'sapnwrfc.config.inc')) {
        die('skip Missing configuration file sapnwrfc.config.inc');
    }
}

/**
 * Skip test if custom function modules tests are disabled.
 *
 * To enable custom function module tests, pass an environment variable
 * SAPNWRFC_CUSTOM=1 and set up custom function modules in your SAP system.
 * See `fixtures/` for the custom function modules.
 */
function skipif_custom_tests_disabled() {
    $runCustomTests = getenv('SAPNWRFC_CUSTOM') === '1';

    if (!$runCustomTests) {
        die('skip Custom FM tests disabled: set up custom function modules and set SAPNWRFC_CUSTOM=1 to enable');
    }
}