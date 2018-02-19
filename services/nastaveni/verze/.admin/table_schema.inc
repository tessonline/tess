<?php
$TABLE_CONFIG['schema'][] = array(
  field => 'CISLO',
  label => 'Verze',
  order_by => 'CISLO'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'DATUM',
  label => 'Datum',
  order_by => 'DATUM'
);

$TABLE_CONFIG['schema'][] = array(
  field => 'PLUGIN',
  label => 'Plugin',
  order_by => 'PLUGIN'
);
/*
$TABLE_CONFIG['schema'][] = array(
  field => "POPIS...'<br/>'...OPRAVY",
  label => 'Popis',
  order_by => 'POPIS'
);
*/
$TABLE_CONFIG['schema'][] = array(
  field => "POPIS",
  label => 'Nová funkcionalita',
  width => '40%',
  is_html => true,
  order_by => 'POPIS'
);

$TABLE_CONFIG['schema'][] = array(
  field => "OPRAVY",
  label => 'Opravy',
  width => '40%',
  is_html => true,
  order_by => 'OPRAVY'
);


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


$TABLE_CONFIG['syscolumns'] = array(
 'upload' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


