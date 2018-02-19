<?php

// !!! POZOR upraveno pro potreby prezentace na SU
// !!! Zmeny jsou jednoucelove
// !!! Nepouzivat

include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_security.inc");

//echo " 1: ".$GLOBALS["PROPERTIES"]["FIELD_UPDATE_ID"];
//echo " 2: ".$met["LAST_USER_ID"];

//metadata z form_.inc
$met = array();
if(!is_array($arr)) $arr = $q->metadata($PROPERTIES["AGENDA_TABLE"]);
foreach($arr as $fld) $met[$fld['name']] = $fld['name'];

//SetFields values 
$FLD_CREATE_DATE = $GLOBALS["PROPERTIES"]["FIELD_CREATE_DATE"]?$GLOBALS["PROPERTIES"]["FIELD_CREATE_DATE"]:$met["CREATE_DATE"];
$FLD_OWNER_ID = $GLOBALS["PROPERTIES"]["FIELD_OWNER_ID"]?$GLOBALS["PROPERTIES"]["FIELD_OWNER_ID"]:$met["OWNER_ID"];
$FLD_UPDATE_DATE = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_DATE"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_DATE"]:$met["LAST_DATE"];
$FLD_UPDATE_TIME = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_TIME"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_TIME"]:$met["LAST_TIME"];
$FLD_UPDATE_ID = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_ID"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_ID"]:$met["LAST_USER_ID"];
$FLD_UPDATE_GROUP_ID = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_GROUP_ID"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_GROUP_ID"]:$met["LAST_GROUP_ID"];


switch ($form_params["formtype"]) {
  case $f_edit:
  case $f_info:

    $FORM_CONFIG["schema"][] = array(
      "label"=>$GLOBALS['RESOURCE_STRING']["owner_user_form_label"],
    );

    $FORM_CONFIG["schema"][] = array(
      "elements"=>array(array("type"=>"text_user", "name"=>"$FLD_OWNER_ID", "xfrozen"=>true)),
      "visible"=>$FLD_OWNER_ID?true:false,
      "label"=>$GLOBALS['RESOURCE_STRING']["owner_user_zalozil"].":"
    );

    $FORM_CONFIG["schema"][] = array(
      "elements"=>array(array("type"=>"date_db", "name"=>"$FLD_CREATE_DATE", "frozen"=>true)),
      "visible"=>$FLD_CREATE_DATE?true:false,
      "label"=>$RESOURCE_STRING['in_day'].":"
    );

    $FORM_CONFIG["schema"][] = array(
      "elements"=>array(array("type"=>"text_user", "name"=>"$FLD_UPDATE_ID", "frozen"=>true)),
      "visible"=>$FLD_UPDATE_ID?true:false,
      "label"=>$RESOURCE_STRING['last_editor'].":"
    );
        
    if($FLD_UPDATE_DATE && $FLD_UPDATE_TIME):
      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"text","name"=>"$FLD_UPDATE_DATE","frozen"=>true,"size"=>12),
               array("type"=>"text", "name"=>"$FLD_UPDATE_TIME","frozen"=>true,"size"=>12,"label"=>$RESOURCE_STRING['in_time'],"value"=>$GLOBALS[$FLD_UPDATE_TIME]?$GLOBALS[$FLD_UPDATE_TIME] : $GLOBALS['RSTR_OST']['meta_unknown'])),
            //"format"=>"$FLD_UPDATE_DATE...' ".strtolower($RESOURCE_STRING['in_time'])." '...$FLD_UPDATE_TIME",
            "label"=>$RESOURCE_STRING['in_day']
          );
    else:
      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"date_db","name"=>"$FLD_UPDATE_DATE","frozen"=>true)),
            "visible"=>$FLD_UPDATE_DATE?true:false,
            "label"=>$RESOURCE_STRING['in_day'].":"
          );

      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"text", "name"=>"$FLD_UPDATE_TIME","frozen"=>true, "value"=>$GLOBALS[$FLD_UPDATE_TIME]?$GLOBALS[$FLD_UPDATE_TIME] : $GLOBALS['RSTR_OST']['meta_unknown'])),
            "visible"=>$FLD_UPDATE_TIME?true:false,
            "label"=>$RESOURCE_STRING['in_time'].":"
          );
     endif;     

     $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"select_main_group","name"=>"$FLD_UPDATE_GROUP_ID","frozen"=>true)),
            "visible"=>$FLD_UPDATE_GROUP_ID?true:false,
            "label"=>$RESOURCE_STRING['group'].":"
          );
     
  break;

  case $f_filter:
    $FORM_CONFIG["schema"][] = array(
          "label"=>$GLOBALS['RESOURCE_STRING']["owner_user_form_label"],
        );
        
    if($FLD_UPDATE_ID && $FLD_OWNER_ID):   
      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"select_users","name"=>"$FLD_UPDATE_ID","insertnull"=>true,"extrahtml"=>'style="width: 150px"'),
               array("type"=>"select_users","name"=>"$FLD_OWNER_ID","insertnull"=>true,"extrahtml"=>'style="width: 150px"',"label"=>$GLOBALS[RESOURCE_STRING]["owner_form_label"])),
            //"format"=>"$FLD_UPDATE_ID...'&nbsp;&nbsp;&nbsp;".$GLOBALS[RESOURCE_STRING]["owner_form_label"].":&nbsp;'...$FLD_OWNER_ID",
            "label"=>$RESOURCE_STRING['last_editor']
          );
    else:    

      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"select_users","name"=>"$FLD_UPDATE_ID","insertnull"=>true)),
            "visible"=>$FLD_UPDATE_ID,
            "label"=>$RESOURCE_STRING['last_editor'].":"
          );

      $FORM_CONFIG["schema"][] = array(
            "elements"=>array(
               array("type"=>"select_users","name"=>"$FLD_OWNER_ID","insertnull"=>true)),
            "visible"=>$FLD_OWNER_ID,
            "label"=>$GLOBALS["RESOURCE_STRING"]["owner_form_label"].":"
          );
        
    endif;    
        
    $FORM_CONFIG["schema"][] = array(
      "elements"=>array(
             array("type"=>"date_db","name"=>$FLD_CREATE_DATE."_od"),
             array("type"=>"date_db","name"=>$FLD_CREATE_DATE."_do")),
      "format"=>$FLD_CREATE_DATE."_od...'&nbsp;&nbsp;&nbsp;".$RESOURCE_STRING['until'].":&nbsp;'...".$FLD_CREATE_DATE."_do",
      "visible"=>$FLD_CREATE_DATE?true:false,
      "label"=>"".$RESOURCE_STRING['date']."&nbsp;".$GLOBALS["RESOURCE_STRING"]["owner_user_zalozeni"]." ".$RESOURCE_STRING['from1'].":"
    );

        
    $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
             array("type"=>"date_db","name"=>$FLD_UPDATE_DATE."_od"),
             //array("type"=>"date_db","name"=>$FLD_UPDATE_DATE."_do")
          ),
          "visible"=>$FLD_UPDATE_DATE,    
          //"format"=>$FLD_UPDATE_DATE."_od...'&nbsp;&nbsp;&nbsp;".$RESOURCE_STRING['until'].":&nbsp;'...".$FLD_UPDATE_DATE."_do",
          "label"=>"".$RESOURCE_STRING['date']." ".$RESOURCE_STRING['last']." ".$RESOURCE_STRING['change_i']//." ".$RESOURCE_STRING['from1'].":"
        );

    $FORM_CONFIG["schema"][] = array(
          "elements"=>array(
             array("type"=>"select_main_group","name"=>"$FLD_UPDATE_GROUP_ID","frozen"=>true)),
          "visible"=>$FLD_UPDATE_GROUP_ID?true:false,
          "label"=>$RESOURCE_STRING['group'].":"
        );

  break;
}
