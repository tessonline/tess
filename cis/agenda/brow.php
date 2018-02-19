<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/config.inc"));

/*$spravce = HasRole("spravce");
$lokalni_spravce = HasRole("lokalni-spravce");
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$odbor[]=VratOdbor($USER_INFO['GROUP_ID']);
if($odbor[0]==-1) $odbor[0] = 0;*/

if (isset($GLOBALS['ID'])) {
  
  if ($GLOBALS['ID']) 
    $_SESSION['ID_AGENDY'] = $GLOBALS['ID'];
  else
    $GLOBALS['ID'] = $_SESSION['ID_AGENDY'];
    
  
  $agenda_id = $_SESSION['ID_AGENDY'];
  
  //$app_where = "id_agenda=".$agenda_id; 
  

  
  Table(array(
    "tablename" => "AGENDY",
    "showaccess" => true, 
    "showself" => true,
    "showedit" => true,
    "setvars" => true,
  ));
  
  $app_where = "";
  unset($GLOBALS['NAZEV']);
  unset($GLOBALS['PORADI']);
  unset($GLOBALS['NEAKTIVNI']);
  unset($GLOBALS['EXTERNAL_ID']);

  if (!isset($GLOBALS['ID_AGENDY']))
    $app_where = " ID_AGENDY=".$agenda_id;
  
  
/*  if (!$spravce) {
    $app_where.= "AND (odbor in (".implode(",",$odbor).")  or odbor is null) AND ID_AGENDY=".$agenda_id;
  }*/ 
  
    
  unset($GLOBALS['ID']);
  Table(array(
    "tablename" => "DRUH_DOKUMENTU",
    'agenda'=>'CIS_POSTA_TYP',
    'showaccess'=>true,
    'showedit'=>true,
    'showinfo'=>true,
    'showdelete'=>true,
    'appendwhere'=> $app_where,
    'showselfurl' => GetAgendaPath("POSTA", 0, 1)."/cis/agenda/index.php?frame&ID=".$agenda_id."&ID_TYP='...ID...'",
    'showself' => true,
    'unsetvars' => true,
    'setvars' => true
  ));
  
  $button = "<input type=\"submit\" class=\"btn button\" value=\"Přidat druh dokumentu\" onClick=\"javascript:NewWindowEditDRUH_DOKUMENTU('".GetAgendaPath("POSTA", 0, 1)."/cis/typ_posty/edit.php?insert&doc=".$agenda_id."&cacheid=');return false;\">\n";
  
  foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
    if ($plug['enabled']){
      $file = FileUp2('plugins/'.$plug['dir'].'/brow_workflow.inc');
      if (File_Exists($file)) include($file);
    }
  }
    
  $GLOBALS['ID'] = $agenda_id;
  
  echo '<form>'.$button.'</form>';
  
} else {
  if (HasRole('access_all')) {
    $app_where = " AND id_superodbor is null";
    include_once(FileUp2('.admin/brow_superodbor.inc'));
    if ($GLOBALS['omez_zarizeni']) $app_where = " AND id_superodbor=" . $GLOBALS['omez_zarizeni'];
  } else {
    $app_where.=" AND ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() .")";
  }
  
  $GLOBALS['APP_WHERE'] = $app_where;
    
  Table(array(
    "tablename" => "AGENDY",
    "showaccess" => true, 
    "showself" => true,
    "appendwhere"=> $app_where,
    'setvars' => true
    ));
}

require(FileUp2("html_footer.inc"));
?>
