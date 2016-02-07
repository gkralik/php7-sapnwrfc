# php7-sapnwrfc API

**NOTE: As the extension is a work in progress, this document may not always be up to date.**

```php
<?php

namespace SAPNWRFC {

class ConnectionException extends \RuntimeException {}

class FunctionCallException extends \RuntimeException {}

class Connection {
    /**
     * Connect to the system using the given parameters.
     *
     * @params array $connectionParams Connection parameters.
     * @throw ConnectionException if the connection fails.
     */
    public function __construct(array $connectionParams) {}

    /**
     * Get the connection attributes.
     *
     * @return array Array of connection attributes.
     * @throws ConnectionException if the connection attributes could not be
     *                             fetched.
     */
    public function attributes() {}

    /**
     * @return bool True if ping successful.
     * @throws ConnectionException if the ping failed.
     */
    public function ping() {}

    /**
     * Lookup a RFC function and return a FunctionEntry object.
     *
     * @param string $functionName Name of the function.
     * @throws FunctionCallException if the lookup fails or an error is
     *                               returned during parameter parsing.
     */
    public function getFunction($functionName) {}

    /**
     * Close the connection.
     *
     * @return bool True if the connection was closed, false if the connection
     *              is closed already.
     * @throws ConnectionException if the connection could not be closed.
     */
    public function close() {}

    /**
     * Sets the path to the sapnwrfc.ini file.
     *
     * By default, the INI file is searched for in the current directory.
     *
     * @param string $path Path to the sapnwrfc.ini file.
     * @return bool True if path was set.
     * @throws ConnectionException if path could not be set.
     */
    public static function setIniPath($path) {}

    /**
     * Reload the INI file.
     *
     * Searches for the INI file either in the path set by
     * Connection::setIniFile() or in the current directory.
     *
     * @return bool True if INI file was reloaded.
     * @throws ConnectionException if the INI file could not be reloaded.
     */
    public static function reloadIniFile() {}

    /**
     * Get the extension version.
     *
     * @return string The extension version.
     */
    public static function version() {}

    /**
     * Get the RFC SDK version.
     *
     * @return string The RFC SDK version.
     */
    public static function rfcVersion() {}
}

class FunctionEntry {
    public function invoke(array $parameters) {}

    public function activate($parameterName) {}

    public function deactivate($parameterName) {}
}

}
```
