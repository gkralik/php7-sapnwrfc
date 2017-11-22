<?php

const HEADER_FILE = 'php_sapnwrfc.h';
const DOCS_CONF_FILE = 'docs/conf.py';

// make paths relative to project root
chdir(dirname(__DIR__));

if ($argc != 2) {
    print "usage: {$argv[0]} <X.Y.Z>\n";
    exit(1);
}

$newVersion = trim($argv[1]);

// quick sanity check
if (preg_match('/\d+\.\d+\.\d+/', $newVersion) === 0) {
    print "'" . $newVersion . "' does not look like a valid version\n";
    exit(1);
}

// update version in php_sapnwrfc.h
print "updating " . HEADER_FILE . "\n";
$versionDefine = sprintf('#define PHP_SAPNWRFC_VERSION "%s"', $newVersion);

$headerContents = file_get_contents(HEADER_FILE);
$headerContents = preg_replace('/^#define PHP_SAPNWRFC_VERSION.*$/m', $versionDefine, $headerContents);
file_put_contents(HEADER_FILE, $headerContents);

// update version in docs/conf.py
print "updating " . DOCS_CONF_FILE . "\n";
$docsVersionReplacement = sprintf("\\1 = '%s'", $newVersion);

$docsConfigContents = file_get_contents(DOCS_CONF_FILE);
$docsConfigContents = preg_replace("/^(version|release)\s*=.*$/m", $docsVersionReplacement, $docsConfigContents);
file_put_contents(DOCS_CONF_FILE, $docsConfigContents);
