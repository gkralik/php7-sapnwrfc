.. _building-from-source:

Building from source
====================

Before attempting to build the extension, make sure the *SAP NW RFC library* is
installed. See :ref:`installing-nwrfcsdk` for instructions.

Building on Linux
-----------------

.. code-block:: shell

    $ git clone https://github.com/gkralik/php7-sapnwrfc.git
    $ cd php7-sapnwrfc
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

We try to provide pre-built extensions for Windows users (see the 
`release <https://github.com/gkralik/php7-sapnwrfc/releases>`_ page). 
If you don't find your desired version there or still want to build yourself, follow the instructions below.

To build PHP 8+ for Windows, you need Visual Studio 2019. To build PHP 7.4, Visual Studio 2017 is required.
The workload *Desktop development with C++* must be installed.

For this guide, we assume the base directory for the build to be ``C:\Workspace\php``
and we want to build the extension for PHP 8.0.

Set up a build environment
^^^^^^^^^^^^^^^^^^^^^^^^^^

Make sure you have a valid `build enviroment as described here <https://wiki.php.net/internals/windows/stepbystepbuild_sdk_2>`_.

First, open a command line (``cmd.exe``).

Change to ``C:\Workspace\php`` and fetch the `latest stable PHP SDK tag <https://github.com/Microsoft/php-sdk-binary-tools>`_:

.. code-block:: none

    $ git clone https://github.com/Microsoft/php-sdk-binary-tools.git php-sdk
    $ cd php-sdk
    $ git checkout php-sdk-2.2.0


Now execute the starter script for the build environment and create the buildtree:

.. code-block:: none

    $ phpsdk-vs16-x64.bat
    $ phpsdk_buildtree phpdev

Clone the `php7-sapnwrfc <https://github.com/gkralik/php7-sapnwrfc>`_ repository
(or download and extract a release ZIP) into the
``php-sdk\phpdev\vs16\x64\modules\sapnwrfc`` folder and check out the tag you want to build:

.. code-block:: none

    $ cd php-sdk\phpdev\vs16\x64
    $ mkdir modules
    $ git clone https://github.com/gkralik/php7-sapnwrfc.git modules\sapnwrfc
    $ cd modules\sapnwrfc
    $ git checkout 2.0.0-beta2


Download the PHP 8 source code from the `PHP for Windows download page <https://windows.php.net/download/>`_
and extract it into ``php-sdk\phpdev\vs16\x64``.
The source code should be in the ``php-8.0.13-src`` or similar folder.

Alternatively, you can clone the `php-src <https://github.com/php/php-src>`_ repository and check out the desired tag.

Now change to the PHP sources folder, install the PHP build dependencies:

.. code-block:: none

    $ cd php-sdk\phpdev\vs16\x64\php-8.0.13-src
    $ phpsdk_deps -u

Create the configure script and add the ``modules`` directory to the module search path:

.. code-block:: none

    $ buildconf --add-modules-dir=..\modules
    $ configure --help

The output of the ``configure --help`` command should now include a line *--with-sapnwrfc*.

Finally, extract the *SAP NW RFC SDK* to ``C:\nwrfcsdk_750`` (or any other path)
and set the *PATH* for the current console session:

.. code-block:: none

    set PATH=%PATH%;C:\nwrfcsdk_750\lib


Build the extension
^^^^^^^^^^^^^^^^^^^

From the PHP source folder, execute ``configure``, then ``nmake`` to build the extension:

.. code-block:: none

    $ configure --disable-all --enable-cli --enable-test-ini --with-sapnwrfc=shared,C:\nwrfcsdk_750
    $ nmake

To build a non-threadsafe version, add ``--disable-zts`` to the ``configure`` command.

The extension DLL can be found in the ``x64\Release_TS`` (or ``x64\Release`` for NTS builds)
folder and is named ``php_sapnwrfc.dll``.

To see if PHP can load the extension, execute the following command:

.. code-block:: none

    $ x64\Release_TS\php.exe -c x64\Release_TS\tmp-php.ini -m

To execute tests, execute ``nmake test``, passing in the tests folder of the extension.
Executing the tests requires access to a SAP system and a configuration file:

.. code-block:: none

  $ nmake test TESTS=..\modules\sapnwrfc\tests NO_INTERACTION=1 SAPNWRFC_ONLINE=1 SAPNWRFC_CUSTOM=1
