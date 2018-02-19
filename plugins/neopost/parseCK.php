<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/oth_funkce.inc"));
require(FileUp2("html_header_full.inc"));


$data = $_GET['data'];

$vaha = substr($data, 13, 5);
$cena = substr($data, 24, 5) / 100;
$kod = substr($data, 37, 3);
$kod = str_replace(' ','', $kod);

$vaha = (int) $vaha;
$cena = (float) $cena;

//echo "vaha $vaha cena $cena kod $kod ";

  $error = false;

switch ($kod) {
  case 'OLZ': $kod = 0; break;
  case 'R': $kod = 2; break;
  case 'R ': $kod = 2; break;
  case 'DB': $kod = 7; break;
  case 'CP': $kod = 11; break;
  case 'CB': $kod = 6; break;

  case 'O': $kod = 5; break;
  case 'ZO': $kod = 0; break;
  case 'ZR': $kod = 2; break;
  case 'ZCP': $kod = 11; break;
  case 'RD': $kod = 2; break;
  case 'DBD': $kod = 7; break;
  case 'CPD': $kod = 11; break;
  case 'CBD': $kod = 6; break;
  case 'RV': $kod = 2; break;
  case 'RBV': $kod = 7; break;
  case 'CPV': $kod = 11; break;
  case 'CBV': $kod = 6; break;
  case 'RDV': $kod = 2; break;
  case 'DBV': $kod = 7; break;
  case 'CPV': $kod = 11; break;
  case 'CBV': $kod = 6; break;
  case 'RVN': $kod = 2; break;
  case 'CP1': $kod = 11; break;
  case 'VP2': $kod = 11; break;
  default:
    $puv_kod = $kod;
    $kod=-1;
}


$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
$LAST_DATE=Date('d.m.Y');

echo '<script type="text/javascript">
  window.parent.document.getElementById(\'hledam\').style = \'visibility:hidden\';
  window.parent.document.getElementById(\'span_text_CK\').innerHTML = \'\';
  window.parent.document.getElementById(\'carKod\').disabled = false;
  window.parent.document.getElementById(\'carKod\').value = \'\';
  window.parent.document.getElementById(\'DOC_ID\').value = \'0\';
</script>
';

$id = (int) $id;
$id = $id ? $id : 0;
$sql = 'select * from posta where id = ' . $id;
$q = new DB_POSTA;
$q->query($sql);
$pocet = $q->Num_Rows();

if ($pocet == 1) {
  $sql="select max(xertec_id) as max_id from posta";
	$q->query($sql);
	$q->Next_Record();

	$a=$q->Record["MAX_ID"];
	$a++;

  $sql="update posta set hmotnost=".$vaha.",cena=".$cena.",druh_zasilky=".$kod.",xertec_id=".$a.",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$id_user where id=".$id;
  if ($q->query($sql)) $res = "Obálka - Váha:".$vaha."g, Cena: ".$cena." ";
  else $res = "Chyba při uložení do databáze";

  $text = 'provedeno frankování - ' . $res;
  EedTransakce::ZapisLog($id, $text, 'DOC', $id_user);

  echo $sql;
}
else {
  $error = true;
  $res = '<font color=red><b>Chyba pri predani ID!</b></font>';
}

if ($kod == -1) {
  $res = '<font color=red><b>Nenalezen kod pro sluzbu '.$puv_kod.'!</b></font>';
  $error = true;
}

if ($error)
  echo '<script type="text/javascript">
    window.parent.document.getElementById(\'hledam\').style = \'visibility:hidden\';
    window.parent.document.getElementById(\'span_text_CK2\').innerHTML = \''.$res.'\';
    window.parent.document.getElementById(\'span_text_CK\').innerHTML = \'\';
    window.parent.document.getElementById(\'carKod\').disabled = false;
    window.parent.document.getElementById(\'carKod\').value = \'\';
    window.parent.document.getElementById(\'DOC_ID\').value = \'0\';
    window.parent.document.getElementById(\'carKod2\').disabled = true;
    window.parent.document.getElementById(\'carKod\').focus();
  </script>
  ';
else
  echo '<script type="text/javascript">
    window.parent.document.getElementById(\'hledam\').style = \'visibility:hidden\';
    window.parent.document.getElementById(\'span_text_CK2\').innerHTML = \''.$res.'\';
  window.parent.document.getElementById(\'span_text_CK\').innerHTML = \'\';
  window.parent.document.getElementById(\'carKod\').disabled = false;
    window.parent.document.getElementById(\'carKod2\').disabled = true;
    window.parent.document.getElementById(\'carKod\').focus();
  </script>
  ';



/*
    $this->options[] = array("value"=>"1", "label"=>"Obyčejně");
    $this->options[] = array("value"=>"0", "label"=>"Psaní");
    $this->options[] = array("value"=>"11", "label"=>"Cenné psaní");
    $this->options[] = array("value"=>"2", "label"=>"Doporučené psaní");
    $this->options[] = array("value"=>"3", "label"=>"Psaní standard / za 6.40 /");
    $this->options[] = array("value"=>"4", "label"=>"Psaní obchodní");
    $this->options[] = array("value"=>"5", "label"=>"balíky");
    $this->options[] = array("value"=>"7", "label"=>"doporučené balíky");
    $this->options[] = array("value"=>"8", "label"=>"poukázka");
    $this->options[] = array("value"=>"9", "label"=>"EMS");
    $this->options[] = array("value"=>"10", "label"=>"jiný druh - po±tovné nastaveno uµivatelem /DSET na stroji /");
*/


/**
 *

kod zeme - 2 znaky
DPM verze - 2 znaky
licence - 9 znaky
vaha - 5 znaky
datum podani - 6 znaky
hodnota vyplatneho - 5 znaky
kumulativni registr zasilek - 8 znaky
kod sluzby - 3 znaky
suma postovneho (celkovy soucet) - 12 znaky
padding - 4 znaky
podpisovy klic - 4 znaky

*/
//CZ 01 L87002101 00018 040215 046.60 00000005 RDV 000000004660 0000 F15C
//CZ 01 L87002101 00011 040215 046.60 00000006 RDV 000000009320 0000 55A7
//CZ 01 L87002101 00010 040215 009.50 00000007 OLZ 000000010270 0000 FC1F

/*
priklady od p. Sandery
2075/2015
CZ01L87002101000180402150466000000005RDV0000000046600000F15C
2131/2015
CZ01L87002101000110402150466000000006RDV000000009320000055A7
2150/2015
CZ01L87002101000100402150095000000007OLZ0000000102700000FC1F
*/

require(FileUp2("html_footer.inc"));




