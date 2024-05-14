--TEST--
Connection::getSSOTicket() fetches SSO ticket
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

$ssoTicket = $c->getSSOTicket();
var_dump(is_string($ssoTicket));
--XFAIL--
This test might fail if the profile parameter login/create_sso2_ticket is set to 0.
--EXPECT--
bool(true)
