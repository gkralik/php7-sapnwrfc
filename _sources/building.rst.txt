.. _building-from-source:

Building from source
====================

Before attempting to build the extension, make sure the *SAP NW RFC library* is
installed and the :ref:`library is in the path <installing-nwrfcsdk-library-path>`.

See :ref:`installing-nwrfcsdk` for instructions.


Building on Linux
-----------------

.. code-block:: shell

    $ git clone https://github.com/gkralik/php7-sapnwrfc.git php-sapnwrfc
    $ cd php-sapnwrfc
    $ phpize
    $ ./configure
    $ make
    $ sudo make install

The build script looks for the *SAP NW RFC library* in the following locations
by default:

.. code-block:: none

    /usr/sap/nwrfcsdk
    /usr/local/sap/nwrfcsdk
    /usr/local/nwrfcsdk
    /opt/nwrfcsdk

If you installed the library in another location, replace the ``./configure`` step
above with ``./configure --with-sapnwrfc=/path/to/rfc-library``.


Building on Windows
-------------------

To build PHP 8+ for Windows, you need `Visual Studio 2019 or the Visual Studio 2019 Build Tools <https://learn.microsoft.com/en-us/visualstudio/releases/2019/history#release-dates-and-build-numbers>`_.
The workload *Desktop development with C++* must be installed.

The process of building PHP and extensions on Windows is `detailed in the PHP Wiki <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2>`_.

The build process described below follows the steps in `Building PECL extensions with phpize <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2#building_pecl_extensions_with_phpize>`_
and assumes you have PHP already installed on your system.

If you need to compile PHP itself, follow instructions from `Build your own PHP on Windows <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2>`_.

For this guide, we assume

  - we want to build the extension for PHP 8.3.7,
  - PHP 8.3.7 is installed at ``C:\php``
  - the *SAP NW RFC library* is in ``C:\nwrfcsdk`` and ``PATH`` is configured correctly.
  - Our working directory is ``C:\workspace``.


Set up a build environment
^^^^^^^^^^^^^^^^^^^^^^^^^^

Follow the steps to `set up a build enviroment as described here <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2>`_.

First, open a command line (``cmd.exe``).

Change to ``C:\workspace`` and fetch the `latest stable PHP SDK tag <https://github.com/php/php-sdk-binary-tools>`_:

.. code-block:: none

    $ git clone https://github.com/php/php-sdk-binary-tools.git php-sdk
    $ cd php-sdk

Now execute the starter script for the build environment:

.. code-block:: none

    $ phpsdk-vs16-x64.bat

All commands described from here on must be executed in the shell configured by the above command.


Building the extension using phpize
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

First, download the development package which corresponds to your pre-built PHP version and variant from `<https://windows.php.net/download/>`_.

In our case, we download *PHP 8.3.7* -> *VS16 x64 Non Thread Safe* -> *Development package (SDK to develop PHP extensions)*

Unpack the development package to ``C:\workspace\php-8.3.7-devel-vs16-x64``.

Now add the development package to the path:

.. code-block:: none

    $ set PATH=%PATH%;C:\workspace\php-8.3.7-devel-vs16-x64

Download and unpack or clone the source of the extension into ``C:\workspace``:

.. code-block:: none

    $ cd C:\workspace
    $ git clone https://github.com/gkralik/php7-sapnwrfc.git php-sapnwrfc

Change to the extension's source directory and invoke ``phpize`` and ``configure``,
passing the path to the installed PHP and the *SAP NW RFC library*:

.. code-block:: none

    $ cd php-sapnwrfc
    $ phpize
    $ configure --with-prefix=C:\php --with-sapnwrfc=C:\nwrfcsdk

Make sure the output of the ``configure`` command includes the following:

.. code-block:: none

    Enabled extensions:
    ----------------------
    | Extension | Mode   |
    ----------------------
    | sapnwrfc  | shared |
    ----------------------

Now build the extension:

.. code-block:: none

    $ nmake

The above command's output should include *EXT sapnwrfc build complete* near the end.

The build artifacts are located in ``x64\Release``
(or one of the `release directories <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2#release_directories>`_ depending on your build).


Running tests
^^^^^^^^^^^^^

After a successful build, you are encouraged to run tests:

.. code-block:: none

    $ nmake test

If running the tests fails with ``reason: sapnwrfc extension not loaded`` and the output includes an error similar to the one shown below,
you have either not correctly configured the path or you have a mismatch between ZTS and NTS versions:

.. code-block:: none

    Warning: PHP Startup: Unable to load dynamic library 'C:\\workspace\\php-sapnwrfc\\x64\\Release\\php_sapnwrfc.dll' (tried: C:\\workspace\\php-sapnwrfc\\x64\\Release\\php_sapnwrfc.dll (The specified module could not be found), C:\php\ext\php_C:\\workspace\\php-sapnwrfc\\x64\\Release\\php_sapnwrfc.dll.dll (The specified module could not be found)) in Unknown on line 0


You can update the path temporarily to make the tests run with the following command:

.. code-block:: none

    $ set PATH=%PATH%;C:\nwrfcsdk\lib
