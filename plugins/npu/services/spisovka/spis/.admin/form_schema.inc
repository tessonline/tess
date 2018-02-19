<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
$hash = md5(Date('dmYHis'));
echo "<span class='text'><p>Pro správné přiřazení památky postupujte prosím následovně:<br/>
1. Klikněte na ikonu <b>Přiřadit památku z MonumNetu</b><br/>
2. V MonumNetu vyberte odpovídající památku a poté vyberte volbu <b>Vložit vazbu</b><br/>
3. V původním okně vyberte ikonu <b>Načíst data z MonumNetu</b>. <br/>
</></p>
Pokud poběhlo vše v pořádku, budou pole Jmenný název a Externí identifikátor vyplněna údaji z MonumNetu.
</p></span>";
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"SPIS_ID"),
                  array( "type"=>"text", "name"=>"NAZEV_SPISU"),
                   ),
                  "format"=>"NAZEV_SPISU",
                  "label"=>"Jmenný název:");
  
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"KATASTR"),
                   ),
                  "format"=>"KATASTR",
                  "label"=>"Katastr:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"EXT_ID"),
                   ),
                  "format"=>"EXT_ID...'&nbsp;<span id=\"PAMATKY_VAZBA\" style=\"font-weight:bold;\"></span><input class=\"button\" type=\"button\" value=\"Přiřadit památku z MonumNetu\" onclick=\"".
                  "window.open('".$PROPERTIES['vazba']."&ident=".$hash."&SPIS_ID=".$GLOBALS['SPIS_ID']."','guide','height=600px,width=600px,scrollbars,resizable');\">'",
                  "label"=>"Externí identifikátor:");
  

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"TEMP","frozen"=>true),
                   ),
                   "format"=>"TEMP...'&nbsp;<input class=\"button\" type=\"button\" value=\"Načíst data z MonumNetu\" onclick=\"".
                "window.open('receive.php?ident=".$hash."','ifrm','');\">'",
                  "label"=>"Zpětné načtení:");
  
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  

