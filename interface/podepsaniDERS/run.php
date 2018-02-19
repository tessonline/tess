<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header.inc"));
//$SOUBOR_ID=9458;
require_once(FileUp2(".admin/upload_.inc"));
require_once(FileUp2(".admin/status.inc"));

if ($SCHVALENO==2)
{
  //dokument neni schvalen
  //pouze ulozime stanovisko

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

  $q=new DB_POSTA;
  $sql="update posta_schvalovani set schvaleno=".$SCHVALENO.",datum_podpisu='".Date('d.m.Y H:i:s')."',
  LAST_DATE='".Date('Y-m-d')."',LAST_TIME='".Date('H:i:s')."',LAST_USER_ID=".$USER_INFO["ID"]." where 
  schvalujici_id=".$USER_INFO["ID"]." and posta_id=".$GLOBALS[EDIT_ID];
//  echo $sql;
//  Die('STOP');  
  $q->query($sql);
  NastavStatus($GLOBALS[EDIT_ID]);

  echo '<script>window.opener.document.location.reload(); window.close();</script>';
  
}
if (!$SOUBOR_ID)
{
  require_once(Fileup2("html_footer.inc"));
  Die('CHYBA: Nebyl vybrán soubor');
}


echo "
  <script type=\"text/javascript\">
    var vr_pki_url_jnlp = 'https://ders.cz/pkisigner/launch.jnlp';
//    var vr_pki_url_jnlp = '/scripts/launch.jnlp';

  </script>

  <script src=\"scripts/vrpki.js\" charset=\"utf-8\"></script>
  <script type=\"text/javascript\">

   var vr_stript_name = '';

  /* callback funkce START */
    function vrpki_test_connected() {
       document.frm_edit.submit();
    }


  function vrpki_test_connect() {
    console.log('ok, test connect');
      vrpki_connect_ws('test_connect', null, null, {
        connected:  vrpki_test_connected,
        xml_signed: vrpki_test_connected,
        websign_cant_connect: vrpki_cant_connect
      })
    }

    /* Funkce volana pokud se nepodarilo pripojit */
    function vrpki_cant_connect(){
    /* Spustim stazeni JNLP souboru */
      var elem = window.document.createElement('a');
      elem.href = p_websign_url
      document.body.appendChild(elem);
      elem.click();
      document.body.removeChild(elem);

      console.log(\"Nepripojeno, snazim se nastartovat\");
      setTimeout(
        function(){
          console.log(\"-- zkousime, jestli uz muzeme komunikovat s WebSign:\", g_ws.readyState, g_ws_alert_connection_showed);
          if (g_ws.readyState !== 1){
            console.log(\"--- Nejde to, zkusime to znovu za dve vteriny\");
            vrpki_test_connect()
          }
        }, 2000
      );
    }
    /* callback funkce KONEC */



  </script>
";

echo '
<form name="frm_edit" action="podepis.php" method="GET">
<input type="hidden" name="SOUBOR_ID[]" value="'.$_GET['SOUBOR_ID'][0].'">
<input type="hidden" name="VIDITELNY" value="'.$_GET['VIDITELNY'].'">
<input type="hidden" name="POZICE_VIDITELNY" value="'.$_GET['POZICE_VIDITELNY'].'">
<input type="hidden" name="DUVOD_PODEPSANI" value="'.$_GET['DUVOD_PODEPSANI'].'">
<input type="hidden" name="MISTO_PODEPSANI" value="'.$_GET['MISTO_PODEPSANI'].'">
<input type="hidden" name="KONTAKTNI_INFO" value="'.$_GET['KONTAKTNI_INFO'].'">
<input type="hidden" name="EDIT_ID" value="'.$_GET['EDIT_ID'].'">

</form>


';




require_once(Fileup2("html_footer.inc"));  
echo '


</head>

<body onload="vrpki_test_connect()">
  <h1>Podepsání souboru</h1>
  <div id="loading"><p>Nyní spouštím doplněk pro el. podpis. Je možné, že se objeví nutnost spuštění, prosím, potvrďte a spusťte daný doplněk (jnlp).</p> <p>Po spuštění programu klikněte <a href="#" onclick="vrpki_test_connect();">sem pro obnovení spojení.</a>.</p></div>

 ';

?>
</body>
</html>




