<?php
$TABLE_CONFIG = array(
//  'callback'=> 'ChangeClassBarva',
  'schema' => array( 
    array( field=>'NAZEV', label=>'Název'),
    
  )
 );

if (HasRole('spravce')) {

  $TABLE_CONFIG['schema'][] = array( field=>'UkazUsera(OWNER_ID)', label=>'Zpracovatel');
  $TABLE_CONFIG["schema"][] = array(
    "field" => "'<a href=\"javascript:newfrom('...ID...')\"><img src=\"" . FileUpImage('images/add', $PROPERTIES['AGENDA_IDENT']) . "\" title=\"Založit jako nový záznam\" border=\"0\"></a>'",
    "class" => "image",
    "label" => "&nbsp;",
    "add" => "align=\"center\""
  );

  NewWindow(array("fname" => "Sort", "name" => "Sort", "header" => true, "cache" => false, "window" => "edit","afterClose" => "sortCloseCallback"));

  echo "
  <script>
  <!--

  function newfrom(id) {
    NewWindowSort('./edit.php?insertfrom&EDIT_ID='+id);
  }

 //-->
</script>
";


}

$TABLE_CONFIG['syscolumns'] = array(
  'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'info' => array ('theme'=>array('dropdown'=>true, 'column'=>false)),
  'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
  'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);

