<?php

$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Název");
//$TABLE_CONFIG["schema"][] =  array( "field"=>"ZKRATKA", "label"=>"Odbor");

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);

NewWindow(array("fname" => "Sort", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
  'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '\');',
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


$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
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