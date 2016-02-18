
# Building

## Unix

```
$ git clone https://github.com/gkralik/php7-sapnwrfc.git
$ cd php7-sapnwrfc
$ phpize
$ ./configure --with-sapnwrfc=/usr/sap/nwrfcsdk
$ make
$ sudo make install
```

## Windows

There should be prebuild downloads available on the [release page here](https://github.com/gkralik/php7-sapnwrfc/releases)

If you still want to build the extension yourself, follow these steps

### Build enviroment

Double check that you have a valid build enviroment, like [described here](https://wiki.php.net/internals/windows/stepbystepbuild)
After you have setup that enviroment, test to build PHP itself with

```
configure --disable-all --enable-cli
nmake
nmake snap
```
  
***If that works, you can continue :-)***

### Build the extension

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
