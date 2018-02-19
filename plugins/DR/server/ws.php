<?php
$file = 'DR.wsdl';
$fp = fopen('DR.wsdl', 'r');
$data = fread($fp, filesize($file));
fclose($fp);

$z = array(
  'WEBSERVICE_ENDPOINT',
);

$url = 'http://' . $_SERVER['HTTP_HOST']. '/ost/posta/plugins/DR/server/';
$na = array(
  $url
);

$vysledne = str_replace($z, $na, $data);
$content_type = "application/xml";

Header("Pragma: no-cache");
Header("Cache-Control: no-cache");
Header("Content-Type: text/xml");

// header("Content-type: $content_type");
// header("Content-Disposition: inline; filename=\"ws.wsdl\"");
// header("Content-length: ".(string)(strlen($vysledne))."");
echo $vysledne;
