# php7-sapnwrfc API

```php
<?php

namespace SAPNWRFC {

class ConnectionException extends \RuntimeException {}

class FunctionCallException extends \RuntimeException {}

class Connection {
    public function __construct(array $loginParams) {}

    public function attributes() {}

    public function ping() {}

    public function getFunction($functionName) {}

    public function close() {}

    public static function setIniPath() {}

    public static function getIniPath() {}

    public static function version() {}

    public static function rfcVersion() {}
}

class Function {
    public function invoke(array $parameters) {}

    public function activate($parameterName) {}

    public function deactivate($parameterName) {}
}

}
```
