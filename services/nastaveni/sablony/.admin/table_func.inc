<?php

include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['typ_posty'] = getSelectDataEed(new of_select_typ_posty(array('selectfull'=>true)));

Function UkazOdkazNaSablonu($id,$sablona,$id_sablony=0)
{
  if ($id) {
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
  $cela_cesta=$cesta."/sablony/";
  $nazev_souboru=md5($id);
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";

  $cesta=GetAgendaPath("POSTA",true,false)."/output/doc/send_to_word.php?ID=$id&sablona=$sablona&id_sablony=$id_sablony";
  $res="<a href=\"$cesta\" target=\"ifrm_get_value2\"><img src=\"".FileUp2('images/wordicon.gif')."\" border=0 alt='Otevřít existující dokument'></a>";
  }
  else {
    $res = '&nbsp;';
  }
  return $res;
}

Function ukazTypPosty($typ_id) {
  $ret = $GLOBALS['typ_posty'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}

Function agendaDokumentu($typ_id) {
  $ret = $GLOBALS['typ_posty'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}

function selectedAgenda($typ_posty = 0, $so_null = true) {
  $db = new DB_POSTA;
  if (!$typ_posty) $typ_posty = 0;
  $append = "";
  if ($so_null) $append = " a.id_superodbor IS null AND "; 
  $sql = "SELECT a.id,a.nazev,a.poradi FROM cis_posta_agenda a join cis_posta_typ t on a.id=t.id_agendy WHERE ".$append." t.id = ".$typ_posty;
  $db->query($sql);
  $db->Next_record();
  return $db->Record['ID'];
}

