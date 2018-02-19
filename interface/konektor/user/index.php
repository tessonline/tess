<?php
require "tmapy_config.inc";
require(Fileup2("html_header.inc"));
?>
<title>SOAP KONEKTOR</title>
</head>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
  <meta http-equiv="content-type" content="text/html; charset=windows-1250">
  <meta name="generator" content="PSPad editor, www.pspad.com">
  <title></title>
  </head>
  <body>

  <h3>Uivatelská stránka pro SOAP konektor programu Elektronická evidence dokumentů</h3> 
  <p>SOAP sluba běí na adrese
  <pre><?php echo ($_SERVER["HTTPS"]?'http://':'http://').$_SERVER["HTTP_HOST"].'/ost/posta/interface/konektor/server/soap.php';?></pre>
    </p>
  <p>WSDL soubor
  <pre><?php echo ($_SERVER["HTTPS"]?'http://':'http://').$_SERVER["HTTP_HOST"].'/ost/posta/interface/konektor/server/soap.php?wsdl';?></pre>
    </p>
  <br/>
  <table>
  <tr>
  <td valign="top">

  <h3>Číselníky:</h3>
  <b>Odbory:</b><br/>
  <a href="../cisleniky/odbor.php" target="ifrm">
  ../ciselniky/odbor.php</a><br/><br/>

  <b>Zpracovatelé:</b><br/>
  <a href="../cisleniky/zpracovatel.php" target="ifrm">
  ../ciselniky/zpracovatel.php</a><br/><br/>

  <b>Druhy obálek:</b><br/>
  <a href="../cisleniky/obalky.php" target="ifrm">
  ../ciselniky/obalky.php</a><br/><br/>

  <b>Způsoby doručení:</b><br/>
  <a href="../cisleniky/doruceni.php" target="ifrm">
  ../ciselniky/doruceni.php</a><br/><br/>

  <b>Skartační kódy:</b><br/>
  <a href="../cisleniky/skartace.php" target="ifrm">
  ../ciselniky/skartace.php</a><br/><br/>

  <b>Druhy dokumentů:</b><br/>
  <a href="../cisleniky/dokument.php" target="ifrm">
  ../ciselniky/dokument.php</a><br/><br/>

  <hr>
  
  </td>
  <td valign="top" style="padding: 1px;">
  <iframe name="ifrm" width="500px" height="400px"></iframe>
  </td>
  </tr>
  </table>
  </body>
</html>


<?php
require(Fileup2("html_footer.inc"));
?> 
