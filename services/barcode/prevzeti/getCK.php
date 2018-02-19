<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/status.inc"));
require(FileUp2("html_header_full.inc"));

$ids = explode('|',$GLOBALS['id']);

$span = array();

if ($GLOBALS['smer'] == 1) {
  $sloupec_datum = 'DATUM_PREDANI';
  $odeslana_posta = 'f';
}
else {
  $sloupec_datum = 'DATUM_PREDANI_VEN';
  $odeslana_posta = 't';
}

$adresa = '';
$vec = '';
$img = 'error';

//echo $_POST['PREBRAL_ID'];
$prebirajici = $GLOBALS["POSTA_SECURITY"]->GetUserInfo($_POST['PREBRAL_ID'],false,true,1);
//print_r($prebirajici);
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
$aktual=Date('Y-m-d H:i:s');


$q = new DB_POSTA;
if (count($ids)>0) {
  foreach($ids as $id) {
    if (strlen($id)>0) {

      $idCK = PrevedCPnaID($id,'');
      echo "Onma naleyeno id $idCK <br/>";
      if ($idCK>0) {
        $sql = 'select * from posta where id=' . $idCK;
        $q->query($sql);
        $q->Next_Record();
        $vec = $q->Record['VEC'];
//        print_r($q->Record);
        if ($q->Record[$sloupec_datum]<>'') {
          $adresa = UkazAdresu($idCK, ', ');
          $span = '<font color=red><b>CHYBA, už převedeno!</b></font>';
          $img = 'error';
        }
        elseif ($q->Record['ODESLANA_POSTA']<>$odeslana_posta) {
          $adresa = UkazAdresu($idCK, ', ');
          $span[] = '<font color=red><b>CHYBA, neshoduje se směr!</b></font>';
          $img = 'error';
        }
        elseif ($_GET['odbor']>0 && ($q->Record['ODBOR'] <> $_GET['odbor'])) {
          $adresa = UkazAdresu($idCK, ', ');
          $span = '<font color=red><b>CHYBA, neshoduje se spisový uzel, jde o správný dokument?</b></font>';
          $img = 'error';
        }
        else {
          $span = 'ok';
          $idok[] = $idCK;
          $img = 'ok';
          $adresa = UkazAdresu($idCK, ', ');

          $sql="update posta set ".$sloupec_datum."='".$aktual."',last_date='".$LAST_DATE."',last_time='".$LAST_TIME."',last_user_id=".$LAST_USER_ID." where id=".$idCK;
          $q->query($sql);
          $text = 'Dokument (<b>'.$idCK.'</b>) převzal(a) '.$prebirajici['LNAME'].' ' .$prebirajici['FNAME'].' dne '.$aktual;
        //  echo $text;
          EedTransakce::ZapisLog($idCK, $text, 'DOC');
          NastavStatus($idCK, $LAST_USER_ID);
          $span = 'předáno';

        }
      }
      else
        $span = '<font color=red><b>nenalezeno!</b></font>';
    }
    else
      $span = '&nbsp;';

  }

  $res = $span;
  echo $res;

  echo '<script type="text/javascript">

  window.parent.document.getElementById(\'span_ID_CK\').innerHTML = \''.$id.'\';
  window.parent.document.getElementById(\'span_adresat_CK\').innerHTML = \''.$adresa.'\';
  window.parent.document.getElementById(\'span_text_CK\').innerHTML = \''.$res.'\';
  window.parent.document.getElementById(\'span_vec_CK\').innerHTML = \''.$vec.'\';

  window.parent.document.getElementById(\'hledam\').style = \'visibility:hidden\';
  window.parent.document.getElementById(\'image_ok\').style = \'visibility:hidden\';
  window.parent.document.getElementById(\'image_error\').style = \'visibility:hidden\';

   window.opener.$( "#image_ok" ).css( "display", "none" );
   window.opener.$( "#image_error" ).css( "display", "none" );

   window.opener.$( "#image_'.$img.'" ).css( "display", "block" );

   window.parent.document.getElementById(\'carKod\').value = \'\';
   window.parent.document.getElementById(\'carKod\').focus();

  ';
  if (count($idok)>0)
  foreach($idok as $idk)
  echo '
  var f = window.parent.document.getElementById(\''.$idk.'\');
  if (f) f.checked=true;

  ';

  echo'
  //   var elements = window.parent.document.frm_posta.SELECT_IDposta;
  //        for (i=0; i<elements.length; i++){
  //            alert(elements[i].value);
  //         }

  </script>
  ';
}
