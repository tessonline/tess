<?php
require("tmapy_config.inc");
require_once(FileUp2('.config/config.inc'));
require(FileUp2(".admin/brow_.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2(".admin/el/of_select_.inc"));
require(FileUp2("html_header_full.inc"));

$append_where = "";

function getSelectData($select) {
  $result = array();
  if (is_object($select)) {
    $options = $select->options;
    if (is_array($options)) {
      foreach ($options as $option) {
        if (trim($option["value"])) {
          $result[$option["value"]] = $option["label"];
        }
      }
    }
  }
  return $result;
}
$q = new DB_POSTA;

if($ID) {
  $sql = "SELECT * FROM posta_spisovna_cis_lokace WHERE id = '$ID'";
  $q->query($sql);
  $q->next_record();
  $GLOBALS["SPISOVNA_ID"] = $q->Record["SPISOVNA_ID"];
}
// require_once(FileUp2(".admin/brow_spisovna.php"));

if($SPISOVNA_ID || $GLOBALS["SPISOVNA_ID"]) {
  NewWindow(array("fname"=>"Obecne", "name"=>"Obecne", "header"=>true, "cache"=>false, "window"=>"edit"));
  $append_where = " AND id_parent IS NULL ";
  if($GLOBALS["ID"]) {
    $i = 0;
    $sql = "SELECT id, id_parent FROM posta_spisovna_cis_lokace WHERE id = '" . $GLOBALS["ID"] . "'";
    $q->query($sql);
    while($q->next_record()) {
      if(!$originalId) {
        $originalId = $q->Record["ID"];
      }
      if($q->Record["ID_PARENT"]) {
        $parentIds[] = $q->Record["ID_PARENT"];
        $i++;
        $sql = "SELECT id, id_parent FROM posta_spisovna_cis_lokace WHERE id = '" . $q->Record["ID_PARENT"] . "'";
        $q->query($sql);
      }
    }
    
    if(is_array($parentIds)) {
      $parentIds = array_reverse($parentIds);
    }
    $parentIds[] = $originalId;
    $append_where .= " AND id = ".$parentIds[0];
    $subId = $GLOBALS["ID"];
    unset($GLOBALS["ID"]);
  }
  $selectedSpisovny = getSelectData(new of_select_spisovna(array()));
  foreach ($selectedSpisovny as $key => $spisovna) {
    if($key == $GLOBALS['SPISOVNA_ID']) {
      $spisovnaNazev = $spisovna;
    }
  }
  $count =
    Table(
      array(
        "showaccess" => true,
        "setvars" => true,
        "showself" => true,
        "showdelete" => true,
        "caption" => 'Budovy: '.$spisovnaNazev,
        "appendwhere" => $append_where,
        "unsetvars" =>
          array(
            "except" => array('ID','ID_PARENT','PLNA_CESTA', 'NAZEV', 'SPISOVNA_ID','DALSI_LOKACE')
          )
      )
    );
    $dalsi_lokace = $GLOBALS['DALSI_LOKACE'];
    unset($GLOBALS['DALSI_LOKACE']);
  if($subId) {
    $GLOBALS["ID"] = $subId;
  }
  $cesta = $GLOBALS['PLNA_CESTA'];
  if($count == 1) {
  	$i = 1;
    //while($count == 1) 
    while ($i<=count($parentIds) && $i < 5)
    {
    	$cesta_puv = $GLOBALS['PLNA_CESTA'];
  	  $cesta = $GLOBALS['PLNA_CESTA'];
  	  $nazev = $GLOBALS['NAZEV'];
    	$GLOBALS["ID_PARENT"] = $GLOBALS["ID"];
    	unset($GLOBALS["ID"]);
      if($parentIds[$i]) {
        unset($GLOBALS["ID_PARENT"]);
        $append_where = " AND id = '".$parentIds[$i]."' ";
  	  $id_parent = $parentIds[$i-1];
      }
      else {
        $append_where = " AND id_parent = '".$GLOBALS["ID_PARENT"]."' ";
  	  $id_parent = $GLOBALS["ID_PARENT"];
      }
      unset($GLOBALS['PLNA_CESTA']);
      unset($GLOBALS['NAZEV']);
      $count = 
        Table(
          array(
            "agenda" => "POSTA_SPISOVNA_CIS_LOKACE",
            "caption" => $GLOBALS['RESOURCE_STRING']['lokace_uroven'][$i+1][8].": " . $spisovnaNazev.'/'.$cesta,
            "tablename" => "posta_spisovna_cis_lokace",
            "showaccess" => true,
            "setvars" => true,
            "showself" => $i < 4 ? true : false,
            "showdelete" => true,
            "appendwhere" => $append_where,
            "unsetvars" =>
              array(
                "except" => array('ID','PLNA_CESTA', 'NAZEV','SPISOVNA_ID','DALSI_LOKACE')
              )
          ) 
  
        );
      $dalsi_lokace = $GLOBALS['DALSI_LOKACE'];
      if ($count == 0) $dalsi_lokace = 1;
      unset($GLOBALS['DALSI_LOKACE']);
      $i++;
      }
      $path = GetAgendaPath("POSTA_SPISOVNA_CIS_LOKACE",0,1)."/edit.php?insert&SPISOVNA_ID=".($SPISOVNA_ID ? $SPISOVNA_ID : $GLOBALS["SPISOVNA_ID"])."&ID_PARENT=$id_parent&UROVEN=".$i."&DALSI_LOKACE=1&cacheid=";
      $button_add_subspace = "<input type=\"button\" value=\"Přidat ".$GLOBALS['RESOURCE_STRING']['lokace_novy'][$i].' '
                           . $GLOBALS['RESOURCE_STRING']['lokace_uroven'][$i][4] . ($i < 6 && $dalsi_lokace == 1  && $nazev ? ' do '.$nazev : '')
                           . "\" class=\"button btn\" title=\"Přidat novou lokaci\" onclick=\"NewWindowObecne('".$path."',640,640)\" />&nbsp;&nbsp;&nbsp";
        
      if ($i < 6 && $dalsi_lokace == 1) {
        echo $button_add_subspace;
      }
      if ($i > 1) {
        echo "<a type=\"button\" target=\"_top\" class=\"button btn\" title=\"Zpět na spisovnu\" href=\"./index.php?frame&SPISOVNA_ID=115\">Zpět na spisovnu</a>";
      }
  }
  else {
    if ($dalsi_lokace>0 || $count<1) {
      $path = GetAgendaPath("POSTA_SPISOVNA_CIS_LOKACE",0,1)."/edit.php?insert&SPISOVNA_ID=".($SPISOVNA_ID ? $SPISOVNA_ID : $GLOBALS["SPISOVNA_ID"])."&ID_PARENT=&UROVEN=1&DALSI_LOKACE=1&cacheid=";
      $button_add_subspace = "<input type=\"button\" value=\"Přidat ".$GLOBALS['RESOURCE_STRING']['lokace_novy'][1]." ".$GLOBALS['RESOURCE_STRING']['lokace_uroven'][1][4]."\" class=\"button btn\" title=\"Přidat novou lokaci\" onclick=\"NewWindowObecne('".$path."',640,640)\" />&nbsp;&nbsp;&nbsp";
      echo $button_add_subspace;
    }
  }
}
else {
  
  
  if (HasRole('access_all')) {
    $selectedSpisovny = getSelectData(new of_select_spisovna(array("superodbor"=>"null")));
   
    include_once(FileUp2('.admin/brow_superodbor.inc'));
    if ($GLOBALS['omez_zarizeni']) {
      $selectedSpisovny = getSelectData(new of_select_spisovna(array("superodbor"=>$GLOBALS['omez_zarizeni'])));
    }
  } else {
    $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();

    $selectedSpisovny = getSelectData(new of_select_spisovna(array("superodbor"=>$USER_INFO["PRACOVISTE"])));
  }
  
  $i = 0;
  foreach ($selectedSpisovny as $key => $spisovna) {
    $ARR_SPIS[$i]["SPISOVNA_ID"] = $key;
    $ARR_SPIS[$i]["SPISOVNA"] = $spisovna;
//     $ARR_SPIS[$i]["ID"] = $key;
    $i++;
  }
  
  if (sizeof($selectedSpisovny)==0) {
    $soucast = (HasRole('spisovna')||HasRole('access_all')) ? "pro vybranou součást" : "";
    echo "Žádné lokace ve spisovně nejsou ".$soucast." dostupné.";
    require(FileUp2("html_footer.inc"));
    die();
  }
  include_once $GLOBALS['TMAPY_LIB'] . '/db/db_array.inc';
  $db_arr = new DB_Sql_Array;
  $db_arr->Data = $ARR_SPIS;
  include_once(FileUp2(".admin/properties_spis.inc"));
  
  
  Table(
    array(
      'db_connector' => &$db_arr,
      'properties' => $PROPERTIES_SPIS,
      'caption' => 'Spisovny',
      'showaccess' => true, 
      'schema_file' => '.admin/table_schema_spis.inc',
      'select_id' => 'SPISOVNA_ID',
      'page_size' => 100,
      'showself' => true,
      'showedit' => false, 
      'showdelete' => false, 
      'showselect' => false,
       'multipleselect' => false, 
       'showinfo' => false, 
       'multipleselectsupport' => false, 
       'showinfo' => false
     )
  );
  $GLOBALS["PROPERTIES"]["AGENDA_ID"] = "ID";
}
  
require(FileUp2("html_footer.inc"));