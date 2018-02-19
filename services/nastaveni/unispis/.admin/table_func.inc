<?php

Function UkazOdkazNaSablonu($id,$sablona,$id_sablony=0)
{
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
  $cela_cesta=$cesta."/sablony/";
  $nazev_souboru=md5($id);
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";

  $cesta=GetAgendaPath("POSTA",true,false)."/output/doc/send_to_word.php?ID=$id&sablona=$sablona&id_sablony=$id_sablony";
  $res="<a href=\"$cesta\" target=\"ifrm_get_value\"><img src=\"".FileUp2('images/wordicon.gif')."\" border=0 alt='Otevřít existující dokument'></a>";
  return $res;
}

?>
