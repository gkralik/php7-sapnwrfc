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

Set up a build environment
^^^^^^^^^^^^^^^^^^^^^^^^^^

Make sure you have a valid `build enviroment as described here <https://wiki.php.net/internals/windows/stepbystepbuild>`_.

After you have set up the enviroment, try to build PHP itself:

.. code-block:: shell

    $ configure --disable-all --enable-cli
    $ nmake
    $ nmake snap

If that works, you can go on. If not, double check your build environment.

Build the extension
^^^^^^^^^^^^^^^^^^^

Make sure that you dont mix up x86/x64 (PHP and *SAP NW RFC library* platforms must match).

.. note::
   1. This guide assumes you want to build the x64 version.
   2. We also assume the SDK files are in C:\nwrfcsdk

Copy all header files (``*.h``) from ``C:\nwrfcsdk\include`` to ``C:\php-sdk\phpdev\vc14\x64\deps\include``. 
Copy all library files (``*.lib``) from ``C:\nwrfcsdk\lib`` to ``C:\php-sdk\phpdev\vc14\x64\deps\lib.``

Download the latest release of this extension and extract it to ``C:\php-sdk\phpdev\vc14\x64\php-7.0-src\ext\sapnwrfc``.

Open the *Developer Command Prompt for VS2015* and execute the commands for 
steps 1-4 as described in the `PHP Windows step by step build page <https://wiki.php.net/internals/windows/stepbystepbuild>`_.

The configure command (step 6) must be replaced with one of the following commands 
(depending on which version you want to build):

.. code-block: none

    // for NTS (shared module)
    configure --disable-all --enable-cli --disable-zts --with-sapnwrfc=shared
    // for NTS (compile in)
    configure --disable-all --enable-cli --disable-zts --with-sapnwrfc

    // for TS (shared module)
    configure --disable-all --enable-cli --with-sapnwrfc=shared
    // for TS (compile in)
    configure --disable-all --enable-cli --with-sapnwrfc

Then continue with steps 7-9.

If you built a shared extension, the extension files should be available in one of the following locations:

.. code-block:: none

    C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release\php-7.0\ext for the NTS version
    C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release_TS\php-7.0\ext for the TS version