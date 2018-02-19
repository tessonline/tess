<?php

$co=StrTok($GLOBALS["QUERY_STRING"], '&');
Form_(array("showaccess"=>true, "nocaption"=>true));

if ($co=='edit')
  $is_edit = true;
else
  $is_edit = true;

echo "<table width='100%'><tr><td width='50%'>";
  require(FileUp2(".admin/brow_.inc"));
  UNSET($LAST_DATE);
  UNSET($LAST_TIME);
  UNSET($LAST_USER_ID);
  UNSET($OWNER_ID); 
  UNSET($ID); 
//  $GLOBALS['SPIS_ID'] = $DOKUMENT_ID;
  $count = Table(array(
     "agenda" => "POSTA_UKLZNACKA",
      //"tablename" => "posta_uklznacka", 
     //"sql" => "select * from posta_uklznacka where spis_id in (".$DOKUMENT_ID.")",
     "appendwhere" => " AND spis_id in (".$DOKUMENT_ID.")",
     "maxnumrows"=>10,
     //"nopaging"=>$nopaging,
     "showdelete"=>$is_edit, 
     "showedit" => false, 
     "showinfo" => false,	 
     "nocaption" => false,
     "showaccess"=>true,
     "setvars"=>true,
  ));

  $doc_id = $DOKUMENT_ID;
  
  NewWindow(array("fname" => "Spis", "name" => "spis_znacka", "header"=>true, "cache" => false, "window" => "edit"));
  
//   echo "<form name=\"spis_pridat\" method=\"GET\">\n";
//   if ($co<>"info") echo "<input type=\"submit\" class=\"btn\" value=\"Přidat ukládací značku\"
//   onClick=\"javascript:NewWindowSpis('".GetAgendaPath("POSTA_UKLZNACKA",false,true)."/edit.php?insert&SPIS_ID=".$DOKUMENT_ID."');return false;\">\n";
//
//   echo "</form>";
//
//   echo "</td><td width='50%'>";
//   if ($GLOBALS['CONFIG']['UKLADACI_ZNACKY']) {
//     $count=Table(array(
//       "agenda" => "POSTA_SPIS",
//       "tablename" => "posta_spis",
//       "appendwhere" => "and spis_id=".$DOKUMENT_ID,
//       "maxnumrows"=>1,
//       "showhistory" => false,
//       "showedit" => false,
//       "showinfo" => false,
//       "showdelete"=>$is_edit,
//       //"nocaption"=>true,
//       "showaccess"=>true,
//       "setvars"=>true,
//       "unsetvars"=>true,
//       "emptyoutput" => false,
//     ));
//   //  if ($count==0)
//     NewWindow(array("fname" => "SpisPam", "name" => "spis_pridat", "header"=>true, "cache" => false, "window" => "editXXam"));
    
//     echo "<form name=\"SpisPam\" method=\"GET\">\n";
//     if (!$spis_uzavren && $co<>"info") echo "<input type=\"submit\" class=\"btn\" value=\"Přiřadit památku\"
//     onClick=\"javascript:NewWindowSpisPam('http://monumnet.npu.cz/spis/esspam.php?dol=&SPIS_ID=".$DOKUMENT_ID."');return false;\">\n";
//     if (!$spis_uzavren && $co<>"info") echo "&nbsp;&nbsp;&nbsp;<input type=\"submit\" class=\"btn\" value=\"Obnovit\"
//     onClick=\"javascript:document.location.reload();return false;\">\n";
//     echo "</form>";
//   }

  echo "</tr></table>";
  $table = '/.admin/table_schema_simple.inc';
  require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');
  require_once(GetAgendaPath('POSTA',false,false).'/services/spisovka/uzavreni_spisu/funkce.inc');
  $cj_obj = new EedCj($DOKUMENT_ID);
  $dalsi_cj=$cj_obj->SeznamCJvSpisu($DOKUMENT_ID);
  $table_schema=array(
    "showaccess"=>0,
    "showupload"=>0,
    'schema_file' => $table,
    "modaldialogs" => false,
    "setvars"=>true,
    "showhistory"=>true,
    "showdelete"=>$is_edit,
    "showdelete"=>$is_edit,
    "showedit" => false,
    "showdelete"=>0,
  );
  UkazSpis_Obj($doc_id,0,$table_schema);
  $GLOBALS["ukaz_ovladaci_prvky"] = false; 
  if (count($dalsi_cj)>0)
  while (list ($key, $val) = each ($dalsi_cj))  {
    $cj_obj_temp = new EedCj($val);
    $cj_obj_info = $cj_obj_temp->GetCjInfo($val,1);
    $spis_vazba = $cj_obj_temp ->SpisVazba($DOKUMENT_ID, $val);
    UkazSpis_Obj($val,$spis_vazba['OWNER_ID'],$table_schema);
    $idcko=$spis_vazba['ID'];
  }

require(FileUp2("html_footer.inc"));

Die();