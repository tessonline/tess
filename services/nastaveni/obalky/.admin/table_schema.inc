<?php
$TABLE_CONFIG["schema"][] = array("field"=>"PORADI", "label"=>"Pořadí", add=>"NOWRAP", width=>"1%");
$TABLE_CONFIG["schema"][] = array("field"=>"NAZEV", "label"=>"Název");
$TABLE_CONFIG["schema"][] = array("field"=>"Ukaz(ID)", "label"=>" ");

$TABLE_CONFIG['schema'][] = array(
  'field' => 'copyEnvelope(ID)',
  'class' => 'image',
  'label' => '&nbsp;',
  'width' => '1px',
  'add' => 'align="center"',
  'no_print' => TRUE
);

$TABLE_CONFIG['schema'][] = array(
  'field' => 'changeObjectsPosition(ID)',
  'class' => 'image',
  'label' => '&nbsp;',
  'width' => '1px',
  'add' => 'align="center"',
  'no_print' => TRUE
);

/*
$TABLE_CONFIG['schema'][] = array(
	'field' => 'createNewFrom(ID)',
	'class' => 'image',
	'label' => '&nbsp;',
	'width' => '1px',
	'add' => 'align="center"',
	'no_print' => TRUE
);
*/
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