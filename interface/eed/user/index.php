<?php
require "tmapy_config.inc";
require(Fileup2("html_header.inc"));
?>
<title>SOAP KONEKTOR EED</title>
</head>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
  <meta http-equiv="content-type" content="text/html; charset=windows-1250">
  <meta name="generator" content="PSPad editor, www.pspad.com">
  <title></title>
  </head>
  <body>

  <h3>U�ivatelsk� str�nka pro SOAP konektor EED programu Elektronick� evidence dokument�</h3> 
  <p>SOAP slu�ba b�� na adrese
  <pre><?php echo ($_SERVER["HTTPS"]?'http://':'http://').$_SERVER["HTTP_HOST"].'/ost/posta/interface/eed/server/soap.php';?></pre>
    </p>
  <p>WSDL soubor
  <pre><?php echo ($_SERVER["HTTPS"]?'http://':'http://').$_SERVER["HTTP_HOST"].'/ost/posta/interface/eed/server/soap.php?wsdl';?></pre>
    </p>
  <br/>
  <p>SOAP test
  <pre><?php echo ($_SERVER["HTTPS"]?'http://':'http://').$_SERVER["HTTP_HOST"].'/ost/posta/interface/eed/priklad.php';?></pre>
    </p>
  
  </body>
</html>


<?php
require(Fileup2("html_footer.inc"));
?> 
