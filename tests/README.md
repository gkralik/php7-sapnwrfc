# Tests

To run the tests, simply type `make test`.

By default, the tests that need interaction with a live SAP system are disabled.
To run all tests, you have to provide a configuration file `sapnwrfc.config.inc` in the `tests` directory.
Simply copy the example file (`sapnwrfc.config.inc.dist`) and fill in your connection details.

If a configuration file is provided, all tests are executed when running `make test`.

Additionally, some tests require custom ABAP function modules to work.
To enable them, make sure the custom function modules exist in the target system (see `tests/fixtures`) and pass the environment variable `ENABLE_CUSTOM_ABAP_TESTS=1` to the `make test` invocation.