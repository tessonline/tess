<?php

include('barcode.php');
/*
// For demonstration purposes, get pararameters that are passed in through $_GET or set to the default value
$filepath = (isset($_GET["filepath"])?$_GET["filepath"]:"");
$text = (isset($_GET["text"])?$_GET["text"]:"0");
$size = (isset($_GET["size"])?$_GET["size"]:"20");
$orientation = (isset($_GET["orientation"])?$_GET["orientation"]:"horizontal");
$code_type = (isset($_GET["codetype"])?$_GET["codetype"]:"code128");
$print = (isset($_GET["print"])&&$_GET["print"]=='true'?true:false);
$sizefactor = (isset($_GET["sizefactor"])?$_GET["sizefactor"]:"1");

// This function call can be copied into your project and can be made from anywhere in your code
*/
$text = 'UKRUK123456789';
$file = barcode( '', $text);
		header ('Content-type: image/png');
echo $file;
