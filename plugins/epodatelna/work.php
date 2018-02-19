<?php

$fp = fopen('/tmp/55277fd327078', "r");
$cert = fread($fp, 8192);
fclose($fp);

echo "Read<br>";
echo openssl_x509_read($cert);
echo "<br>";
echo "*********************";
echo "<br>";
echo "Parse<br>";
print_r(openssl_x509_parse($cert));