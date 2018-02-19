<?php

$TABLE_CONFIG["schema"][] = array("field"=>"ID", "label"=>"id",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"DATUM", "label"=>"Datum",  "width"=>"20%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"FROM", "label"=>"Odesílatel",  "width"=>"30%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"VEC", "label"=>"Věcdf",  "width"=>"50%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"ODKAZ", "label"=>"",  "width"=>"1%","add"=>"align=left","is_html"=>true);

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
