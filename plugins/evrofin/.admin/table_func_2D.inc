<?php

NewWindow(array(
  "name"=>"map_link", 
  "fname"=>"MapLink", 
  "width"=>400, "height"=>10, "left"=>8000, "top"=>1,
  "header"=>true,
  "features"=>"", 
  "modal"=>false
));    

function ShowMapADR($adresa_kod) {
  global $CONFIG;
  static $img;
  if (!$img) 
    $img = FileUp_Main('images/globe.gif', $CONFIG["IDENT_PREFIX"]."INDEX");
  $func = $CONFIG["MAP_CONDITION"]; 
  if ($func(array("adresa_kod"=>$adresa_kod))) {
    $res = "<a href=\"javascript:NewWindowMapLink('map.php?Command=SelByFld&Field=OBJEKT_KOD&Values=".$adresa_kod."&Theme=budovy&DoSel=0&PinColor=\$FF&DrawPin=1&Scale=2000&Zoom=ToExtent&MinScale=2000');\"><img alt=\"Mapa\" src=\"".$img."\" border=\"0\"></a>";
  } else { 
    $res = "&nbsp;";
  }
  return $res;
}

/*function ShowMapADR($adresa_kod) {
  global $CONFIG;
  static $img;
  if (!$img)
    $img = FileUp_Main('images/globe.gif', $CONFIG["IDENT_PREFIX"]."INDEX");
  $func = $CONFIG["MAP_CONDITION"]; 
  if ($func(array("porcis"=>$porcis, "parcis"=>$parcis, "parpod"=>$parpod, "parskup"=>$parskup))) {
    $res = "<a href=\"map.php?Command=SelByFld&Field=".$CONFIG["MAP_THEME_FIELD"]."&Values=".$adresa_kod."&Theme=".$CONFIG["MAP_THEME"]."&DoSel=0&PinColor=".$CONFIG["MAP_PIN_COLOR"]."&DrawPin=1&Scale=2000&Zoom=ToExtent&MinScale=2000"."\"><img alt=\"Mapa\" src=\"".$img."\" border=\"0\"></a>";
  } else {
    $res = "&nbsp;";
  }
  return $res;
}
*/
function Domcislo($t, $h) {
  $q = "";
  if ($t == 1):
    $q .= "č. p. <b>".$h."</b>";
  else:    
    $q .= "č. e. <b>".$h."</b>";
  endif;
  $q .= "&nbsp;";
  return $q;
} 

function Ocislo($h, $p) {
  $q = "";
  if ($h):
    $q .= "<b>".$h.$p."</b>";
  else:    
    $q .=  "<b>&nbsp;".$p."</b>";
  endif;
  $q .= "&nbsp;";
  return $q;
} 

function XZpet (){
  $q = "<a href=\"".$SERVER_CONFIG["SERVER_WWW_ROOT"]."/php/uiradr3\" target=\"_top\"><img src=\"../../images/find.gif\" border=\"0\" alt=\"hledání\" valign=\"bottom\"></a>";
  return $q;
}

function FCE_UkonceniA($ulk){
  static $img = '';
  if (!$img) $img = FileUp2("images/trash.gif");
  $res = "&nbsp;";
  if (HasRole("all_update")){
    $ulk .= "&ukonceni=true";
    $res = "<a href=javascript:edit_ui_adresa('$ulk')>";
    $res .="<img src=\"$img\" alt=\"Demolice\" border=\"0\"></img></a>\n";
  }  
  return $res;
}

function Dum($cobce,$cdom,$cdom_typ){
  static $img = '';
  if (!$img) $img = FileUp2("images/ownership/house.gif");
    $res = "<a href=\"".GetAgendaPath("DOMY")."/brow.php?COBCE_KOD=$cobce&CDOM_HOD=$cdom&CDOM_TYP=$cdom_typ\">";
    $res .="<img src=\"$img\" alt=\"Dům\" border=\"0\"></img></a>\n";
  return $res;
}

function Obyvatele($adresa){
  static $img = '';
  if (!$img) $img = FileUp2("images/two_people.gif");
    $res = "<a href=\"".GetAgendaPath("OBYVATELE")."/brow.php?UIR_ADRESA=$adresa\">";
    $res .="<img src=\"$img\" alt=\"Obyvatelé\" border=\"0\"></img></a>\n";
  return $res;
}

function ChangeClassMy($t) {
//print_r($GLOBALS);
  if ($GLOBALS["STAV"]==12 || $GLOBALS["STAV"]==2) $color="_violet";
//  $color="_violet";
  static $i;
  if ($i):
    $t->classname = "brow".$color;
    $i = 0;
  else:
    $t->classname = "browdark".$color;
    $i = 1;
  endif;
}

function CheckBoxs($id,$stav){
 if ($stav != 12)
    $res = "<input type=\"radio\" name=\"SELECT_ID\" value=\"$id\"></input>";
 else $res = "&nbsp;";   
 return $res;
}
?>
