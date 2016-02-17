
# SAP NW RFC extension for PHP 7

This extension is intended to provide a means for PHP 7 developers to interface with the SAP NetWeaver SDK.

## Install SAP NetWeaver RFC SDK (required always!)

To ***build or install*** you need always the *SAP NetWeaver RFC SDK* from the *SAP Service Marketplace* first!
You can [follow the instructions here](docs/installing_nwrfcsdk.md).


## Building

### Unix

```
$ git clone https://github.com/gkralik/php7-sapnwrfc.git
$ cd php7-sapnwrfc
$ phpize
$ ./configure --with-sapnwrfc=/usr/sap/nwrfcsdk
$ make
$ sudo make install
```

### Windows

There should be prebuild downloads available on the [release page here](https://github.com/gkralik/php7-sapnwrfc/releases)

If you still want to build the extension yourself, follow these steps

#### Build enviroment

Double check that you have a valid build enviroment, like [described here](https://wiki.php.net/internals/windows/stepbystepbuild)
After you have setup that enviroment, test to build PHP itself with

```
configure --disable-all --enable-cli
nmake
nmake snap
```
  
***If that works, you can continue :-)***

#### Build the extension

Make sure that you dont mix x86/x64 between PHP and SAP NW RFC SDK. In this example we build x64 version!

Go to your extraced x64 SAP NW RFC SDK folder and copy the files to
`C:\php-sdk\phpdev\vc14\x64\deps\include` (*.h files from the include folder)
`C:\php-sdk\phpdev\vc14\x64\deps\lib` (*.lib files from lib folder)

Download the latest release of this extension, and extract it to `C:\php-sdk\phpdev\vc14\x64\php-7.0-src\ext\sapnwrfc`

Open `VS2015 x64 Native Tools Command Prompt` and execute everything [described here](https://wiki.php.net/internals/windows/stepbystepbuild) until the `configure ...` part

The configure command is now
```
// for NTS
configure --disable-all --enable-cli --disable-zts --with-sapnwrfc=shared
// for NTS (extension build in the php you compile)
configure --disable-all --enable-cli --disable-zts --with-sapnwrfc

// for TS
configure --disable-all --enable-cli --with-sapnwrfc=shared
// for TS (extension build in the php you compile)
configure --disable-all --enable-cli --with-sapnwrfc
```

If you used `shared` your extension should be available here
`C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release\php-7.0\ext`
`C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release_TS\php-7.0\ext`


## Installing

Add `extension=sapnwrfc.so` to your `php.ini` (for windows `extension=php_sapnwrfc.dll`) 

You can verify that the extension is loaded by running `php -m | grep sapnwrfc`.

## Usage

This simple example shows how to call a (fictional) RFC function and get its return value:

```php
use SAPNWRFC\Connection as SapConnection;
use SAPNWRFC\Exception as SapException;

$config = [
    'ashost' => 'my.sap.system.local',
    'sysnr'  => '00',
    'client' => '123',
    'user' => 'DEMO',
    'passwd' => 'XXXX',
    'trace'  => SapConnection::TRACE_LEVEL_OFF,
];

try {
    $c = new SapConnection($config);

    $f = $c->getFunction('Z_TEST_FUNCTION');
    $result = $f->invoke([
        'CHAR1' => 'A',
        'TABL' => [
            ['INT4' => 1, 'CHAR4' => 'NOPE'],
        ]
    ]);

    var_dump($result);
} catch(SapException $ex) {
    echo 'Exception: ' . $ex->getMessage() . PHP_EOL;
    
    /*
     * You could also catch \SAPNWRFC\ConnectionException and \SAPNWRFC\FunctionCallException
     * separately if you want to.
     */
}
```

See [documentation](docs/readme.md) for details.

## Contributing

Contribution to the project (be it by reporting/fixing bugs, writing documentaton, helping with testing) is very welcome.
Just open up an issue or a PR.

## License

This software is licensed under the MIT license. See [LICENSE](LICENSE) for details.

## Legal notice

SAP and other SAP products and services mentioned herein are trademarks or registered trademarks of SAP SE (or an SAP affiliate company) in Germany and other countries.
