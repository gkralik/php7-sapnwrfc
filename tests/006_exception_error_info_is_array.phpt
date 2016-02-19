--TEST--
Exception "errorInfo" is array with at least "key", "code" and "message".
--SKIPIF--
<?php include("skipif.inc"); ?>
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
} catch(\SAPNWRFC\Exception $e) {
    var_dump(is_array($e->errorInfo));
    var_dump(!empty($e->errorInfo["code"]));
    var_dump(!empty($e->errorInfo["key"]));
    var_dump(!empty($e->errorInfo["message"]));
}
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
