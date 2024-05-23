<?php

/**
 * This is a stub file of the extensions public interface to enable
 * code completion in IDEs.
 */
namespace SAPNWRFC;

die('This file is intended for IDE parsers and should not be included.');

/**
 * Clear the function desc cache for $functionName.
 *
 * Clears the default repository. If $repositoryId is passed, the cache
 * repository matching $repository is cleard as well.
 *
 * @since 1.3.0
 *
 * @param string $functionName Function name.
 * @param string $repositoryId The cache repository to use. Defaults to null.
 *                             If passed, the repository is cleared in addition
 *                             to the default repository.
 *
 * @return bool True if the call succeeded (this does not necessarily mean
 *              that a cache entry was found).
 *
 */
function clearFunctionDescCache(string $functionName, string $repositoryId = null): bool {}

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
    public function getErrorInfo(): ?array {}
}

class ConnectionException extends Exception {}

class FunctionCallException extends Exception {}

class Connection
{
    /**
     * Off. Only severe errors are logged to the dev_rfc.log file.
     * @var int
     */
    public const TRACE_LEVEL_OFF = 0;

    /**
     * Brief. All API calls (except for the setter and getter functions) and important attributes like codepages,
     * RFC headers, logon parameters are traced. Trace is written to a file named rfc<pid>.trc or
     * rfc<pid>_<tid>.trc, depending on whether tracing is done on a "per-process" basis or a "per-thread" basis.
     * <pid> is the current process ID, <tid> the current thread ID.
     * @var int
     */
    public const TRACE_LEVEL_BRIEF = 1;

    /**
     * Verbose. In addition to 1, the values of the "scalar" RFC parameters as well as the contents of the network
     * containers are traced. Scalar parameters are primitive types (CHAR, INT, FLOAT, etc) and flat structures.
     * @var int
     */
    public const TRACE_LEVEL_VERBOSE = 2;

    /**
     * Detailed. In addition to 2 the contents of nested structures and tables and hexdumps are traced.
     * @var int
     */
    public const TRACE_LEVEL_DETAILED = 3;

    /**
     * Full. In addition to 3 all API calls of setter and getter functions and table operations are traced.
     * @var int
     */
    public const TRACE_LEVEL_FULL = 4;

    /**
     * Connect to the system using the given parameters.
     *
     * @param array $parameters Connection parameters (see `sapnwrfc.ini` documentation for supported keys)
     * @param array $options Additional options {
     *      @var bool $use_function_desc_cache Use function desc cache (defaults to `true`)
     * }
     *
     * @throws ConnectionException if the connection fails.
     */
    public function __construct(array $parameters, array $options = []) {}

    /**
     * Get the connection attributes.
     *
     * @return array Array of connection attributes.
     *
     * @throws ConnectionException if the connection attributes could not be
     *                             fetched.
     */
    public function getAttributes(): array {}

    /**
     * @return bool True if ping successful.
     *
     * @throws ConnectionException if the ping failed.
     */
    public function ping(): bool {}

    /**
     * Lookup a RFC function and return a RemoteFunction object.
     *
     * @param string $functionnName   Name of the function.
     * @param bool   $invalidateCache If true, invalidates the function desc cache.
     *
     * @return RemoteFunction A RemoteFunction class for the RFC function.
     *
     * @throws FunctionCallException if the lookup fails or an error is
     *                               returned during parameter parsing.
     */
    public function getFunction(string $functionName, bool $invalidateCache = false): RemoteFunction {}

    /**
     * Retrieve a SSO ticket from the connection.
     *
     * For this to work, the connection must be opened with parameter `GETSSO2=1`
     * and the profile parameter `login/create_sso2_ticket` must be set to a value
     * different from '0' in the backend.
     *
     * Note: To retrieve a SSO ticket from the connection, SDK version 7.50.1 or
     * later is required.
     *
     * @return string The SSO ticket.
     *
     * @throws ConnectionException if no SSO ticket could be retrieved.
     */
    public function getSSOTicket(): string {}

    /**
     * Close the connection.
     *
     * @return bool True if the connection was closed, false if the connection
     *              is closed already.
     *
     * @throws ConnectionException if the connection could not be closed.
     */
    public function close(): bool {}

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
    public static function setIniPath(string $path): bool {}

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
    public static function reloadIniFile(): bool {}

    /**
     * Set trace directory.
     *
     * @param string $path Path to trace directory (must exist).
     *
     * @return true True if path was set (BC).
     *
     * @throws ConnectionException if path could not be set.
     */
    public static function setTraceDir(string $path): bool {}

    /**
     * Set trace level.
     *
     * @param int $level Trace level.
     *
     * @return true True if trace level was set (BC).
     *
     * @throws ConnectionException if level could not be set.
     */
    public static function setTraceLevel(int $level): bool {}

    /**
     * Sets the global logon timeout in seconds.
	 *
	 * Sets the timeout for how long the logon in the ABAP backend can take when opening a connection.
	 * The default value is 60 seconds.
	 *
	 * The timeout can also be set via <code>RFC_GLOBAL_LOGON_TIMEOUT</code> in the <code>DEFAULT</code>
     * section of the <em>sapnwrfc.ini</em> file.
     *
     * @param int $timeout Timeout in seconds (1 - 3600).
     *
     * @throws ConnectionException if timeout cannot be set or is out of range.
     */
    public static function setGlobalLogonTimeout(int $timeout): void {}

    /**
     * Get the extension version.
     *
     * @return string The extension version.
     */
    public static function version(): string {}

    /**
     * Get the RFC SDK version.
     *
     * @return string The RFC SDK version.
     */
    public static function rfcVersion(): string {}
}

class RemoteFunction
{
    /**
     * Invoke the RFC function.
     *
     * @param array $parameters Function parameters.
     * @param array $options Additional invoke options {
     *      @var bool $rtrim Right trim CHAR field values.
     * }
     * @return array Return value from the backend.
     *
     * @throws FunctionCallException if any error occurs during execution.
     */
    public function invoke(array $parameters = [], array $options = []): array {}

    /**
     * Make a parameter active or inactive.
     *
     * @param string $parameterName The parameter to modify.
     * @param bool   $isActive      True to activate the parameter, false to deactivate.
     *
     * @throws FunctionCallException if the parameter status could not be set or the connection is already closed.
     */
    public function setParameterActive(string $parameterName, bool $isActive): void {}

    /**
     * Check if a parameter is active or inactive.
     *
     * @param string $parameterName The parameter to check.
     *
     * @return bool True if parameter is active, false if not.
     * @throws FunctionCallException if the connection is already closed.
     */
    public function isParameterActive(string $parameterName): bool {}

    /**
     * Get the function's parameter description.
     *
     * @return array The parameter descriptions, indexed by parameter name.
     *
     * @throws FunctionCallException if the interface description cannot be retrieved.
     */
    public function getFunctionDescription(): array {}

    /**
     * Get the function's name.
     *
     * @return string The function name.
     */
    public function getName(): string {}
}
