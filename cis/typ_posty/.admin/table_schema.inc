<?php

$TABLE_CONFIG['callback'] = 'changeCellClassTP';
$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Druh dokumentu");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ukazOdbory(ID)", "label"=>"Spisový uzel");
//$TABLE_CONFIG["schema"][] =  array( "field"=>"ZKRATKA", "label"=>"Spisový uzel");
$TABLE_CONFIG["schema"][] =  array( "field"=>"ShowSkartace(SKARTACE_ID)", "label"=>"Spisový znak");

$TABLE_CONFIG['syscolumns'] = array(
   'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);

NewWindow(array("fname" => "Sort", "name" => "Sort", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
  'url' => 'javascript:NewWindowSort(\'./../typ_posty/sort.php?id=' . $t->name . '&SELECTOR=ID_AGENDY&SELECTOR_ID='.$_GET['ID'].'\');',
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


