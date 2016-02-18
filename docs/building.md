# Building

## Linux/Unix

```
$ git clone https://github.com/gkralik/php7-sapnwrfc.git
$ cd php7-sapnwrfc
$ phpize
$ ./configure --with-sapnwrfc=/usr/sap/nwrfcsdk
$ make
$ sudo make install
```

If you installed the *SAP NetWeaver RFC SDK* in some other place, replace the path in the `configure` step above.

## Windows

We try to provide pre-built extensions for Windows users (see the [release page](https://github.com/gkralik/php7-sapnwrfc/releases)).
If you don't find your desired version there or still want to build yourself, follow the instructions below.

### Set up a buid environment

Make sure you have a valid build enviroment as [described here](https://wiki.php.net/internals/windows/stepbystepbuild).

After you have set up the enviroment, try to build PHP itself:

```
$ configure --disable-all --enable-cli
$ nmake
$ nmake snap
```

If that works, you can go on. If not, double check your build environment.

### Build the extension

Make sure that you dont mix up x86/x64 (PHP and SAP NW RFC SDK platforms must match).

*NOTE 1: This guide assumes you want to build the x64 version.*

*NOTE 2: We also assume you followed [the SAP NW RFC SDK installation guide](installing_nwrfcsdk.md) and therefor have the SDK files in `C:\nwrfcsdk`*

Copy all header files (`*.h`) from `C:\nwrfcsdk\include` to `C:\php-sdk\phpdev\vc14\x64\deps\include`.
Copy all library files (`*.lib`) from `C:\nwrfcsdk\lib` to `C:\php-sdk\phpdev\vc14\x64\deps\lib`.

Download the latest release of this extension and extract it to `C:\php-sdk\phpdev\vc14\x64\php-7.0-src\ext\sapnwrfc`.

Open the `Developer Command Prompt for VS2015` and execute the commands for [steps 1-4 as described here](https://wiki.php.net/internals/windows/stepbystepbuild#compile) .

The `configure` command (step 6) must be replaced with one of the following commands (depending on which version you want to build):

```
// for NTS (shared module)
configure --disable-all --enable-cli --disable-zts --with-sapnwrfc=shared
// for NTS (compile in)
configure --disable-all --enable-cli --disable-zts --with-sapnwrfc

// for TS (shared module)
configure --disable-all --enable-cli --with-sapnwrfc=shared
// for TS (compile in)
configure --disable-all --enable-cli --with-sapnwrfc
```

Then continue with steps 7-9 and grab a cup of coffee :)

If you built a `shared` extension, the extension files should be available in one of the following locations:
* `C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release\php-7.0\ext` for the NTS version
* `C:\php-sdk\phpdev\vc14\x64\php-7.0-src\x64\Release_TS\php-7.0\ext` for the TS version
