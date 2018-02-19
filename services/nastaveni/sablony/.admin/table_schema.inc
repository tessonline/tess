<?php
include_once(FileUp2(".admin/table_func_upload.inc"));



$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název šablony", "width"=>"35%");
$TABLE_CONFIG["schema"][] =  array( "field"=>"UkazOdbor(ODBOR)", "label"=>"Spisový uzel", "width"=>"25%");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ukazTypPosty(TYP_POSTY)", "label"=>"Druh dokumentu", "width"=>"25%");

If ($GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
{
  $TABLE_CONFIG["schema"][] = array("field"=>"UkazOdkazNaSablonu(ID_DOKUMENTU,'odpoved_test',ID)", "label"=>"TEST",  "width"=>"10%","add"=>"align=center");
//If ($GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
  $TABLE_CONFIG["schema"][] = array("field"=>"UkazOdkazNaSablonu(ID,'sablona')", "label"=>"ŠABLONA",  "width"=>"15%","add"=>"align=center");
}
else
{
  $TABLE_CONFIG["schema"][] = array("field"=>"UkazOdkazNaSablonu(ID_DOKUMENTU,'odpoved',ID)", "label"=>"TEST",  "width"=>"10%","add"=>"align=center");
//  $TABLE_CONFIG["schema"][] = array( field=>"upload_files(ID)", "label"=>"&nbsp;", "class"=>"image", "width"=>"1px");
}  

$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);

//NewWindow(array("fname" => "Sort", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));
NewWindow(array("fname" => "Sort", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
  //'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '\');',
  'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '&sql=' . $GLOBALS['TABLE_SELECT'].'\');',
  'target' => '_self',
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'dropdown' => false,
        'button' => true
      )
    )
  )
);

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Načíst znovu',
  'url' => 'javascript:location.reload();',
  'target' => '_self',
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'dropdown' => false,
        'button' => true
      )
    )
  )
);
echo "
  <script>
  <!--
    
  function sortCloseCallback() {
    window.location.reload();
  }
    
 //-->
</script>
";

  ?>
<iframe id="ifrm_get_value" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden" src="blank.php"></iframe>
