<?php

$TABLE_CONFIG['schema'][] = array(
  'field' => 'ShowNazev(NAZEV, TEXT, ID)',
  'label' => 'Název',
  'width' => '40%',
  'add' => 'align=left',
);
$TABLE_CONFIG['schema'][] = array(
  'field' => 'POPIS',
  'label' => 'Popis',
  'width' => '40%',
  'add' => 'align=left',
);
$TABLE_CONFIG['schema'][] = array(
  'field' => 'zobrazDokumentace(ID)',
  'label' => 'Dokumenty',
  'width' => '20%',
  'add' => 'align=left',
  'ishtml' => true,
);

if (HasRole('spravce'))
$TABLE_CONFIG["schema"][] = array(
  "field" => "'<a href=\"javascript:newfrom('...ID...')\"><img src=\"" . FileUpImage('images/add', $PROPERTIES['AGENDA_IDENT']) . "\" title=\"Založit jako nový záznam\" border=\"0\"></a>'",
  "class" => "image",
  "label" => "&nbsp;",
  "add" => "align=\"center\""
);

$TABLE_CONFIG['syscolumns'] = array(
  'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'info' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
);

NewWindow(array("fname" => "Sort", "name" => "Sort", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Setřídit',
  //'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '&so=' . $GLOBALS['so'].'\');',
  'url' => 'javascript:NewWindowSort(\'sort.php?id=' . $t->name . '&so=' . $GLOBALS['omez_zarizeni'].'\');',
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

//   $TABLE_TOP_MENU["schema"] = array(
//     array("label"=>"Načíst vše",  "url"=>"javascript:RunScript_Tisk('receive.php','".$table_params['tablename']."')", "target"=>"_self", "title"=>"Načíst"),
// );

//echo "  newwindow = window.open('edit.php?insertfrom&EDIT_ID='+id, 'agenda_nova', 'height=500,width=760,scrollbars,resizable');\n";


echo "
  <script>
  <!--
    
  function sortCloseCallback() {
    window.location.reload();
  }
  function newfrom(id) {
    NewWindowSort('./edit.php?insertfrom&EDIT_ID='+id);
  }

 //-->
</script>
";


