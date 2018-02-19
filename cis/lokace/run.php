<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

require_once(FileUp2(".admin/form_func.inc"));
require_once(FileUp2(".config/config.inc"));

$i=1;
foreach ($GLOBALS['RESOURCE_STRING']['lokace_uroven'] as $singleUroven) {
  if ($singleUroven[1] == $GLOBALS['NAZEV_TEXT']) $urovenSpisovny = $i;
  $i++;
}
//pouze 1. a 2. uroven ma jit blokovat pridavani lokace, neni defaultne zaskrtnuto pridat lokaci, 

if ($urovenSpisovny > 2) {
  $GLOBALS['NAZEV_CISLO'] = (int)$GLOBALS['NAZEV_CISLO'];
  if ($GLOBALS['NAZEV_CISLO'] <= 0) {
    echo 'Do pole '.$GLOBALS['RESOURCE_STRING']['lokace_uroven'][$urovenSpisovny][1].' lze uložit pouze přirozenou číselnou hodnotu!<br /><br />';
    echo '<button class="btn" onclick="parent.$.fancybox.close()">Zavřít okno</a>';
    require_once(Fileup2("html_footer.inc"));
    die();
  }
}
$q = new DB_POSTA;
if (empty($GLOBALS['DALSI_LOKACE'])) $GLOBALS['DALSI_LOKACE'] = 0;
$GLOBALS['NAZEV'] = $GLOBALS['NAZEV_TEXT'].' '.$GLOBALS['NAZEV_CISLO'];

if (!$GLOBALS['DELETE_ID']) {
  $sql = "SELECT * FROM posta_spisovna_cis_lokace WHERE nazev='".$GLOBALS['NAZEV']."'"
       . ($GLOBALS['ID_PARENT']   ? " AND id_parent='".$GLOBALS['ID_PARENT']."'"     : '')
       . ($GLOBALS['SPISOVNA_ID'] ? " AND spisovna_id='".$GLOBALS['SPISOVNA_ID']."'" : '');
  $q->query($sql);
  if ($q->next_record() && $q->Record['ID'] != $GLOBALS['EDIT_ID']) {
    echo $GLOBALS['RESOURCE_STRING']['lokace_uroven'][$urovenSpisovny][1].' s tímto názvem již existuje. Zvolte, prosím, jiný název.<br /><br />';
    echo '<button class="btn" onclick="parent.$.fancybox.close()">Zavřít okno</a>';
    require_once(Fileup2("html_footer.inc"));
    die();
  }
}

$where = '';
if ($GLOBALS['EDIT_ID']) {
  $sql = 'SELECT * FROM posta_spisovna_cis_lokace WHERE id='.$GLOBALS['EDIT_ID'];
  $q->query($sql);
  $q->next_record();
  $staryNazev = $q->Record['NAZEV'];
  if ($GLOBALS['ID_PARENT'] > 0) {
    $where = "id_parent='".$GLOBALS['ID_PARENT']."'";
  }
  else {
    $where = "id_parent IS NULL AND spisovna_id='".$GLOBALS['SPISOVNA_ID']."'";
  }
  $sql = "UPDATE posta_spisovna_cis_lokace SET dalsi_lokace='".$GLOBALS['DALSI_LOKACE']."' WHERE ".$where;
  $q->query($sql);
  updateAllChildren($q, $staryNazev, $GLOBALS['NAZEV'], $GLOBALS['EDIT_ID']);
}
$delimiter = "/";
$GLOBALS["PLNA_CESTA"] = makeFullWay($GLOBALS["NAZEV"], $GLOBALS["ID_PARENT"], $delimiter);
//die($GLOBALS["ID_PARENT"]." ".$GLOBALS["NAZEV"]." ".$GLOBALS["PLNA_CESTA"]);
//$GLOBALS["ID_PARENT"] = getParentFromFullWay($GLOBALS["PLNA_CESTA"], $delimiter);
Run_(array("showaccess"=>true,"outputtype"=>3));

require_once(Fileup2("html_footer.inc"));