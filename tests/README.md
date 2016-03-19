# Tests

To run the tests, simply type `make test`.

By default, the tests that need interaction with a live SAP system are disabled.
To run all tests, you have to provide a configuration file `sapnwrfc.config.inc` in this (the `tests`) directory.
Simply copy the example file (`sapnwrfc.config.inc.dist`) and fill in your connection details.

If a configuration file is provided, all tests are executed when running `make test`.
