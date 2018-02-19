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
  background: url('images/add.png');
}

form a.button.remove {
  background: url('images/delete.png');
}
</style>
  <script defer src="<?php echo fileUpUrl('js/multiple_items.js'); ?>" type="text/javascript"></script>
  <script defer src="<?php echo fileUpUrl('js/vnitrni_adresati.js'); ?>" type="text/javascript"></script>
<?php
require_once(Fileup2(".admin/vnitrni_adresati.inc"));


if ($GLOBALS['DATUM_VYPRAVENI']) $is_send = true; else $is_send = false;


$url_nastaveni = GetAgendaPath('POSTA_NASTAVENI_VNITRNIADR', 0, 1) . '/index.php';

$temp = array();
$a = 0;
foreach($FORM_CONFIG["schema"] as $key => $val) {
  if ($FORM_CONFIG["schema"][$key]['elements'][0]['name'] == 'AGENDA_DOKUMENTU') {
    $temp[$a] = $temp[10];
    $a++;
    $temp[10] = $val; //dame na prvni misto
  }
  elseif ($FORM_CONFIG["schema"][$key]['elements'][0]['name'] == 'ODES_TYP') {
    $temp[$a] = array('elements'=>array(
        array(
          'type' => 'select_odes_typ',
          'name' => 'ODES_TYP',
          'width'=>10,
          "multiple"=>$false,
          'required' => 'true',
          'add' => 'onChange=\'DruhAdresataWhoIS(this.value)\';onFocus=\'DruhAdresataWhoIS(this.value)\'')
        ),
        'visible'=>$is_edit or $is_info or $is_insert or $is_new,
        'label'=>$label_adresat
      );
    
    $a++;
    $temp[$a] = array(
      "elements"=>array(
        array(
          "type" => "select_vnitrni_adresati_skupina",
          "name" => "VNITRNI_ADRESATI_SKUPINY"
        ),
        array( 'type' => 'button', 'name' => 'pridatAdresaty', 'add'=>' class="btn"', 'value' => 'Vložit'),
        array( 'type' => 'button', 'name' => 'Nastaveni', 'add'=>' class="btn"', 'value' => 'Nastaveni', 'onclick' => 'NastaveniVnitrniPosty()'),
      ),
      "format"   => "VNITRNI_ADRESATI_SKUPINY...'&nbsp;&nbsp;&nbsp;<a href=\"#\" name = \"pridatAdresaty\" class=\"btn\">Přidat</a>&nbsp;&nbsp;&nbsp;<a href=\"$url_nastaveni\" class=\"btn\" target=\"blank\">Nastavení</a>'",
      "label"    => "Přednastavení adresáti:",
      "visible"  => $is_update && !$is_send
    );
    
    $vnitrniAdresati_count = 0;
    
    if ($is_new || $is_insert) $GLOBALS['MULTI_ODBOR'] = VratSuperOdbor();
    
    // MULTI ITEMS SUPPORT - BEGIN
    
    $isZpracovatelRequired = $GLOBALS['CONFIG']['VNITRNI_POSTA_JEN_ZPRACOVATELI'];
    $zpracovatelAdd = $isZpracovatelRequired ? ' data-required="ZPRACOVATEL" class="required"' : '';
    if ($is_edit || $is_info) {
      
      // Jeden zaznam posty (jeden spis) muze mit nekolik adresatu.
      // Ti se ukladaji do vedlejsi tabulky posta_vnitrni_adresati.
      // Mezi tabulkami posta a posta_vnitrni_adresati je vazba 1:N.
      // Zde se tedy vygeneruji vsechni adresati daneho spisu.
      $vnitrniAdresati = getVnitrniAdresaty(intval($GLOBALS['EDIT_ID']));
      
      $vnitrniAdresati_count = sizeof($vnitrniAdresati);
      
      foreach ($vnitrniAdresati as $id => $adresat) {
        
        $organizacniVyborName = 'ORGANIZACNI_VYBOR-' . $id;
        $zpracovatelName = 'ZPRACOVATEL-' . $id;
        $a++;
        $temp[$a] = array(
          "elements"=>array(
            array(
              "type"=>"select_interni_spisuzly2",
              "name"=> $organizacniVyborName,
              'value'=> $adresat['ov'],
              "insertnull"=>"true",
              "abbr"=>true,
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
    if ((!$is_edit && !$is_info) || $vnitrniAdresati_count == 0) {
      $a++;
      $temp[$a] = array(
        "elements"=>array(
          array(
            "type"=>"select_interni_spisuzly2",
            "name"=> 'ORGANIZACNI_VYBOR',
            "insertnull"=>"true",
            "abbr" => true, 
            'extrahtml' => "onChange=\"UkazPracovnika(this,'ODESL_PRAC2');\"",
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
    
    
     $a++;
    $temp[$a] = array('elements'=>array(
        array( 'type' => 'text_number', 'name' => 'WHOIS_NUMBER', 'size' => '15', 'required'=>false,'label' => 'WhoIS identifikátor'),
        array( 'type' => 'text_number', 'name' => 'WHOIS_IDSTUDIA', 'size' => '15', 'required'=>false,'label' => 'ID studia'),
        array( 'type' => 'hidden', 'name' => 'WHOIS_TYPOVYSPISID'),
        array( 'type' => 'hidden', 'name' => 'WHOIS_TYPOVYSPISSOUCAST'),
        array( 'type' => 'button', 'name' => 'Ares', 'value' => 'Hledat ve WhoIS', 'onclick' => 'GuideWHOIS()', 'label' => 'WHOIS', 'tooltip' => 'test'),
      ),
      'visible'=>$is_edit || $is_insert || $is_new || $is_info || $is_filter_all,
      'label' => 'Člověk:',
    );
     $a++;
  }

  else {
     $temp[$a] = $val;
     $a++;
  }

}
unset($FORM_CONFIG);
for ($a=0; $a<count($temp); $a++ ) {
  if (is_array($temp[$a]))
    $FORM_CONFIG['schema'][] = $temp[$a];
}


$fce_uk_whois = "

  var val = document.forms[0].ODES_TYP.value;
  if((val=='C' || val=='G') && !document.forms[0].WHOIS_NUMBER.value)   {
    alert('Při zadání studenta je potřebné vyplnit WHOIS číslo!');
    document.forms[0].WHOIS_NUMBER.focus();
    return(false);
  }
  if(val=='C' && !document.forms[0].WHOIS_IDSTUDIA.value)   {
    alert('Při zadání studenta je potřebné vyplnit ID STUDIA (dohledejte přes WhoIS)!');
    document.forms[0].WHOIS_IDSTUDIA.focus();
    return(false);
  }

  if((val=='C' || val=='G') && (!document.forms[0].ODESL_PRIJMENI.value || !document.forms[0].ODESL_JMENO.value))   {
    alert('Při zadání fyzické osoby je nutné zadat její příjmení a jméno!');
    document.forms[0].ODESL_PRIJMENI.focus();
    return(false);
  }

//    if((val=='C' || val=='G') && (!document.forms[0].WHOIS_TYPOVYSPISID.value) || (document.forms[0].WHOIS_TYPOVYSPISID.value == '0'))   {
//      TypovySpisWHOIS();
//      return false;
//    }
//    if((val=='C' || val=='G') && (!document.forms[0].WHOIS_TYPOVYSPISSOUCAST.value) || (document.forms[0].WHOIS_TYPOVYSPISSOUCAST.value == '0'))   {
//      TypovySpisWHOIS();
//      return false;
//    }
//

  $( \"input[type='submit']\" ).attr('value' ,'ukládám....');
  $( \"input[type='submit']\" ).attr('disabled' ,'');

";


$FORM_CONFIG["schema"][] = array("elements"=>array(
   array("type"=>"valid_fce","name_fce"=>$fce_uk_whois)),
      "visible"=>$is_edit || $is_insert || $is_new,
   );

include_once(FileUp2('plugins/uk/.admin/javascript_end.inc'));
