<?php
include_once(FileUp2(".admin/table_func.inc"));
/**
 * SABLONY
 */
$testovani=array('xxxxx');
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$login = $USER_INFO["LOGIN"];

$add = '';
//if (HasRole('lokalni-spravce'))
$add = ' AND (id_superodbor IS NULL OR id_superodbor='.EedTools::VratSuperOdbor().')';

If (!in_array($login,$testovani)) {
//plny rezim, vyber sablon
//jdeme zjistit, do jakeho odboru patri
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:VratOdbor();
  If (HasRole('editace_admin')) {
    $sql="SELECT id,nazev FROM posta_cis_sablony ORDER BY poradi asc,id asc";
  }
  else {
    $GLOBALS["ODBOR"]=$GLOBALS["ODBOR"]?$GLOBALS["ODBOR"]:0;
    if ($GLOBALS['ODBOR'] > 0) {
      $odbory = array();
      $odbory[] = $GLOBALS['ODBOR'];
      $user_obj = LoadClass('EedUser', 11);
      $unity = $user_obj->VratOdborZSpisUzlu($GLOBALS['ODBOR']);
      $podrizene_unity = $user_obj->VratNadrizeneUnity($unity);
      foreach($podrizene_unity as $unita => $val) {
        $temp = $user_obj->VratSpisUzelZOdboru($unita);
        if ($temp['ID']>0) $odbory[] = $temp['ID'];
      }
    }


 //     $sql="SELECT id,nazev FROM posta_cis_sablony WHERE odbor in (".implode(',',$odbory).") or odbor is null ".$add." ORDER BY poradi asc,id asc";
      $sql="SELECT id,nazev FROM posta_cis_sablony WHERE (odbor in (".implode(',',$odbory).") or odbor is null or odbor=0)  ".$add." ORDER BY poradi asc,id asc";
   }
//testovaci rezim s oknem
  static $qqq;
  If (!$qqq) $qqq=new DB_POSTA;
  $text_sablona.="<div class=\"form-field\"><select name='sablony' style=\"width:260px;\"><option value=''></option>";
  $qqq->query($sql);
  while ($qqq->Next_Record()) {
    $sablona=$qqq->Record['ID'];
    $selected = "";
    If ($GLOBALS["CONFIG"]["POUZIVAT_COOKIES"] && $sablona==$_COOKIE["TWIST_POSTA_VybranaSablona"] ) $selected="SELECTED"; 
    if ($sablona ==vybranaSablona($GLOBALS['TYP_POSTY'])) $selected='selected';
    $text_sablona.='<option value='.$sablona.' '.$selected.'>'.$qqq->Record['NAZEV'].'</option>';
  }
  $text_sablona.="</select></div>";
  $ikony = "<div class=\"form-append\"><a href=\"javascript:Sablona_Nove(".$GLOBALS['EDIT_ID'].")\"   title='vygenerovat dokument v této šabloně'><img src='".FileUpImage('images/file')."' border=0></a></div></div>";

  if ($GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"]) {
    $GLOBALS['EXPORT_ALL_step']=true; //aby se nam nenacitali JS
    include_once('.admin/table_funkce.inc');
    if (ExistujeSoubor($GLOBALS["ID"],$GLOBALS["CISLO_JEDNACI1"],$GLOBALS["CISLO_JEDNACI2"])<>'&nbsp;')
      $ikony .= "<a href=\"javascript:Sablona_Smazat(".$GLOBALS['EDIT_ID'].")\"   title='smazat existující dokument'><img src='".FileUp2('images/spis_ko.gif')."' border=0></a>";
  }
}
else {
//testovaci rezim
  If (is_array($GLOBALS["CONFIG"]["SABLONY"]))
    while (list($key,$val)=each($GLOBALS["CONFIG"]["SABLONY"]))
      $ikona.="<div class=\"form-append\"><a href=\"javascript:Sablona('".$val[FILE]."')\"   title='".$val[TITLE]."'><img src='".FileUpImage($val[IKONA])."' border=0></a></div>";

}
$FORM_CONFIG["schema"][] = array("elements"=>array(
          ),
          "format"=>"'$text_sablona$ikony&nbsp;'",
		  "add"=>"style=\"width:130px;\"",
     	  "label"=>"Šablony:");


/**
 * OBALKY
 */

$text_sablona = '';
If ($GLOBALS["ODESLANA_POSTA"]=='t') {
  static $qqq;
  If (!$qqq) $qqq=new DB_POSTA;
  $text_sablona.="<div class=\"form-field\"><select name='obalka' style=\"width:260px;\">";
  $qqq->query("select * from posta_cis_obalky where aktivni='1' ".$add." ORDER BY poradi asc,id asc");
  while ($qqq->Next_Record())  {
    $obalka=$qqq->Record['ID'];
    If ($GLOBALS["CONFIG"]["POUZIVAT_COOKIES"] && $obalka==$_COOKIE["TWIST_POSTA_VybranaObalka"] ) $selected="SELECTED"; else $selected="";
    $text_sablona.='<option value='.$obalka.' '.$selected.'>'.$qqq->Record['NAZEV'].'</option>';
  }
  $text_sablona.="</select></div>";
  $text_sablona.="<div class=\"form-append\"><a href=\"javascript:Obalka(".$GLOBALS['EDIT_ID'].")\"   title='Otevřít obálku do PDF'><img src='".FileUpImage('images/mail')."' border=0></a></div>";
  
  


$FORM_CONFIG["schema"][] = array("elements"=>array(
            ),
            "format"=>"'$text_sablona'",
            "label"=>"Obálky:");
}
//$text_sablona = '<div class="form-append">';

/*
   $FORM_CONFIG["schema"][] = array("elements"=>array(
                ),
                "format"=>"'$text_sablona'", 
                "label"=>"");	

*/

?>
