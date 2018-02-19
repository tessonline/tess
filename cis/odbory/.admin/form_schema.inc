<?php
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 

$kody=explode(':',$GLOBALS["PRAVA"]);
//print_r($kody);
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_odbor", "name"=>"ID_ODBOR","frozen"=>!$is_insert)),
                   "label"=>"Odbor/oddělení:");
                   
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"ZKRATKA")),
                   "label"=>"Zkratka odboru/oddělení:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"ALTNAZEV")),
                   "label"=>"Alternativní název:");

$FORM_CONFIG["schema"][] = array("elements"=>array(
                     array( "type"=>"checkbox","name"=>"AKTIVNI")),
                     "label"=>"Aktivní:");
                   

$FORM_CONFIG["schema"][] = array( "label"=>"Spisové znaky:");



$q=new DB_POSTA;
$q->query ("select * from cis_posta_skartace order by id,kod");
$puvodni="";
while($q->next_record())
{ $i++;
  $id=$q->Record["ID"];
  $kod=$q->Record["KOD"];
  $nazev=$q->Record["TEXT"];
  
  If ($kod<>$puvodni)
  {
    If (in_array($kod,$kody)) {$checked='CHECKED';} else  {$checked='';}
    UNSET($GLOBALS['KOD']);
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "multiple"=>1,"name"=>"KOD","array_val"=>$id,"add"=>$checked)),
//  						"format"=>"KOD...'$nazev'",
  					"label"=>$nazev);
    $puvodni=$kod;
   }
  }

?>
