<?php
include(FileUp2('.admin/config.inc'));
include_once(FileUpUrl('.admin/table_func.inc'));
require_once(Fileup2(".admin/vnejsi_adresati.inc"));

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array( 
      'type'=>'select_adresati_skupina', 
      'name'=>'TYP',
      'insertnull'=>$if_filter,
      'admin' => HasRole('spravce'),
    ),
  ),
  'label'=>'Typ skupiny:',
);										 



$FORM_CONFIG['schema'][] = array( 
  'elements' => array(
    array( 
      'type' => 'text', 
      'name' => 'NAZEV_SKUPINY',
      'size' => 30
    )
  ),
  'visible' => true,
  'label' => 'Název skupiny'
);

  $vnejsiAdresati = getVnejsiAdresaty(intval($GLOBALS['EDIT_ID']));
  if(!empty($vnejsiAdresati)) {	
		foreach ($vnejsiAdresati as $id => $adresat) { 
			$adrName = 'ADRESAT-'.$adresat['id'].'-OLD';
			$FORM_CONFIG["schema"][] = array("elements"=>array(
			  array(
				"type"=>"text",
				"name"=>$adrName,
				'value'=> $adresat['name'],
				"size"=>"80",
				"label"=>"Vyhledat adresu:",
				"add"=>'placeholder="např.: brno muzeum" class="adr" data-multiple-item="true" id=""',
				"disabled_onoff"=>$is_multiedit
			  ),
			),
			  "format"=>"$adrName",
			  "visible"=>true,										 
			  "label"=>"Adresáti:",
			); 
		}
	} else {
		$FORM_CONFIG['schema'][] = array( 
		'elements' => array(
		array( 
		'type'  => 'text', 
		'name'  => 'ADRESAT-0-OLD',
		'value' => '',
		'size'  => 40,
		"add"=>'placeholder="např.: brno muzeum" class="adr" data-multiple-item="true" id=""',
		)
		),
		'visible' => true,
		'label' => 'Adresáti:'
		);
	}

?>


<?php/*  if ($is_edit || $is_insert || $is_new || $is_multiedit) {  */?>

<style>
<?php include(FileUp2('/css/autocomplete.css'));?>
</style>
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.1/jquery-ui.min.js"></script>
<script type="text/javascript">
<?php include(FileUp2('/js/jquery.placeholder/jquery.placeholder.js'));
      include(FileUp2('/js/adresat.js'));
      include(FileUp2('/js/multiple_items.js'));
?>
</script>


<?php /* }  */?>