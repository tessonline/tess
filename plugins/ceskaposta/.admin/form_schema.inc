<?php
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/security_name.inc"));
//include_once(FileUp2(".admin/table_funkce.inc"));
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
{
  $odborova_podatelna=true;
  $GLOBALS["ODBOR"]=VratOdbor();
}


If ($is_insert)
{
//  if ($GLOBALS["ODBOR"]>0) $append=" WHERE ODBOR IN (".$GLOBALS["ODBOR"].") ";
  $append=" AND superodbor in (".EedTools::VratSuperOdbor().")";
  $w=new DB_POSTA;
  $sql="select max(protokol) as max_protokol from posta_cis_ceskaposta where rok in ('".Date('Y')."') $append  ";
  $w->query($sql);
  $w->Next_Record();
  $cislo=$w->Record["MAX_PROTOKOL"]?$w->Record["MAX_PROTOKOL"]:0;
  $cislo++;
  $GLOBALS["ROK"]=Date('Y');
  $GLOBALS["PROTOKOL"]=$cislo;

  $w=new DB_POSTA;
  $sql="select * from posta_cis_ceskaposta WHERE 1=1 $append order by rok desc,protokol desc";
  $w->query($sql);
  $w->Next_Record();
  $GLOBALS["DATUM_OD"]=$w->Record["DATUM_DO"]?$w->str2dbdate($w->Record["DATUM_DO"]):0;
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"ROK"),
            ),
            "label"=>"");							

}

If ($GLOBALS["MESICNI_VYKAZ"])
{

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"date_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>true,'label'=>'Datum od:'),
            array( "type"=>"date_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>true,'label'=>'Datum do:')),
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO",
            "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              )
            )
      );
}
else
{
If ($GLOBALS[DATUM_VRACENI]) $frozen=true; else $frozen=false;

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"PROTOKOL","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Číslo protokolu:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO_OD","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Číslo R - od:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO_DO","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Číslo R - do:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"CISLO2_OD","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"Číslo R - pokračovat do:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"OBYC1","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"<b>Přičíst obyč. standartní psaní:</b>");
            
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"OBYC2","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>"<b>Přičíst psaní ZR:</b>");
            
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"OBYC3","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>" obyč. psaní do 50g:");							
            
  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text_number", "name"=>"OBYC4","frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?false:true) || $frozen,
            "label"=>" obyč. psaní do 200g:");							
            


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"frozen"=>$frozen||$odborova_podatelna),
            array( "type"=>"hidden", "name"=>"SUPERODBOR","value"=>EedTools::VratSuperOdbor(),"frozen"=>$frozen),
            ),
            "visible"=>$is_insert or $frozen,
            "label"=>"Odbor:");							

$FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"select_deniky", "name"=>"MAIN_DOC"),
        ),
            "visible"=>($is_insert or $frozen) && $GLOBALS['CONFIG_POSTA']['PLUGINS']['deniky']['enabled'],
        "label"=>"Evidence:");


  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"PROTOKOL","value"=>$GLOBALS[PROTOKOL],"frozen"=>$frozen),
            ),
            "label"=>"");							
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_OD","insertdatebutton"=>true,"required"=>$odborova_podatelna,"frozen"=>$frozen,'label'=>'Datum od:'),
            array( "type"=>"datetime_db", "name"=>"DATUM_DO","insertdatebutton"=>true,"required"=>$odborova_podatelna,"frozen"=>$frozen,'label'=>'Datum do:')),
            "format"=>"DATUM_OD...'&nbsp;do&nbsp;'...DATUM_DO...'<br/><small>Pozn:Datum Od je předvyplněno z předchozího protokolu,<br/>lze samozřejmě změnit'",
            "visible"=>$is_insert or $frozen,
            "label"=>"Datum od:",
              // zruseni format pro tema square
            'theme_config' => array(
              'square' => array(
                'format' => '',
              ),
             ),
            );

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"datetime_db", "name"=>"DATUM_VRACENI","insertdatebutton"=>true,"frozen"=>$frozen),
            ),
            "visible"=>($GLOBALS[DATUM_VYTISTENI]?true:false) || $frozen,
            "label"=>"Datum převzetí Českou poštou:");							

}
?>
