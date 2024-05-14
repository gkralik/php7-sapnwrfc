<?php

/**
 * This is a stub file of the extensions public interface to enable
 * code completion in IDEs.
 */
namespace SAPNWRFC;

trigger_error('This file is intended for IDE parsers/static analyzers and should not be included.', E_USER_WARNING);

class Exception extends \RuntimeException
{
    /**
     * Detailed RFC/ABAP error information.
     *
     * $errorInfo contains at least the "code", "key" and "message" keys from
     * the RFC library.
     * If the error is an ABAP error, the following additional keys are
     * available:
     *    "abapMsgClass", "abapMsgType", "abapMsgNumber", "abapMsgV1",
     *    "abapMsgV2", "abapMsgV3", "abapMsgV4"
     *
     * @var array
     */
    protected $errorInfo;

    /**
     * Getter for the errorInfo property.
     *
     * @returns array|null
     */
    public function getErrorInfo()
    {
    }
}

class ConnectionException extends Exception
{
}

class FunctionCallException extends Exception
{
}

class Connection
{
    const TRACE_LEVEL_OFF = 0;
    const TRACE_LEVEL_BRIEF = 1;
    const TRACE_LEVEL_VERBOSE = 2;
    const TRACE_LEVEL_FULL = 3;

    /**
     * Connect to the system using the given parameters.
     *
     * @param array $parameters Connection parameters.
     *
     * @throws ConnectionException if the connection fails.
     */
    public function __construct(array $parameters)
    {
    }

    /**
     * Get the connection attributes.
     *
     * @return array Array of connection attributes.
     *
     * @throws ConnectionException if the connection attributes could not be
     *                             fetched.
     */
    public function getAttributes()
    {
    }

    /**
     * @return bool True if ping successful.
     *
     * @throws ConnectionException if the ping failed.
     */
    public function ping()
    {
    }

    /**
     * Lookup a RFC function and return a RemoteFunction object.
     *
     * @param string $functionnName Name of the function.
     *
     * @return RemoteFunction A RemoteFunction class for the RFC function.
     *
     * @throws FunctionCallException if the lookup fails or an error is
     *                               returned during parameter parsing.
     */
    public function getFunction($functionName)
    {
    }

    /**
     * Close the connection.
     *
     * @return bool True if the connection was closed, false if the connection
     *              is closed already.
     *
     * @throws ConnectionException if the connection could not be closed.
     */
    public function close()
    {
    }

    /**
     * Sets the path to the sapnwrfc.ini file.
     *
     * By default, the INI file is searched for in the current directory.
     *
     * @param string $path Path to the sapnwrfc.ini file.
     *
     * @return bool True if path was set.
     *
     * @throws ConnectionException if path could not be set.
     */
    public static function setIniPath($path)
    {
    }

    /**
     * Reload the INI file.
     *
     * Searches for the INI file either in the path set by
     * Connection::setIniFile() or in the current directory.
     *
     * @return bool True if INI file was reloaded.
     *
     * @throws ConnectionException if the INI file could not be reloaded.
     */
    public static function reloadIniFile()
    {
    }

    /**
     * Set trace directory.
     *
     * @param string $path Path to trace directory (must exist).
     *
     * @return bool True if path was set.
     *
     * @throws ConnectionException if path could not be set.
     */
    public static function setTraceDir($path)
    {
    }

    /**
     * Set trace level.
     *
     * @param string $level Trace level.
     *
     * @return bool True if level was set.
     *
     * @throws ConnectionException if level could not be set.
     */
    public static function setTraceLevel($level)
    {
    }

    /**
     * Get the extension version.
     *
     * @return string The extension version.
     */
    public static function version()
    {
    }

    /**
     * Get the RFC SDK version.
     *
     * @return string The RFC SDK version.
     */
    public static function rfcVersion()
    {
    }
}

class RemoteFunction
{
    /**
     * Invoke the RFC function.
     *
     * @param array $parameters Function parameters.
     * @param array $options Additional invoke options. Only 'rtrim' supported for now.
     * @return array Return value from the backend.
     *
     * @throws FunctionCallException if any error occurs during execution.
     */
    public function invoke(array $parameters, array $options = [])
    {
    }

    /**
     * Make a parameter active or inactive.
     *
     * @param string $parameterName The parameter to modify.
     * @param bool   $isActive      True to activate the parameter, false to deactivate.
     *
     * @throws FunctionCallException if the parameter status could not be set.
     */
    public function setParameterActive($parameterName, $isActive)
    {
    }

    /**
     * Check if a parameter is active or inactive.
     *
     * @param string $parameterName The parameter to check.
     *
     * @return bool True if parameter is active, false if not.
     */
    public function isParameterActive($parameterName)
    {
    }
}
