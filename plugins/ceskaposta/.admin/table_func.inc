<?php

function UkazTlacitka($id) {
  If ($id==1 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='funkce.php?typ=1&ID=$GLOBALS[ID]&DATUM_OD=$GLOBALS[DATUM_OD]&DATUM_DO=$GLOBALS[DATUM_DO]&ODBOR=$GLOBALS[ODBOR]'>znovu načíst dokumenty</a>";}
  If ($id==1 && $GLOBALS[DATUM_VYTISTENI]&& !$GLOBALS[DATUM_VRACENI]) {$res="<i>zapište datum převzetí Českou poštou...</i>";}

  
//  If ($id==2 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='protokol.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>starší protokol</a>&nbsp;&nbsp;&nbsp;<a href='protokol2010.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>nový protokol</a>";}
//  If ($id==2 && $GLOBALS[DATUM_VYTISTENI]) {$res="<a href='protokol.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>starší protokol</a>&nbsp;&nbsp;&nbsp;<a href='protokol2010.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>nový protokol</a>";}
  If ($id==2 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a title='Generovat poštovní podací arch bez obyčejných zásilek' href='protokol2010.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>generovat PDF</a>";}
  If ($id==2 && $GLOBALS[DATUM_VYTISTENI]) {$res="<a title='Generovat poštovní podací arch bez obyčejných zásilek' href='protokol2010.php?ID=$GLOBALS[ID]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>generovat PDF</a>";}
  If ($id==3 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='funkce.php?typ=2&ID=$GLOBALS[ID]'><img src='".FileUpUrl('images/ok_check.gif')."' BORDER=0 title='Uzavřít (a zamknout) tento protokol'></a>";}
  If ($id==3 && $GLOBALS[DATUM_VYTISTENI]) {$res="Protokol uzavřen dne ".$GLOBALS[DATUM_VYTISTENI];}


  return $res;
}

function PocetDoc($ID = 0) {
  $sql = "select count(*) as pocet from posta_cis_ceskaposta_id where protokol_id in ($ID)";
  if (!$db1) $db1 = new DB_POSTA;
  $db1->query($sql);
  $db1->Next_Record();
  if ($db1->Record['POCET']>0) {
    $res.="<a title='Seznam všech dokumentů, které odpovídají danému zařazení' href='browDOC.php?PROTOKOL_ID=".$ID."'>".$db1->Record['POCET']."</a>";
  }
  else
    $res = '0';
  return $res;
}

function TableCeskaPostaVypraveni($doporucene) {
  $ret = $GLOBALS['doporucene'][$doporucene];
  if (!$ret) $ret = $doporucene;
  return $ret;
}

function TableDeniky($main_doc) {
  $ret = $GLOBALS['of_select_deniky'][$main_doc];
  if (!$ret) $ret = $main_doc;
  return $ret;
}

function ShowProtokolSuperodbor($so, $protokol, $rok) {
  $so_ret = $GLOBALS['of_superodbor_prefix'][$so];
  if ($so_ret) $ret .= $so_ret . '/';
  if ($protokol) $ret .= $protokol . '/';
  if ($rok) $ret .= $rok;
  $ret = '<b>' . $ret . '</b>';
  return $ret;
}

function EPA($ID) {
  $res="<a href='epa.php?&ID=".$GLOBALS[ID]."' target='ifrm_get_value' title='Generovat elektronický podací arch'>ePa</a>";
  return $res;
}

include_once(FileUp2('posta/.admin/table_func.inc'));
?>
<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
