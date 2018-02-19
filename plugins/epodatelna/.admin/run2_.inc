<?php


include_once(FileUp2(".admin/agenda_func.inc"));
include_once(Fileup2(".admin/nocache.inc"));
//include_once(Fileup2(".admin/properties.inc"));
// lumo 27.1.2009
$PROPERTIES = loadProperties();
$RESOURCE_STRING = $GLOBALS['RESOURCE_STRING'];

// je v loadProperties 
// lumo 25.3.2009
//if (!$GLOBALS["client_lang"]) $GLOBALS["client_lang"] = $PROPERTIES["DEFAULT_LANG"]?$PROPERTIES["DEFAULT_LANG"]:"cz_win";
//@include(FileUp2(".admin/lg/".$GLOBALS["client_lang"].".inc"));
//@include(FileUp2(".admin/lg/app_".$GLOBALS["client_lang"].".inc"));
//$GLOBALS["RESOURCE_STRING"] = $RESOURCE_STRING;

include_once(Fileup2(".admin/db/db_default.inc"));
include_once(Fileup2(".admin/access_.inc"));
include_once(Fileup2(".admin/functions.inc"));
include_once(Fileup2(".config/settings/agenda_path.inc"));

function Run_($run_params=false) {
  //Proměnná $form_params je pole obsahující následující klíče
  /*
  agenda                                    identifikace agendy
  runsql                                    prime vlozeni dotazu
  noaccessrefresh                           bez znovunacteni pristupovych prav
  noaccesscondition        bool, false      preskoceni AccessCondition
  outputtype                                typ vystupu funkce
                         1                  bez vystupu
                         2 (default)        default - podle typu akce
                         3                  bez vystupu se zavrenim
                         4                  neprovede SQL jenom ho vrati jako string a nezavre se
                         5                  zavre se bez vystupu, ale po INSERTU skoci primo na vlozeny zaznam
                         nazev souboru      owner - vlastni typ (.admin/run_output.inc)
  returntype             2                  vrati pouze vlastni SQL string                         
  no_unsetvars             bool, false      nesmaze po sobe globalni promenne
  to_history               bool, false      vlozit puvodni zaznam do historie
  history_table                             jmeno tabulky pro historii 
  db_connector                              objekt db konektoru, nebude se zakladat novy, pouzije tento (predavano referenci - objekt pak obsahuje pripadnou chybu)
  */

  if ($run_params==false):
    $run_params = array();
  endif;
  
  if (!$run_params["outputtype"]):
    $run_params["outputtype"] = 2;
  endif;  
   
  if (isset($run_params["agenda"])):
    include_once(FileUp2(".admin/agenda_func.inc"));
    ChDir(GetAgendaPath($run_params["agenda"], false));
    //include(Fileup2(".admin/properties.inc"));
    // lumo 27.1.2009
    $PROPERTIES = loadProperties();
    $GLOBALS["PROPERTIES"]=$PROPERTIES;
  endif;  

  //SetFields values 
  $FLD_OWNER_ID = $GLOBALS["PROPERTIES"]["FIELD_OWNER_ID"]?$GLOBALS["PROPERTIES"]["FIELD_OWNER_ID"]:"OWNER_ID";
  $FLD_UPDATE_DATE = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_DATE"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_DATE"]:"LAST_DATE";
  $FLD_UPDATE_TIME = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_TIME"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_TIME"]:"LAST_TIME";
  $FLD_UPDATE_ID = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_ID"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_ID"]:"LAST_USER_ID";
  $FLD_UPDATE_GROUP_ID = $GLOBALS["PROPERTIES"]["FIELD_UPDATE_GROUP_ID"]?$GLOBALS["PROPERTIES"]["FIELD_UPDATE_GROUP_ID"]:"LAST_GROUP_ID";
   
  //Konverze pro datum
  $db = $GLOBALS["PROPERTIES"]["DB_NAME"]?$GLOBALS["PROPERTIES"]["DB_NAME"]:"DB_DEFAULT";
  // nastaveni databazoveho konektoru - lumo 17.12.2007
  if ($run_params["db_connector"]) {
    $q = &$run_params["db_connector"];
  }
  else {
    $q = new $db;
  }
  $met = $q->metadata($GLOBALS["PROPERTIES"]["AGENDA_TABLE"]);
  reset($met);
  while (list($key, $val) = each($met)):
    switch (strtolower($val["type"])):
      case "date":
      case "datetime":
      case "datetime2":
      case "smalldatetime":
  //		  eval("global $".$val["name"]);
  			if (isset($GLOBALS[$val["name"]])):
    			$GLOBALS[$val["name"]] = $q->str2dbdate($GLOBALS[$val["name"]]);
  			endif;
    endswitch;
  	if (!$owner){ $owner = ($val["name"] == $FLD_OWNER_ID);} 
  	if (!$date){ $date = ($val["name"] == $FLD_UPDATE_DATE);} 
  	if (!$time){ $time = ($val["name"] == $FLD_UPDATE_TIME);} 
  	if (!$id){ $id = ($val["name"] == $FLD_UPDATE_ID);} 
  	if (!$group_id){ $group_id = ($val["name"] == $FLD_UPDATE_GROUP_ID);} 
  endwhile;
  
  include_once(FileUp2(".admin/security_obj.inc"));  
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
  if ($date):
    $GLOBALS[$FLD_UPDATE_DATE] = $q->date2dbdate();
  endif;
  if ($time):
    $GLOBALS[$FLD_UPDATE_TIME] = $q->time2dbtime();
  endif;
  if ($id): 
    $GLOBALS[$FLD_UPDATE_ID] = $USER_INFO["ID"];
  endif;
  if ($group_id): 
    $GLOBALS[$FLD_UPDATE_GROUP_ID] = $USER_INFO["GROUP_ID"];
  endif;
  
  //Bezpecnost
  $acc = $run_params["noaccessrefresh"] || Access();
  //tohu - dodelano pro uredni desku praha4
	if ($GLOBALS["PROPERTIES_ACCESS"][all_tester]) die("Toto je pouze <b>TESTOVACI</b> rezim !!!");

  $run_type = 0;
  $agenda_id_type_string = false;
  for ($i=0;$i<count($met);$i++){
    if ($met[$i]["name"]==$GLOBALS["PROPERTIES"]["AGENDA_ID"]){
      $agenda_id_type_string = QuotedType ($met[$i]["type"], $met[$i]["flags"]);
      break; 
    }
  }	  

  if ($acc && !$run_params["runsql"]):  
    //Sestava dotazu
    if ($GLOBALS["DELETE_ID"]):
      if(is_array($GLOBALS["DELETE_ID"])) $delete_id = $GLOBALS["DELETE_ID"];
      else $delete_id = array($GLOBALS["DELETE_ID"]); 
      $run_type = 1;
      $set = "";
      if ($GLOBALS["PROPERTIES"]["SET_LAST_BEFORE_DELETE"]) {
        $set = "UPDATE ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." SET ";
        $set .= CreateSetWhereSQLFromVar(&$met, false, null, $run_params['directsqlvalues']);
        if (!$agenda_id_type_string)
          $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN (".implode(",",$delete_id).")";
        else
          $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN ('".implode("','",$delete_id)."')";
        $set .= ";\n";
      }
      //SetType($DELETE_ID,"integer");
      $set .= "DELETE FROM ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"];
      if (!$agenda_id_type_string)
        $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN (".implode(",",$delete_id).")";
      else
        $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN ('".implode("','",$delete_id)."')";
      foreach($delete_id as $did){
        $acc = HasAccessToRecord("delete", $did);
        if(!$acc) break;
      }  
    //Edit  
    elseif (isset($GLOBALS["EDIT_ID"])&&($GLOBALS["EDIT_ID"])):
      if(is_array($GLOBALS["EDIT_ID"])) $edit_id = $GLOBALS["EDIT_ID"];
      else $edit_id = array($GLOBALS["EDIT_ID"]); 
      $run_type = 2;
      //SetType($GLOBALS["EDIT_ID"],"integer");
      $set = "UPDATE ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." SET ";
      $set .= CreateSetWhereSQLFromVar(&$met, false, &$q, $run_params['directsqlvalues']);
      if (!$agenda_id_type_string)
        $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN (".implode(",",$edit_id).")";
      else
        $set .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN ('".implode("','",$edit_id)."')";
      foreach($edit_id as $uid){
        //$acc = HasAccessToRecord("update", $uid);
      }  
    else:
      $run_type = 3;
      if ($owner):
        if (empty($GLOBALS["OWNER_ID"])) $GLOBALS["OWNER_ID"] = $USER_INFO["ID"];
      endif;
      $set = "INSERT INTO ".$GLOBALS["PROPERTIES"]["AGENDA_TABLE"]." ";
      $set .= CreateValuesSQLFromVar($met, $run_params['directsqlvalues']);
      $insert = true;
      $name = "insert";
      if (!HasRole("all_$name")):
        if (HasRole("group_$name")):
          $group = $USER_INFO["GROUP"];
          $groupset = $GLOBALS["PROPERTIES"]["AGENDA_GROUP_ID"];
          if ((!empty($groupset))&&(!preg_match("/" . StrToUpper($group).".*" . "/", StrToUpper($groupset)))):
            $access = false;
          endif;
        else:
          $group = $USER_INFO["SUBGROUP"];
          $groupset = $GLOBALS["PROPERTIES"]["AGENDA_GROUP_ID"];
          if ((!empty($groupset))&&(!preg_match("/" . StrToUpper($group).".*" . "/", StrToUpper($groupset)))):
            $access = false;
          endif;
        endif;
      endif;
    endif;
  else:
    $set = $run_params["runsql"];
    if (preg_match("/^insert.*/i",$set)) $insert=true;
  endif;

  //Bezpecnost
  if (!$acc):
    if ($run_params["outputtype"]>0):  
      echo "</head>\n";
      echo "<body>\n";
      include_once(FileUp2("html_error.inc"));
      include_once($GLOBALS["TMAPY_LIB"]."/oohformsex.inc");
      $f = new formex;
      $f->ae(array( type=>"button_close", name=>"__"));
      $f->start("","","","","");
      $f->se("__");
      $f->finish();
    endif;
    exit;
  endif;
  
  //vybrat puvodni hodnoty pro historii
  if($run_params["to_history"] && ($GLOBALS['EDIT_ID'] || $GLOBALS['DELETE_ID'])):
    if (isset($PROPERTIES["BROW_SELECT"]) && $PROPERTIES["BROW_SELECT"]) 
      $sql = $PROPERTIES["BROW_SELECT"];
    else
      $sql = 'SELECT * FROM '.$GLOBALS['PROPERTIES']['AGENDA_TABLE'];
    if ($GLOBALS["DELETE_ID"]):
      if(is_array($GLOBALS["DELETE_ID"])) $delete_id = $GLOBALS["DELETE_ID"];
      else $delete_id = array($GLOBALS["DELETE_ID"]);
      if (!$agenda_id_type_string)
        $sql .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN (".implode(",",$delete_id).")";
      else
        $sql .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN ('".implode("','",$delete_id)."')";
    elseif (isset($GLOBALS["EDIT_ID"])&&($GLOBALS["EDIT_ID"])):
      if(is_array($GLOBALS["EDIT_ID"])) $edit_id = $GLOBALS["EDIT_ID"];
      else $edit_id = array($GLOBALS["EDIT_ID"]);
      if (!$agenda_id_type_string)
        $sql .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN (".implode(",",$edit_id).")";
      else
        $sql .= " where ".$GLOBALS["PROPERTIES"]["AGENDA_ID"]." IN ('".implode("','",$edit_id)."')";
    endif;
       
    $q->query($sql);
    while($q->next_record()) $records_old[$q->Record[$GLOBALS["PROPERTIES"]["AGENDA_ID"]]] = $q->Record; 
  endif;

  //echo $set;
// die($set);
//  return 18;
  
  $result = false; 
  
  if ($run_params["returntype"] == 2) return $set;

  $queryOK = $q->query($set);
   
//  if (($queryOK) && ($q->affected_rows() >= 0)):
  if ($queryOK):
//  if (true):
    
    //vlozit puvodni hodnoty do historie
    if($run_params["to_history"] && $records_old && !$insert):
      foreach ($GLOBALS as $globalsKey => $globalsValue) $globalsOld[$globalsKey] = $GLOBALS[$globalsKey]; // zapamatujeme si nynejsi - CreateValuesSQLFromVar je prepise
      $table_h = $run_params["history_table"]?$run_params["history_table"]:$GLOBALS["PROPERTIES"]["AGENDA_TABLE"].'_h';
      $meth = $q->metadata($table_h);
      foreach($records_old as $id => $record_old) { 
        foreach($record_old as $key => $val) $GLOBALS[$key]=$val;
        $seth = "INSERT INTO $table_h ";
        $seth .= CreateValuesSQLFromVar($meth);
        $q->query($seth);
      }
      foreach ($globalsOld as $globalsKey => $globalsValue) { // vratime zpatky
        $GLOBALS[$globalsKey] = $globalsOld[$globalsKey];
        $$globalsKey = $globalsOld[$globalsKey];
      }
    endif;

    $result = -1;

    //Inserted ID 
    if ($insert) {
      $lastid = $q->getlastid($GLOBALS["PROPERTIES"]["AGENDA_TABLE"], $GLOBALS["PROPERTIES"]["AGENDA_ID"]);   
      if ($lastid):    
        if ($GLOBALS["PROPERTIES"]["AGENDA_ID"]):
          if(!$run_params["no_unsetvars"]) unsetvars();
          $GLOBALS[$GLOBALS["PROPERTIES"]["AGENDA_ID"]] = $lastid;
          $result = $lastid;
        endif;
      endif;
    //result EDIT_ID
    } else if ($run_type == 2) {
      $result = $GLOBALS["EDIT_ID"];
    }
    //result DELETE_ID
    else {
      $result = $GLOBALS["DELETE_ID"];
    }

    if ($run_params["tran_commit"]){ 
       if ($q->Query_ID) $q->Tran_Commit();
       else $q->Tran_Rollback();
    }

    // Init Spinbox update layer
    $sbx = null;
    if (isset($GLOBALS["PROPERTIES"]['TMS_SPINBOX_PARAMS']) && isset($GLOBALS["PROPERTIES"]['TMS_SPINBOX_PARAMS']['updateLayer'])) {
    	require_once 'tw_maplinkspinbox.inc'; 
    	$sbx = new TW_MapLinkSpinbox($GLOBALS["PROPERTIES"]['TMS_SPINBOX_PARAMS']);
    }

    //Default output type
    if ($run_params["outputtype"] == 2):
    
      //Spinbox update layer
	    if (is_object($sbx)) {
	    	$sbx->writeUpdateJS(true);
	    }
	    
      //Insert
      if ($insert):
         
        include_once($GLOBALS["TMAPY_LIB"]."/oohformsex.inc");
        include_once(FileUp2(".admin/brow_.inc"));
        
        $str = " - ".$GLOBALS["RESOURCE_STRING"]["menu_insert"];
        echo "<title>".$GLOBALS["PROPERTIES"]["AGENDA_NAME"]."$str</title>\n";
        echo "<script type=\"text/javascript\">\n";
        echo "function Close() {\n";
        if (($GLOBALS["PROPERTIES"]["INSERT_REFRESH"])&&(!$GLOBALS["NO_REFRESH"])):
          echo "  if (window.opener.parent.frames[1]!=null) {\n";
//          echo "    window.opener.parent.frames[1].location.reload();\n";
          echo "    window.opener.parent.frames[1].history.go(0);\n";
          echo "  }\n";
        endif;
        echo "  window.close();\n";
        echo "}\n";
        echo "</script>\n";
        echo "</head>\n";
        echo "<body>\n";
        echo "<span class=\"caption\">".$GLOBALS["PROPERTIES"]["AGENDA_NAME"]."$str</span>\n";
        echo "<h3>".$GLOBALS["RESOURCE_STRING"]["record_saved"].":</h3>\n";

        Table(array("nocaption"=>true, "nopaging"=>true, "showedit"=>false, "showdelete"=>false, "noprint"=>true, "noaccesscondition"=>$run_params["noaccesscondition"], "script_extension"=>$run_params["script_extension"], "image_dir"=>$run_params["image_dir"], "noshowrelation"=>true, "noshowinsert2clip"=>true, "noshowrelationbreak"=>true));

        if (!$run_params["NoCloseButton"]):
          $f = new formex;
          $f->ae(array( type=>"button", name=>"__", value=>$GLOBALS["RESOURCE_STRING"]["button_close"], onclick=>"Close();"));
          $f->start("frm_delete","GET","","","");
          echo "<table width='100%'>";
          echo "<tr><td align='left'>\n";
          $f->se("__");
          echo "</table>\n";
          $f->finish();
        endif;
        
      //Update a Delete  
      else:

        echo "<script type=\"text/javascript\">\n";
        echo "function Open() {\n";
        echo "  if (window.opener!=null) {\n";
        echo "    window.opener.history.go(0);\n";
        echo "    //window.close();\n";
        echo "  }else{\n";
        echo "    window.history.go(-1);\n";
        echo "    window.history.go(0);\n";
        echo "  }\n";
        echo "}\n";
        echo "</script>\n";
        echo "<title>".$GLOBALS["PROPERTIES"]["AGENDA_NAME"]."</title>\n";
        echo "</head>";
        echo "<body onload=\"Open()\">\n";
        echo '<span class="caption">'.$GLOBALS["PROPERTIES"]["AGENDA_NAME"]."</span>\n";
        echo "<h3>".$GLOBALS["RESOURCE_STRING"]["record_edited"]."</h3>\n";
      endif;
      
    elseif ($run_params["outputtype"] == 1):
    
      usleep(0);
      
    elseif ($run_params["outputtype"] == 3 || $run_params["outputtype"] == 5):
    
      //Spinbox update layer
      if (is_object($sbx)) {
        $sbx->writeUpdateJS(true);
      }
      
      echo "<script type=\"text/javascript\">\n";
      if (($GLOBALS["PROPERTIES"]["INSERT_REFRESH"])&&(!$GLOBALS["NO_REFRESH"])):
        echo "  if (window.opener!=null && window.opener.parent.frames[1]!=null &&
                    window.opener.parent.frames[1].name == 'main') {\n";
        if ($run_params["outputtype"] == 5 && $insert) {
          echo "    window.opener.parent.frames[1].location.href = 'brow.php?".$GLOBALS["PROPERTIES"]["AGENDA_ID"].'='.$GLOBALS[$GLOBALS["PROPERTIES"]["AGENDA_ID"]]."';\n";
        } else {
          echo "    window.opener.parent.frames[1].location.reload();\n";          
        }
        echo "  }else if (window.opener!=null) {\n";
        if ($run_params["outputtype"] == 5 && $insert) {
          echo "    window.opener.location.href = 'brow.php?".$GLOBALS["PROPERTIES"]["AGENDA_ID"].'='.$GLOBALS[$GLOBALS["PROPERTIES"]["AGENDA_ID"]]."';\n";
        } else {
          echo "    window.opener.location.reload();\n";          
        }
        echo "  }else if (window.parent!=null) {\n";
        if ($run_params["outputtype"] == 5 && $insert) {
          echo "    window.parent.location.href = 'brow.php?".$GLOBALS["PROPERTIES"]["AGENDA_ID"].'='.$GLOBALS[$GLOBALS["PROPERTIES"]["AGENDA_ID"]]."';\n";
        } else {
          echo "    window.parent.location.reload();\n";          
        }
        echo "  }\n";
      endif;
      echo " window.close();\n";
      echo "</script>\n";

    else:
      include_once(FileUp2($run_params["outputtype"]));
    endif;
    
  else:

    if ($run_params["outputtype"]>0):  
      echo "</head>\n";
      echo "<body>\n";
      if (!$q->Errno):
        include_once(Fileup2("html_error.inc"));
        echo "<br><br><b>".$GLOBALS["RESOURCE_STRING"]["error"].":</b> ".$GLOBALS["RESOURCE_STRING"]["record_error"]."\n";
      else:
        $SHOW_BUTTON_BACK = true;
        include_once(FileUp2("html_db_error.inc"));
      endif;
    endif;
    
  endif;
  
  return $result;
}


?>
