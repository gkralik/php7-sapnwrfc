--TEST--
Connection::getSSOTicket() fails if connection closed.
--SKIPIF--
<?php
require_once(__DIR__ . '/../skipif.inc');
skipif_online_tests_disabled();
?>
--FILE--
<?php
$config = require(__DIR__ . '/../sapnwrfc.config.inc');

// Set the GETSSO2 parameter
$config['GETSSO2'] = '1';

$c = new \SAPNWRFC\Connection($config);
$c->close();

try {
    $ssoTicket = $c->getSSOTicket();
} catch (SAPNWRFC\ConnectionException $ex) {
    echo $ex->getMessage() . PHP_EOL;
}
--EXPECTF--
Failed to retrieve SSO ticket: connection closed.
