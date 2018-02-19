<?php
if ($GLOBALS['RECORD_ID'] && $GLOBALS['AGENDA_IDENT'] == 'POSTA') {
	EedTools::MaPristupKDokumentu($GLOBALS['RECORD_ID'], 'editace');
}

if ($GLOBALS['PRIVATE'] == 'y') {
  include_once(FileUp2('.admin/upload/table_func_posta.inc'));
  $muze_duverne = false;
  $muze_duverne = MuzeDuverne($GLOBALS['RECORD_ID'], $GLOBALS['OWNER_ID']);
  if (!$muze_duverne) Die('<br/><br/><h3>Nemáte právo pro editaci tohoto záznamu.</h3>');
}


?>
<script language="JavaScript" type="text/javascript">
<!--
  function DelWin(script){
    newwindow = window.open(script, 'DelHistFile','height=300,width=400,left=100,top=50,scrollbars,resizable');
    newwindow.focus();
  }
  function RunAfterValidForm(){
    document.forms[0].style.display = 'none';
    document.getElementById('upl_wait_message').style.display = 'block';
  }
//-->
</script>
<div id="upl_wait_message" class="text" style="display:none">
  <br><?php echo $GLOBALS['RESOURCE_STRING']['upload_loading_wait']?>
  <br><img src="<?php echo FileUpUrl('images/progress.gif')?>" title="<?php echo $GLOBALS['RESOURCE_STRING']['upload_loading']?>" alt="<?php echo $GLOBALS['RESOURCE_STRING']['upload_loading']?>">
</div>
<?php
//echo $form_params["formtype"]."--".$f_insert;
//if ($form_params["formtype"] == $f_info || $form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_filterall || $form_params["formtype"] == $f_insert)             
//$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();

//$GLOBALS["RECORD_ID"] = 83155;

//$FORM_CONFIG["schema"][] = "&nbsp;";

include_once($GLOBALS["TMAPY_LIB"]."/of_security.inc");

class of_select_yes_no_upload extends of_select {
  // Constructor
  function of_select_yes_no_upload($a) {
    $this->setup_element($a);
		if($a['insertnull']) {
      $this->options[] = array("value" => "", "label" => "");
    }
		$this->options[] = array(
      "value" => "n", 
      "label" => $GLOBALS['RESOURCE_STRING']['no']
    );
    $this->options[] = array(
      "value" => "y", 
      "label" => strtoupper($GLOBALS['RESOURCE_STRING']['yes'])
    );
  }
}

class of_text_uploadfile extends of_text {

  function self_get_frozen($val,$which, &$count) {
    global $q;
    
    if (!$GLOBALS['upload_modul_to_url']) {
       $upload_modul_first_key = array_pop(array_keys($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']));
       $GLOBALS['upload_modul_to_url'] = ($upload_modul_first_key ? $upload_modul_first_key : 'table');

    }
  //print_r($this);echo"<br><br>";
  //echo $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]."--".$this->value."<br>";
    $str = "&nbsp;";
    $v = $this->value;
    $n = $this->name . ($this->multiple ? "[]" : "");
    if ($GLOBALS["HISTORY_TABLE_IDENT_COLUM"] == 'OLD' && $this->values['id']) $file_id = $this->values['id']; 
    if ($GLOBALS["HISTORY_TABLE_IDENT_COLUM"] == 'NEW' && $this->values['id_new']) $file_id = $this->values['id_new'];
    if ($v){
      if ($file_id) {
        if ($GLOBALS['modul_obj']->IsFileExistsByID($file_id, true)) {
          //$v = end(explode('_',$v,3)); 
          $str = "<a href=\"ug_file.php?FILE_ID_H=$file_id&upload_modul=".$GLOBALS['upload_modul_to_url']."\" class=\"pages\" target=\"_blank\"><b>$v</b></a>";
          $str.= '&nbsp;<a href="javascript:DelWin(\'ug_file.php?show_typ=3&upload_modul='.$GLOBALS['upload_modul_to_url'].'&DELETE_ID_H='.$file_id.'\')" title="'.$GLOBALS['RESOURCE_STRING']['upload_delete'].'">';
          $str.= '<img src="'.FileUp_Main('images/delete_small.gif',$GLOBALS['PROPERTIES']['AGENDA_IDENT']).'" border="0" alt="delete" /></a>'; 

         ShowJSfce_URLFile2Clip();
         $str .= '&nbsp;<a href=# onclick="URLFile2Clip(event,'.$file_id.',true)"><img src="'.FileUpURL('images/clip_copy_small.gif').'" alt="'.$GLOBALS["RESOURCE_STRING"]["tooltip_clip_copy"].'" border="0"></a>';

        }
        else {
          $str = $v;
        }  
      }
      else {
        $str .= "<input type=\"hidden\" name=\"$n\" value=\"$v\" /><b>$v</b>";
      }
    }  
    $count = 1;
    return $str;
  }
}

if ($form_params["formtype"] == $f_info) {
  $GLOBALS['JIDFILES'] = $GLOBALS['CONFIG']['ID_PREFIX']. 'F' . $GLOBALS['ID'];

  $upl = Upload(array(
            'create_only_objects' => true,
            'agenda' => 'POSTA',
            'noshowheader'=>true)
          );

  $razitko = $upl['table']->stg_obj->getMetaData($GLOBALS['DIRECTORY']);




}
$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "text",
      "name" => "JIDFILES",
      "size" => 70,
    )
  ),
  "visible" => $form_params["formtype"] == $f_info,
  "label" => "JID souboru:"
);

$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "valid_fce",
      "name_fce" => 'return RunAfterValidForm();'
    )
  ),
  "visible" => $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_edit
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array(
      "type" => "hidden", 
      "name" => "RECORD_ID",
      "value" => $GLOBALS["RECORD_ID"]
    ),
    array(
      "type" => "hidden", 
      "name" => "AGENDA_IDENT",
      "value" => $GLOBALS['PROPERTIES']["AGENDA_IDENT"]
    )
  ),
  "visible" => $form_params["formtype"] == $f_insert
);


$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text_uploadfile", 
      "name" => "NAME",
      "size" => 50, 
      "frozen" => $form_params["formtype"] == $f_edit
    )
  ),
  "visible" => $form_params["formtype"] != $f_insert,
  "label" => $GLOBALS['RESOURCE_STRING']['file_name'].":"
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text", 
      "name" => "RENAME",
      "size" => 50
    )
  ),
  "visible" => $form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert ,
  "label" => $GLOBALS['RESOURCE_STRING']['rename'].":"
);
              
$max_upload = $GLOBALS['modul_obj']->GetMaxFileSizeUpload();
$max_file_size = number_format(round($max_upload/1024), 0, '', ' ')." kB";

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "file", 
      "name" => "UPLOAD_FILE[]", 
      "size" => 0, 
      "required" => false, 
      "add" => "class='button btn'",
      "extrahtml" => 'multiple="multiple"',
    )
  ),
  "visible" => $form_params["formtype"] == $f_insert,
  "format" => "UPLOAD_FILE[]...'<i>(".$GLOBALS['RESOURCE_STRING']['max_size']." $max_file_size)</i>'",
  "label" => $GLOBALS['RESOURCE_STRING']['file'].":"
            
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "file", 
      "name" => "UPLOAD_FILE", 
      "size" => 0, 
      "required" => false, 
      "add" => "class='button btn'",
    )
  ),
  "visible" => $form_params["formtype"] == $f_edit,
  "format" => "UPLOAD_FILE...'<i>(".$GLOBALS['RESOURCE_STRING']['max_size']." $max_file_size)</i>'",
  "label" => $GLOBALS['RESOURCE_STRING']['new_version'].":"
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "textarea", 
      "name" => "DESCRIPTION", 
      "rows" => 4, 
      "cols" => 50
    )
  ),
  "visible" => true,
  "label" => $GLOBALS['RESOURCE_STRING']['notice'].":"
);

  $FORM_CONFIG["schema"][] = array(
    "elements" => array(
      array(
        "type" => "select_dostupnost_souboru",
        "name" => "PRIVATE",
        "duverne" => $GLOBALS['MUZE_DUVERNE'],
      )
    ),
    "visible" => true,
    "label" => "Dostupnost souboru:"
  );

/*
  $FORM_CONFIG["schema"][] = array(
    "elements" => array(
      array(
        "type" => "checkbox",
        "name" => "CONVERT",
//        "value" => "1",
      )
    ),
    "visible" => !$GLOBALS[EDIT_ID],
    "label" => "Konvert do PDF:"
  );
*/

/*
$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "select_agendy", "name" => "AGENDA_IDENT", "value" => $GLOBALS["AGENDA_IDENT"], "insertnull" => true, "required" => $form_params["formtype"] == $f_insert, "frozen" => ($GLOBALS["AGENDA_IDENT"]?true:false))),
                   "visible" => $form_params["formtype"] != $f_edit,
                   "label" => "Agenda:"
                   );

$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "text", "name" => "RECORD_ID")),
                   "visible" => $form_params["formtype"] == $f_info,
                   "label" => "ID z�znamu:"
                   );
*/
$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text", 
      "name" => "DIRECTORY",
      "size" => 70,
    )
  ),
  "visible" => $form_params["formtype"] == $f_info,
  "label" => "Identifikátor v úložišti:"
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text", 
      "name" => "FILESIZE_kB", 
      "value" => number_format(round($GLOBALS["FILESIZE"]/1024), 0, '', ' ')." kB"
    )
  ),
  "visible" => $form_params["formtype"] == $f_info,
  "label" => $GLOBALS['RESOURCE_STRING']['size'].":"
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text", 
      "name" => "TYPEFILE",
      "size" => 70,
    )
  ),
  "visible" => $form_params["formtype"] == $f_info,
  "label" => "Typ:"
);

$FORM_CONFIG["schema"][] = array( 
  "elements" => array(
    array( 
      "type" => "text", 
      "name" => "COUNTER"
    ),
    array( 
      "type" => "date_db", 
      "name" => "LAST_DATE_SHOW"
    )
  ),
  "visible" => $form_params["formtype"] == $f_info,
  "format" => "COUNTER...'&nbsp;&nbsp;&nbsp;".$GLOBALS['RESOURCE_STRING']['last_display'].":&nbsp;'...LAST_DATE_SHOW",
  "label" => $GLOBALS['RESOURCE_STRING']['access_count'].":"
);

/*                   
$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array("type" => "date_db", "name" => "LAST_DATE", "value" => date("Y-m-d"), "frozen" => true)),
                   "visible" => $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info,
                   "label" => "Datum nahr�n�:"
                   );

$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "date_db", "name" => "LAST_DATE_od"),
                   array( "type" => "date_db", "name" => "LAST_DATE_do")),
                   "format" => "LAST_DATE_od...'&nbsp;&nbsp;Do:&nbsp;'...LAST_DATE_do",
                   "visible" => $form_params["formtype"] == $f_filter,
                   "label" => "Datum nahr�n� Od:"
                   );
                   
$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "select_users", "name" => "OWNER_ID", "insertnull" => true, "value" => $USER_INFO["CODE"], "frozen" => true)),
                   //"visible" => $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info,
                   "label" => "Nahr�l:"
                   );

$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "select_group", "name" => "OWNER_ID","group" => array("upload_admin","upload_user"),"group_id" => "ID","insertnull" => true)),
                   "visible" => $form_params["formtype"] == $f_filter,
                   "label" => "Nahr�l:"
                   );

$FORM_CONFIG["schema"][] = array( "elements" => array(
                   array( "type" => "checkbox", "name" => "PRIVATE", "add" => ((($form_params["formtype"]!=$f_edit) || ($USER_INFO["ID"]==$GLOBALS["OWNER_ID"]))?"":"disabled"))),
                   "visible" => true,
                   "label" => "D�v�rn�:"
                   );
*/          

if ($form_params["formtype"] == $f_info) {
  $FORM_CONFIG["schema"][] = array("label" => 'Časové razítko');
  if ($razitko['cul:PKILog.Razitko.overeniVysledek']<>'') {
      $FORM_CONFIG["schema"][] = array( "elements" => array(
                         array("type" => "text", "name" => 'CAS1', "value" => $razitko['cul:PKILog.Razitko.serioveCislo'], "frozen" => true,"label" => 'Sériové číslo'),
                         array("type" => "text", "name" => 'CAS2', "value" => $razitko['cul:PKILog.Razitko.vystavil'], "frozen" => true, 'label' =>'Vystavil'),
                         )
                         );
                         
      $FORM_CONFIG["schema"][] = array( "elements" => array(
                         array("type" => "textarea", "name" => 'CAS3', "value" => $razitko['cul:PKILog.Razitko.overeniVysledek'], 'rows' =>5, 'cols'=>60, "frozen" => true)),
                         "label" => 'Platnost'
                         );
  }
  if (HasRole('spravce') && is_array($razitko)) {
    print_r($razitko);
  }
}


///proto, aby se nacetla spravna metadata          
$PROPERTIES["AGENDA_TABLE"] = $GLOBALS['upl_table'];

unset($arr);
//include(FileUp2(".admin/el/owner_user_date_form_add.inc"));

// z duvodu, aby se v tagu form pridalo enctype="multipart/form-data" viz. ooohforms.inc
$f->isfile = true;
