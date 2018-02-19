<?php

$TABLE_CONFIG["schema"][] = array("field"=>"ID", "label"=>"id",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"JEJICH_CJ", "label"=>"Jejich čj./spis",  "width"=>"7%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"NASE_CJ", "label"=>"Naše čj./spis",  "width"=>"8%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"DATUM", "label"=>"Datum",  "width"=>"10%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"FROM", "label"=>"Odesílatel/příjemce",  "width"=>"20%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"VEC", "label"=>"Věc",  "width"=>"25%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"SOUBORY", "label"=>"soubory",  "width"=>"15%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"SCHVALENI", "label"=>"",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"DORUCENI", "label"=>"doručení",  "width"=>"20%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"ODKAZ", "label"=>"",  "width"=>"1%","add"=>"align=left");

if ($GLOBALS["ODCHOZI_DS"])
  $TABLE_TOP_MENU["schema"] = array(
    array("label"=>"Načíst zaškrtnuté",  "url"=>"javascript:RunScript_Tisk('send.php','".$table_params['tablename']."')", "target"=>"_self", "title"=>"Načíst"),
);
else
  $TABLE_TOP_MENU["schema"] = array(
    array("label"=>"Načíst vše",  "url"=>"javascript:RunScript_Tisk('receive.php','".$table_params['tablename']."')", "target"=>"_self", "title"=>"Načíst"),
);

?>
<script>

  function RunScript_Tisk(name_script, tablename){;
    var frm = document.forms['frm_'+tablename];
    frm.method='POST';
//    window.open(name_script,'tisk','height=260,width=470,left=50,top=50,scrollbars,resizable');
    var act = frm.action;
    var tar = frm.target;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='1';
    frm.action = name_script;
//    frm.target = '_top';
    frm.submit();
    frm.action = act;
    frm.target = tar;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='0';
  }
</script>
