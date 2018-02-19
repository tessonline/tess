<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
$hash = md5(Date('dmYHis'));
echo "<span class='text'><p>Pro správné přiřazení GIS objektu postupujte prosím následovně:<br/>
<p>
1. Zadejte odpovídající identifikátor (paGIS nebo přírůstkový bod)<br/>
nebo<br/>
2. Vyberte odpovídající objekt pomocí mapy (viz. ikona Načíst z mapy)<br/>
</p></span>";
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"SPIS_ID"),
                  array( "type"=>"text", "name"=>"PAGIS"),
                   ),
                  "format"=>"PAGIS",
                  "label"=>"Identifikátor paGIS:");
  
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"PRIRUST"),
                   ),
                  "label"=>"Přírůstkový bod:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"TEMP","frozen"=>true),
                   ),
                   "format"=>"TEMP...'&nbsp;<input class=\"button\" type=\"button\" value=\"Načíst z mapy\" 
   onClick=\"javascript:NewWindowSpisovna('".GetAgendaPath("POSTA_VAZBA_GIS",false,true)."/edit.php?insert&DOKUMENT_ID=".$spis_id."');return false;\">\n\"'",
                   "label"=>""); 
