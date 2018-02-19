   <script src="//ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js" type="text/javascript"></script>
   <style>
  /* Tlacitka pro duplikovani polozek ve formulari */
form a.button {
  display: inline-block;
  width: 22px;
  height: 22px;
  vertical-align: middle;
  cursor: pointer;
}

form a.button.add {
  background: url('./../../../images/add.png');
}

form a.button.remove {
  background: url('./../../../images/delete.png');
}
</style>
<?php
//
include(FileUp2('.admin/config.inc'));
require_once(Fileup2(".admin/vnitrni_adresati.inc"));

if ($form_params['formtype'] == $f_insert) $is_insert = true; else $is_insert = false;
if ($form_params['formtype'] == $f_info) $is_info = true; else $is_info = false;
if ($form_params['formtype'] == $f_edit) $is_edit = true; else $is_edit = false;
if ($form_params['formtype'] == $f_filter) $is_filter = true; else $is_filter = false;
if ($form_params['formtype'] == $f_filterall) $is_filterall = true; else $is_filterall = false;

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
  'elements'=>array(
    array( 
      'type'=>'hidden', 
      'name'=>'OWNER_ID',
      'insertnull'=>!$if_filter,
    ),
  ),
  'label'=>'Typ skupiny:',
);										 

$FORM_CONFIG['schema'][] = array(
  'elements'=>array(
    array(
      'type'=>'text', 
      'name'=>'NAZEV'
      
    ),   
  ),
  'label'=>'Název skupiny:'
);

// MULTI ITEMS SUPPORT - BEGIN

/*
if ($is_edit || $is_info) {

  // Jeden zaznam skupiny muze mit nekolik adresatu.
  // Ti se ukladaji do vedlejsi tabulky posta_nastaveni_vnitrni_adresati.
  // Mezi tabulkami posta_nastaveni_vnitrni_adresati_skupiny a
  // posta_nastaveni_vnitrni_adresati je vazba 1:N.
  // Zde se tedy vygeneruji vsechni adresati dane skupiny.
  $vnitrniAdresati = getVnitrniAdresaty(intval($GLOBALS['EDIT_ID']));

  foreach ($vnitrniAdresati as $id => $adresat) {

    $organizacniVyborName = 'ORGANIZACNI_VYBOR-' . $id;
    $zpracovatelName = 'ZPRACOVATEL-' . $id;

    $FORM_CONFIG["schema"][] = array(
      "elements" => array(
        array(
          "type"        => "select_spisuzly",
          "name"        => $organizacniVyborName,
          'value'       => $adresat['ov'],
          "insertnull"  => "true",
          'add'         => 'data-multiple-item="true" style="width: 350px;"'
        ),
        array(
          "type"        => "select_referent",
          "name"        => $zpracovatelName,
          'value'       => $adresat['zp'],
          'set_odbor'       => $adresat['ov'],
          "insertnull"  => "true",
          'add'         => 'data-multiple-item="true"' . $zpracovatelAdd,
          'fullselect'  => false
        )
      ),
      "format"  => "$organizacniVyborName...'&nbsp;Zpracovatel:'...$zpracovatelName",
      "label"   => $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':'
    );
  }
}
else {

  $FORM_CONFIG["schema"][] = array(
    "elements" => array(
      array(
        "type"        => "select_spisuzly",
        "name"        => 'ORGANIZACNI_VYBOR',
        "insertnull"  => "true",
        'add'         => 'data-multiple-item="true" style="width: 350px;"'
      ),
      array(
        "type"        => "select_referent",
        "name"        => 'ZPRACOVATEL',
        "insertnull"  => "true",
        'add'         => 'disabled="disabled" data-multiple-item="true"' . $zpracovatelAdd,
        'fullselect'  => true
      )
    ),
    "format"  => "ORGANIZACNI_VYBOR...'&nbsp;Zpracovatel:'...ZPRACOVATEL",
    "visible" => $is_update,
    "label"   => $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':'
  );  
}

// MULTI ITEMS SUPPORT - END*/


$isZpracovatelRequired = $GLOBALS['CONFIG']['VNITRNI_POSTA_JEN_ZPRACOVATELI'];
$zpracovatelAdd = $isZpracovatelRequired ? ' data-required="ZPRACOVATEL" class="required"' : '';
if ($is_edit || $is_info) {
  
  // Jeden zaznam posty (jeden spis) muze mit nekolik adresatu.
  // Ti se ukladaji do vedlejsi tabulky posta_vnitrni_adresati.
  // Mezi tabulkami posta a posta_vnitrni_adresati je vazba 1:N.
  // Zde se tedy vygeneruji vsechni adresati daneho spisu.
  $vnitrniAdresati = getVnitrniAdresaty(intval($GLOBALS['EDIT_ID']));
  
  foreach ($vnitrniAdresati as $id => $adresat) {
    
    $organizacniVyborName = 'ORGANIZACNI_VYBOR-' . $id;
    $zpracovatelName = 'ZPRACOVATEL-' . $id;
    $FORM_CONFIG["schema"][]= array(
      "elements"=>array(
        array(
          "type"=>"select_interni_spisuzly2",
          "name"=> $organizacniVyborName,
          'value'=> $adresat['ov'],
          "insertnull"=>"true",
          "frozen"=>$is_send,
          'add' => 'data-multiple-item="true"
                        data-required="ORGANIZACNI_VYBOR"
                        class="required"
                        style="width: 350px;"'
        ),
        array(
          "type"=>"select_referent",
          "name"=> $zpracovatelName,
          'value'=> $adresat['zp'],
          'set_odbor'=> $adresat['ov'],
          "insertnull"=>"true",
          "frozen"=>$is_send,
          'add' => 'data-multiple-item="true"' . $zpracovatelAdd,
          'fullselect' => false,
          'label' => 'Zpracovatel'
        )
      ),
      "format"=>"$organizacniVyborName...'&nbsp;Zpracovatel:'...$zpracovatelName",
      "label"=>$is_edit ? '<b>' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':</b>' : $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':',
      // zruseni format pro tema square
      'theme_config' => array(
        'square' => array(
          'format' => '',
        )
      )
    );
    
  }
}
else {

  $FORM_CONFIG["schema"][]= array(
    "elements"=>array(
      array(
        "type"=>"select_interni_spisuzly2",
        "name"=> 'ORGANIZACNI_VYBOR',
        "insertnull"=>"true",
        'add' => 'data-multiple-item="true"
                      data-required="ORGANIZACNI_VYBOR"
                      class="required"
                      style="width: 360px;"'
      ),
      array(
        "type"=>"select_referent",
        "name"=> 'ZPRACOVATEL',
        "insertnull"=>"true",
        'add' => 'disabled="disabled" data-multiple-item="true"' . $zpracovatelAdd,
        'label' => 'Zpracovatel',
        'fullselect' => true
      )
    ),
    "format"=>"ORGANIZACNI_VYBOR...'&nbsp;Zpracovatel:'...ZPRACOVATEL",
    "visible"=>$is_update,
    "label"=>$GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':',
    // zruseni format pro tema square
    'theme_config' => array(
      'square' => array(
        'format' => '',
      )
    )
  );
}

// MULTI ITEMS SUPPORT - END

?>

<?php if ($is_edit || $is_insert) { ?>

  <script defer src="<?php echo fileUpUrl('js/multiple_items.js'); ?>" type="text/javascript"></script>
  <script defer src="<?php echo fileUpUrl('js/vnitrni_adresati.js'); ?>" type="text/javascript"></script>
  
<?php } ?>
