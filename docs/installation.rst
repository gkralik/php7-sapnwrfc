Installation
============

The installation of the ``php7-sapnwrfc`` extension consists of three steps.

- Installing the *SAP NW RFC library*
- Compiling the PHP extension
- Enabling the extension in your PHP configuration

.. _installing-nwrfcsdk:

Installing the SAP NW RFC library
---------------------------------

You can find detailed instructions on how to compile, install and use 
the *SAP NW RFC library* on https://support.sap.com/en/product/connectors/nwrfcsdk.html.

The SAP NW RFC SDK is fully backwards compatible, supporting all NetWeaver systems, 
from today's S4 down to R/3 release 4.6C. Using the latest version is recommended.

.. note::
   .. versionchanged:: 1.4.0
      This extension only supports building for SAP NW RFC SDK 7.50.

Download the SAP NW RFC library
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To download the *SAP NW RFC library*, go to the `Software Center on the 
SAP ONE Support Launchpad <https://launchpad.support.sap.com/#/softwarecenter>`_.

Enter ``SAP NW RFC SDK 7.50`` in the search box. Then download the library version 
that suits your platform.

.. image:: /images/search_nwrfcsdk.png
   :alt: Search for SAP NW RFC SDK 7.50

If you don't already have it, you also need the *SAPCAR* utility to extract the 
library. You can also download it from the SAP Support Portal. Search for
``SAPCAR``.

.. image:: /images/search_sapcar.png
   :alt: Search for SAPCAR

Extract the library to a directory on your machine. This guide uses 
``/usr/sap/nwrfcsdk`` (on Linux) or ``C:\nwrfcsdk`` (on Windows) as the 
default path. You are free to choose another directory. If you do so, 
make sure to substitute the correct path in the instructions below.

Configuring the library path
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You have to configure your system to include the ``lib`` directory of your 
*SAP NW RFC library* installation in the library search path.

Linux
"""""

Create the file ``/etc/ld.so.conf.d/nwrfcsdk.conf`` with following contents:

::

    /usr/sap/nwrfcsdk/lib

Then run ``ldconfig``.

Windows
"""""""

On a command prompt, execute ``set PATH=%PATH%;C:\nwrfcsdk\lib``. This is temporary
the change will be lost as soon as you close the command prompt.

.. note:: 

   The steps might differ depending on your version of Windows.

To permanently add the library to the PATH environment variable, follow these steps:
    
    1. Open the Start menu and type ``environment``
    2. Select ``Edit the system environment variables`` or ``Edit environment variables for your account``,
       depending on whether you want to set the path for the user or the whole system.
    3. Select the ``PATH`` environment variable, click ``Edit`` and add the path ``C:\nwrfcsdk\lib``.

Compiling the PHP extension
---------------------------

Follow the steps in :ref:`building-from-source` to build the extension.

Enabling the extension
----------------------

To enable the extension, add one of the following lines to your ``php.ini``:

::

    # for Linux/Unix
    extension=sapnwrfc.so

    # for Windows
    extension=php_sapnwrfc.dll

You can verify that the extension is loaded by inspecting the output
of ``php -m``. It should contain a line ``sapnwrfc``.