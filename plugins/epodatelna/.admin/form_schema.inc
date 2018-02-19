<?php
  
$FORM_CONFIG["schema"][] = array( "label"=>"1. Výběr souboru:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"file", "name"=>"UPLOAD_FILE")),
                   "label"=>"soubor s XML importem:");

$FORM_CONFIG["schema"][] = array( "label"=>"2. Nastavení hodnot:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_referent", "name" => "REFERENT", "fullselect" => true, "insertnull" => true)),
                   "label"=>"Dokumenty budou uloženy k zpracovateli:");

// $FORM_CONFIG["schema"][] = array( "elements"=>array(
//                    array( "type"=>"checkbox", "name"=>"VSE_STEJNE_CJ"),
//                    array( "type"=>"checkbox", "name"=>"VSE_NOVE_CJ"),
//                    array( "type"=>"text_number", "name"=>"CISLO_SPISU1", "size"=>8),
//                    array( "type"=>"text_number", "name"=>"CISLO_SPISU2", "size"=>4),
//                    ),
//                    "format"=>"VSE_NOVE_CJ...'&nbsp;Každý dokument bude mít nové čj.&nbsp;NEBO<br/>".
//                              "'...VSE_STEJNE_CJ...'&nbsp;Všechny dokumenty bude mít stejné čj.&nbsp;(nově přidělené)&nbsp;NEBO<br/>".
//                           "Všechny okumenty budou mít čj. '...CISLO_SPISU1...'/'...CISLO_SPISU2",
//                    "label"=>"Přiřazení čj.:");

// z duvodu, aby se v tagu form pridalo enctype="multipart/form-data" viz. ooohforms.inc
$f->isfile = true;
