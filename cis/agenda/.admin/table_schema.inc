<?php

$TABLE_CONFIG['callback'] = 'changeCellClass';
$TABLE_CONFIG["schema"][] =  array( "field"=>"NAZEV", "label"=>"Agenda");

NewWindow(array("fname" => "KopirovatAgendu", "name" => "KopirovatAgendu", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_CONFIG['schema'][]
= array(
  'field' => 'kopirovatAgendu(ID)',
  //'label' => 'Kopírovat agendu',
  'add' => 'align = center',
  'width' => '1%',
  'class' => 'image',
  'add' => 'NOWRAP',
  'settings' => 'function',
  'theme' => array(
    'dropdown'=>false,
    'column'=>true
  ),
);

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);

NewWindow(array("fname" => "Sort", "name" => "Sort", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
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

if (HasRole('spravce')||HasRole('super_spravce')) {
  $TABLE_TOP_MENU["schema"][] = array(
    'label' => 'Exportovat přehled (TXT)',
    'url' => 'javascript:RunScript_Export(\'prehled_agend.php?so='.$_GET['omez_zarizeni'].'\',\'AGENDY\');',
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
    'label' => 'Exportovat přehled (CSV)',
    'url' => 'javascript:RunScript_Export(\'prehled_agend.php?CSV=1&so='.$_GET['omez_zarizeni'].'\',\'AGENDY\');',
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
  
}


echo "
 
  <script type=\"text/javascript\">
  function RunScript_Export(name_script, tablename){;
    var frm = document.forms['frm_'+tablename];
    frm.method='POST';
    var act = frm.action;
    var tar = frm.target;
    frm.action = name_script;
    frm.submit();
    frm.action = act;
    frm.target = tar;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='0';
  }

  <!--

  function sortCloseCallback() {
    window.location.reload();
  }

 //-->
</script>
";