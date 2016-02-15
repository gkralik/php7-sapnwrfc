# SAP NW RFC extension for PHP 7

**NOTE: This extension is currently in an alpha version. Help (especially testing) is welcome**

This extension is intended to provide a means for PHP 7 developers to interface with the SAP NetWeaver SDK.

## Building

To build the extension you need to download the *SAP NetWeaver RFC SDK* from the *SAP Service Marketplace* and extract the SDK. You can [follow the instructions](http://sap.github.io/PyRFC/install.html#install-c-connector).

```
$ git clone https://github.com/gkralik/php7-sapnwrfc.git
$ cd php7-sapnwrfc
$ phpize
$ ./configure --with-sapnwrfc=/usr/sap/nwrfcsdk
$ make
$ sudo make install
```

## Installing

Add `extension=sapnwrfc.so` to your `php.ini`.

You can verify that the extension is loaded by running `php -m | grep sapnwrfc`.

## Usage

This simple example shows how to call a (fictional) RFC function and get its return value:

```php
<?php

try {
    $c = new \SAPNWRFC\Connection([
        'ashost' => 'my.sap.system.local',
        'sysnr'  => '00',
        'client' => '123',
        'user' => 'DEMO',
        'passwd' => 'XXXX',
        'trace'  => '0'
    ]);

    $f = $c->getFunction('Z_TEST_FUNCTION');
    $result = $f->invoke([
        'CHAR1' => 'A',
        'TABL' => [
            ['INT4' => 1, 'CHAR4' => 'NOPE'],
        ]
    ]);

    var_dump($result);
} catch(\SAPNWRFC\ConnectionException $e) {
    print "Connection failed: ".$e->getMessage()."\n";
    exit(1);
} catch(\SAPNWRFC\FunctionCallException $e) {
    print "Connection failed: ".$e->getMessage()."\n";
    exit(1);
}
```

See [the API overview](docs/api.md) for details about the provided interface.

## Issues and Pull Requests

As this extension is in early development, some issues are expected. If you find anything, don't hesitate to open an issue or a pull request and help out.

## License

This software is licensed under the MIT license. See [LICENSE](LICENSE) for details.

## Legal notice

SAP and other SAP products and services mentioned herein are trademarks or registered trademarks of SAP SE (or an SAP affiliate company) in Germany and other countries.
