<?php
//
include(FileUp2(".admin/config.inc"));

if ($form_params["formtype"] == $f_insert) $is_insert = true;
else $is_insert = false;
if ($form_params["formtype"] == $f_info) $is_info = true;
else $is_info = false;
if ($form_params["formtype"] == $f_edit) $is_edit = true;
else $is_edit = false;
if ($form_params["formtype"] == $f_filter) $is_filter = true;
else $is_filter = false;
if ($form_params["formtype"] == $f_filterall) $is_filterall = true;
else $is_filterall = false;

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_odes_typ", "name"=>"ODES_TYP", "width"=>10,"insertnull"=>true)),
  "visible"=>$is_filter,
  "label"=>"Odesílatel:"
);										 

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array("type"=>"text", "name"=>"ODESL_PRIJMENI","size"=>"40","label"=>"Příjmení"),   
  array("type"=>"text", "name"=>"ODESL_JMENO","size"=>"20","label"=>"Jméno"),
  array("type"=>"text", "name"=>"ODESL_TITUL","size"=>"5","label"=>"Titul")),
  "format"=>"ODESL_PRIJMENI...'&nbsp;&nbsp;&nbsp;Jméno:&nbsp;'...ODESL_JMENO...'&nbsp;&nbsp;&nbsp;Titul:&nbsp;'...ODESL_TITUL",
  "visible"=>$is_filter,										 
  "label"=>"Příjmení&nbsp;/&nbsp;Firma:"
);		

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"ODESL_ICO","size"=>"15","label"=>"IČO"),   
  array( "type"=>"text", "name"=>"ODESL_ODD","size"=>"20","label"=>"Oddělení"),   
  array( "type"=>"text", "name"=>"ODESL_OSOBA","size"=>"20","label"=>"Osoba")),
  "format"=>"ODESL_ICO...'&nbsp;&nbsp;&nbsp;Oddělení&nbsp;'...ODESL_ODD...'&nbsp;&nbsp;&nbsp;Kont.&nbsp;osoba&nbsp;'...ODESL_OSOBA",
  "visible"=>$is_filter_all,										 
  "label"=>"IČO:"
);		

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"ODESL_ULICE","size"=>"40","label"=>"Ulice"),   
  array( "type"=>"text", "name"=>"ODESL_CP","label"=>"č.p."),
  array( "type"=>"text", "name"=>"ODESL_COR","label"=>"č.orient.")),
  "format"=>"...ODESL_ULICE...'&nbsp;&nbsp;&nbsp;č.p.&nbsp;'...ODESL_CP...'&nbsp;&nbsp;&nbsp;č.orient.&nbsp;'...ODESL_COR",
  "visible"=>$is_filter,										 
  "label"=>"Ulice:"
);		

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"ODESL_PSC","label"=>"PSČ"),   
  array( "type"=>"text", "name"=>"ODESL_POSTA","size"=>"40","label"=>"Město")),
  "format"=>"ODESL_PSC...'&nbsp;&nbsp;&nbsp;Město&nbsp;'...ODESL_POSTA",
  "visible"=>$is_filter_all,										 
  "label"=>"PSČ:"
);		

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"ODESL_PSC","label"=>"PSČ","required"=>true),   
  array( "type"=>"text", "name"=>"ODESL_POSTA","size"=>"40","label"=>"Město")),
  "format"=>"ODESL_PSC...' '...ODESL_POSTA",
  "visible"=>$is_info,										 
  "label"=>""
);		

 /*
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM","insertdatebutton"=>true,"required"=>true),),   
            "label"=>"Dne:");		

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"POZNAMKA"),),   
            "label"=>"Poznámka:");		

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_odbor", "name"=>"ODBOR", "insertnull"=>true)),
  "visible"=>$is_filter,
  "label"=>"Odbor:"
);										 

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_referent", "name"=>"REFERENT", "insertnull"=>true)),
  "visible"=>$is_filter,
  "label"=>"Referent:"
);										 
*/
$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_platna_typ", "name"=>"FROZEN", "insertnull"=>true)),
  "visible"=>$is_filter,
  "label"=>"Adresa:"
);

$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_typ_view", "name"=>"TYP_VIEW")),
  "visible"=>$is_filter,
  "label"=>"Zobrazit:"
);
