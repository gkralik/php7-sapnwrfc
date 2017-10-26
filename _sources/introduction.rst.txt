Introduction
============

The ``php7-sapnwrfc`` extension wraps the *SAP NW RFC library* and
uses the provided methods to allow PHP developers to call 
remote-enabled ABAP modules.

If you do not have prior experience with the *SAP NW RFC SDK*, the 
lecture of the following articles is highly recommended:

- `SAP NetWeaver RFC SDK (SAP Help) <https://help.sap.com/saphelp_nw73ehp1/helpdata/en/48/a88c805134307de10000000a42189b/frameset.htm?frameset=/en/48/a994a77e28674be10000000a421937/frameset.htm>`_
- `SAP NetWeaver RFC SDK -- RFC Client Programs <https://wiki.scn.sap.com/wiki/display/ABAPConn/SAP+NetWeaver+RFC+SDK+--+RFC+Client+Programs>`_
- `SAP NetWeaver RFC SDK -- Advanced Topics <https://wiki.scn.sap.com/wiki/display/ABAPConn/SAP+NetWeaver+RFC+SDK+--+Advanced+Topics>`_

.. _quick-start:

Quick start
-----------

The following simple example calls the RFC-enabled ABAP module 
``STFC_CHANGING`` and dumps its return value:

.. code-block:: php

    <?php

    use SAPNWRFC\Connection as SapConnection;
    use SAPNWRFC\Exception as SapException;

    $config = [
        'ashost' => 'my.sap.system.local',
        'sysnr'  => '00',
        'client' => '123',
        'user'   => 'YOUR USERNAME',
        'passwd' => 'YOUR PASSWORD',
        'trace'  => SapConnection::TRACE_LEVEL_OFF,
    ];

    try {
        $c = new SapConnection($config);

        $f = $c->getFunction('STFC_CHANGING');
        $result = $f->invoke([
            'START_VALUE' => 0,
            'COUNTER' => 1,
        ]);

        var_dump($result);
        /*
        * array(2) {
        *   ["COUNTER"]=>
        *   int(2)
        *   ["RESULT"]=>
        *   int(1)
        *   }
        */
    } catch(SapException $ex) {
        echo 'Exception: ' . $ex->getMessage() . PHP_EOL;
    }

Read the :doc:`usage guide </usage>` for a detailed explanation of the
provided interface.

Usage scenarios
---------------

Not all functionality of the *SAP NW RFC SDK* has been implemented
in this exension (yet). Basically, we distinguish between two 
scenarios:

- Client: Calling ABAP modules from PHP code
- Server: Calling PHP code from an ABAP client

Currently, the extension only supports the client scenario, that is
calling ABAP function modules from PHP.

It does not support the server scenario at this moment.

Other functionality might also not be available in this extension. If you
have special needs, feel free to `open an issue <https://github.com/gkralik/php7-sapnwrfc/issues>`_ 
or a `pull request <https://github.com/gkralik/php7-sapnwrfc/pulls>`_ on GitHub.