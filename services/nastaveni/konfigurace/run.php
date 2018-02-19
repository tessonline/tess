<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

require_once(Fileup2("html_header_title.inc"));

$q = new DB_POSTA;

if (HasRole('spravce')) {
  $prac = getSelectDataEed(new of_select_superodbor(array()));
  foreach($prac as $key => $val) {

    if (array_key_exists($key, $GLOBALS['PRACOVISTE'])) {
      if (!EedTools::JeNastaveniKonfigurace($key, $GLOBALS['PARAMETR'])) {
        //ma byt konfigurace, ale neni zalozena, tak ji pridame
        $sql = "insert into posta_konfigurace (KATEGORIE, TYP, PARAMETR, HODNOTA, POPIS, SUPERODBOR)
         VALUES ('".$GLOBALS['KATEGORIE']."','".$GLOBALS['TYP']."','".$GLOBALS['PARAMETR']."',
         '".$GLOBALS['HODNOTA']."','".$GLOBALS['POPIS']."',$key)";
  //       echo $sql.'<br/>';
         $q->query($sql);
      }
    }
    else {
      if ($id_konf = EedTools::JeNastaveniKonfigurace($key, $GLOBALS['PARAMETR'])) {
        //ma byt konfigurace, ale neni zalozena, tak ji pridame
        $sql = "delete from posta_konfigurace where id=" . $id_konf;
  //       echo $sql.'<br/>';
         $q->query($sql);
      }
    }

  }

}


$lastid = Run_(array("showaccess"=>true,"outputtype"=>1,'to_history'=>true));

$tran = LoadClass('EedTransakce');
$tran->ZapisZHistorieTable($lastid, 0, 'posta_konfigurace', ' v Nastavení EED');
require_once(Fileup2("html_footer.inc"));  

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';

?>

