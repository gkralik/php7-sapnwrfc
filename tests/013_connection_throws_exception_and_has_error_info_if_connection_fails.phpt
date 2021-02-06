--TEST--
Connection throws ConnectionException with errorInfo set if connection fails.
--SKIPIF--
<?php
require_once(__DIR__ . '/skipif.inc');
?>
--FILE--
<?php
try {
    $c = new \SAPNWRFC\Connection([
        'ashost' => 'does.not.exist.local',
        'sysnr'  => '00',
        'client' => '123',
        'user' => 'DEMO',
        'passwd' => 'XXXX',
        'trace'  => \SAPNWRFC\Connection::TRACE_LEVEL_OFF,
    ]);
} catch(\SAPNWRFC\ConnectionException $e) {
    $errorInfo = $e->getErrorInfo();
    var_dump(is_array($errorInfo));
    var_dump(!empty($errorInfo["code"]));
    var_dump(!empty($errorInfo["key"]));
    var_dump(!empty($errorInfo["message"]));
}
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
