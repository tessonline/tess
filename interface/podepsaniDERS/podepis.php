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

if (!$GLOBALS['TIMESTAMP']) $GLOBALS['TIMESTAMP']=0;
if (!$GLOBALS['VIDITELNY']) $GLOBALS['VIDITELNY']=0;
$viditelnost = 0;

$ts_url=$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_URL"];
if ($GLOBALS['TIMESTAMP']>0 && strlen($ts_url)<5) 
{
  require_once(Fileup2("html_footer.inc"));
  Die('CHYBA: Není zadána webová služba pro přidělení Časového razítka');
}
$soubory=array();
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS['EDIT_ID']); 

$SOUBOR_ID = $SOUBOR_ID[0];
while (list($key,$val)=each($upload_records))
  if ($val[ID]==$SOUBOR_ID)
{
      $data=$uplobj['table']->GetUploadFiles($val);
//      $base64 = $data;
      $name = $val['FILE_NAME'];
}

if (strlen($data)<1) 
{
  require_once(Fileup2("html_footer.inc"));
  Die('Není k dispozici obsah souboru');
}

$pocet_podpisu = substr_count($data, '(Signature');

if ($pocet_podpisu>5) {
  require_once(Fileup2("html_footer.inc"));
  $button = '<input type="button" onclick="parent.$.fancybox.close();" value="   Zavřít   " class="btn">';
  Die('<p>CHYBA: V daném souboru je již 6 podpisů, další již nelze přidat.</p><p>' . $button .' </p>');
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
      vrpki_test_xml_1();
    }

   function vrpki_test_xml_1_signed(p_data) {
      
      console.log('podepsano, jdeme ulozit');
      var data = p_data;
      if (data.data == 'SIGNED') return false;

      var reader = new FileReader();
      reader.onload = function(event) {
        var fd = new FormData();

        fd.append('file_data', btoa(event.target.result) || \"NEMAM RESULT\");
        fd.append('fname', 'vr_pki_update_fileman');

        fd.append('dokument_id', document.frm_edit.dokument_id.value);
        fd.append('file_id', document.frm_edit.file_id.value);
        fd.append('SCHVALUJICI_ID', document.frm_edit.SCHVALUJICI_ID.value);
        fd.append('POZNAMKA', document.frm_edit.POZNAMKA.value);
        fd.append('SCHVALENO', document.frm_edit.SCHVALENO.value);

        $('#loading').css( \"display\", \"none\" );
        $('#loaded').css( \"display\", \"none\" );
        $('#saved').css( \"display\", \"block\" );

        $.ajax({
          url: 'save.php',
          type: 'POST',
          processData: false,
          contentType: false,
          data: fd
        }).fail(function(e) {
          console.error('Chyba pri uploadu souboru ', e)
          alert($.i18n.message('core.pki.error.upload'))
        }).success(function(e) {
          console.log('Upload souboru se zdaril');

          $('#saved').html(e);
          window.opener.document.location.reload();
      });
    };
    reader.readAsDataURL(data.data);
//    reader.readAsBinaryString (data.data);

    return false;

    }

    function vrpki_test_xml1_sent(){
      $('#loading').css( \"display\", \"none\" );
      $('#loaded').css( \"display\", \"block\" );

    }

    function vrpki_test_xml_1() {
      console.log('Jdeme nahravat data');
      //var binaryData = [];
      //binaryData.push(document.getElementById('pdf_data').value); // v #pdfdata mame base64 pdf souboru
      //var byteCharacters = b64toBlob(binaryData); // zavolame novou funkci
      //var byteCharacters = b64toBlob(binaryData); // zavolame novou funkci


";
if ($GLOBALS['VIDITELNY']>0)  {
  $viditelnost=2;
  $poz = $GLOBALS['POZICE_VIDITELNY'];
  $x = $GLOBALS['CONFIG']['VIDITELNY_PODPIS'][$poz]['X'];
  $y = $GLOBALS['CONFIG']['VIDITELNY_PODPIS'][$poz]['Y'];

  $puvx=$x;
  $puvy = $y;

  $radku = floor($pocet_podpisu / 3) ; //delime 3.1 - aby pripadne hodnota 3 dala 0 - tedy prvni radek

  $sloupec = $pocet_podpisu - ($radku * 3);

  $radku = $radku +1;
  $sloupec = $sloupec + 1;
  $x = $x + (($sloupec-1) * 190);
  $y = $y + (($radku-1) * 35);
//  echo "alert('puvodne $puvx x $puvy - radek $radku, sloupec $sloupec - x je $x a y je $y');";
//        var l_layout = {x: ".$x.", y: ".$y.", p: 0};

  echo "
        var l_layout = {x: ".$x.", y: ".$y.", p: 0};
  ";
}
else echo "
      var l_layout = null; // pokud zaskrtnu, tak nedelam viditelny podpis do PDF
";


echo "


    var request = new XMLHttpRequest();
    request.open('GET', 'https://".$_SERVER['HTTP_HOST']."/ost/posta/getfile.php?FILE_ID=".$SOUBOR_ID."&POSTA_ID=".$GLOBALS['EDIT_ID']."&cacheid=123', true);
    request.responseType = 'blob';
    request.onload = function() {
        var reader = new FileReader();
        reader.readAsDataURL(request.response);
        reader.onload =  function(e){
          vrpki_podepsat(
            {id:'url', data: request.response, akce: 'stahnout', typ: 'PDF', layout: l_layout, nazev: ''},
            g_websocket_url,
            {connected: function(){console.log(111111);},success: vrpki_test_xml_1_signed, sent: vrpki_test_xml1_sent},
            {index: 0, size: 0}
          );
        };
    };
    request.send();


    }


  function vrpki_test_connect() {
    console.log('podepis.php - jdeme na test connect');
      vrpki_connect_ws('test_connect', null, null, {
        connected:  vrpki_test_connected,
        xml_signed: vrpki_test_xml_1,
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
<form name="frm_edit" action="save.php" method="POST">
<input type="hidden" name="dokument_id" value="'.$GLOBALS[EDIT_ID].'">
<input type="hidden" name="file_data" id="file_data">
<input type="hidden" name="file_id" value="'.$SOUBOR_ID.'">
<input type="hidden" name="SCHVALUJICI_ID" value="'.$SCHVALUJICI_ID.'">
<input type="hidden" name="POZNAMKA" value="'.$POZNAMKA.'">
<input type="hidden" name="SCHVALENO" value="'.$SCHVALENO.'">
</form>





';





echo '


</head>

<body onload="vrpki_test_connect()">

  <h1>Podepsání souboru</h1>
  <div id="loading"><p>Připravuji soubor pro podpis...</p></div>
  <div id="loaded" style="display:none"><center>Nyní v programu WebSign vyberte Váš certifikát a klikněte na tlačítko Podepsat.</p><p><img src="img/websignPodpis.PNG" /></p></center></div>
  <div id="saved" style="display:none">Ukládám, čekejte prosím... </div>

';

//     <textarea name="pdf_data" rows="1" cols="1" id="pdf_data" style="visibility:hidden">' . $base64 . '</textarea>

//require_once(Fileup2("html_footer.inc"));
//     <script>vrpki_test_connect();</script>

?>

</body>
</html>
