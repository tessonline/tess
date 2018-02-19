<?php
$file = 'ermsAPI.wsdl';
$fp = fopen($file, 'r');
$data = fread($fp, filesize($file));
fclose($fp);

$z = array(
  'WEBSERVICE_ENDPOINT',
);

$url = 'http://' . $_SERVER['HTTP_HOST']. '/ost/posta/interface/BP/';
$na = array(
  $url
);

$vysledne = str_replace($z, $na, $data);
$content_type = "application/xml";
header("Content-type: $content_type");
header("Content-Disposition: inline; filename=\"ws.wsdl\"");
header("Content-length: ".(string)(strlen($vysledne))."");
echo $vysledne;
