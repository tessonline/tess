<?php
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/table_funkce.inc"));
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 


If (!(HasRole('spravce')||HasRole('podatelna')))
  $odbor=VratOdbor();

//echo $odbor;
If ($is_insert)
{
  if ($GLOBALS["ODBOR"]>0) $append=" WHERE ODBOR IN (".$odbor.")";
  $w=new DB_POSTA;
  $append="WHERE  superodbor in (".VratSuperOdbor().")";
  $w=new DB_POSTA;
  $sql="select max(protokol) as max_protokol from posta_cis_ceskaposta where rok in ('".Date('Y')."') and superodbor in (".VratSuperOdbor().") ";
  $w->query($sql);
  $w->Next_Record();
  $cislo=$w->Record["MAX_PROTOKOL"]?$w->Record["MAX_PROTOKOL"]:0;
  $cislo++;
  $GLOBALS["ROK"]=Date('Y');
  $GLOBALS["PROTOKOL"]=$cislo;

  $w=new DB_POSTA;
  $sql="select * from posta_cis_dorucovatel $append order by rok desc,protokol desc";
  $w->query($sql);
  $w->Next_Record();
  $GLOBALS["DATUM_OD"]=$w->Record["DATUM_DO"]?$w->Record["DATUM_DO"]:0;
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"ROK"),
            ),
            "label"=>"");							

}

If ($GLOBALS[DATUM_VRACENI]) $frozen=true; else $frozen=false;

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"PROTOKOL","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Číslo protokolu:");							


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO2_OD","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Počet obyčejných:");							

  If ($odbor)
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","value"=>$odbor,"frozen"=>true),
              ),
              "visible"=>$is_insert or $frozen,
              "label"=>"Odbor:");							
  else
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true,"frozen"=>$frozen),
            array( "type"=>"hidden", "name"=>"SUPERODBOR","value"=>VratSuperOdbor(),"frozen"=>$frozen),
              ),
              "visible"=>$is_insert or $frozen,
              "label"=>"Odbor:");							


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"PROTOKOL","value"=>$GLOBALS[PROTOKOL],"frozen"=>$frozen),
            ),
            "label"=>"");							
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,"frozen"=>$frozen),   
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,"frozen"=>$frozen)),   
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'<br/><small>Pozn:Datum Od je předvyplněno z předchozího protokolu,<br/>lze samozřejmě změnit'",
            "visible"=>$is_insert or $frozen,
            "label"=>"Datum od:");		

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_VRACENI","insertdatebutton"=>true,"frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?true:false) || $frozen,
            "label"=>"Datum převzetí doručovatelem:");							


?>
