<?php
include(FileUp2(".admin/config.inc"));
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$is_admin=($USER_INFO["LOGIN"]=='onma')?false:true;
$GLOBALS['HODNOTA'] = str_replace('\\', '', $GLOBALS['HODNOTA']);
$GLOBALS['POPIS'] = str_replace('\\', '', $GLOBALS['POPIS']);

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_nastaveni_kategorie", "name"=>"KATEGORIE","insertnull"=>$is_filter,"frozen"=>$is_edit,"frozen"=>$is_admin),
//            array( "type"=>"select_referent", "name"=>"PUV_REFERENT"),
            ),
            "label"=>"Kategorie:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_nastaveni_typ", "name"=>"TYP","insertnull"=>$is_filter,"frozen"=>$is_edit,"frozen"=>$is_admin),
            ),
            "visible"=>!$is_filter,
            "label"=>"Typ hodnoty:");							

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"PARAMETR","insertnull"=>$is_filter,"frozen"=>$is_edit,"size"=>50,"frozen"=>$is_admin),
            ),
            "visible"=>!$is_filter,
            "label"=>"Parametr:");							
 
if ($GLOBALS["TYP"]=='text' || $GLOBALS[TYP]=='number') $select=$GLOBALS[TYP];
else $select="text";

if ($GLOBALS["TYP"]=='textarea')
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"textarea", "name"=>"HODNOTA","cols"=>50,"rows"=>10),
            ),   
            "visible"=>!$is_filter,
            "label"=>"Popis:");		
else
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>$select, "name"=>"HODNOTA","size"=>50,"required"=>true),
            ),   
            "visible"=>!$is_filter,
            "label"=>"Hodnota:");		



 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"textarea", "name"=>"POPIS","cols"=>50,"rows"=>5,"frozen"=>$is_admin),
            ),   
            "visible"=>!$is_filter,
            "label"=>"Popis:");		


if ($GLOBALS['CONFIG']['USE_SUPERODBOR'] && HasRole('spravce')) {

  $FORM_CONFIG["schema"][] = array("label"=>"Nastavení pro pracoviště");
  $prac = getSelectDataEed(new of_select_superodbor(array()));

  foreach($prac as $key => $val) {
    $name = 'PRACOVISTE_' . $key;
    if (EedTools::JeNastaveniKonfigurace($key, $GLOBALS['PARAMETR'])) $checked = 'CHECKED'; else $checked='';
   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array(
                "type"=>"checkbox",
                "name"=>"PRACOVISTE",
                "multiple"=>1,
                'array_val' => $key,
                'add' => $checked),
              ),
              "visible"=>!$is_filter,
              "label"=>$val);
  }

}