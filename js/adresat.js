/**
 *  Skript resi podporu pro zadavni adresatu rucne nebo pomoci jQuery autocomplete.
 */

$(document).ready(function() {
	
  $('input, textarea').placeholder();
  
  toggleAdresa();
  
  $('[name="ODES_TYP"]').on('change', function () {
    
    toggleAdresa();
  });
  
  /**
   * jQuery UI plugin autocomplete
   */
  $('[name="ADRESAT"]').autocomplete({
    
    source: "get_adresat.php",
    minLength: 5,
    
    select: function(event, ui) {
      
      if (ui.item.id) {
        $('[name="ADRESAT_ID"]').val(ui.item.id);
        $('.autocomplete-result').text(ui.item.preview);
        $('[name="ODESL_DATSCHRANKA"]').val(ui.item.DS);
      }
    },
    
    response: function(event, ui) {
      
      if (!ui.content.length) {
        
        ui.content[0] = {label: 'Zadanému textu neodpovídá \u017eádná adresa'};
      }
    }
  });
  
  /**
   * Handler pro udalost odeslani formulare.
   * Kontrola pokud je vyuzivan autocomplete, tak musi byt vybrana nejaka adresa a tedy
   * nastaveno id adresata v hidden polozce ADRESAT_ID.
   */
  $('form[name="frm_edit"]').on('submit', function () {
     
    if (isUsedAutocomplete() && isEditable()) {
    
      // adresat vytvoreny pomoci autocomplete
      var $adresat = $('[name="ADRESAT_ID"]');
      // prednastaveni adresati
      var $adresati = $('[name^="ADRESAT_ID_"]'); 
      
//      if (!$adresati.length && ($adresat.val() == '' || $adresat[0].disabled)) {   
      
//        window.alert('Nebyla vybrána adresa odesílatele!');
//        $adresat.focus();
        // Standardni T-WIST validace formulare nastavi tlacitko submit na disabled (nutne zrusit)
//        $('[name="__"]')[0].disabled = false;

//        return false;
//      }
    }
    else {
      clearAdresatAutocomplete();
    
      return true;
    }
  });
});

/**
 * Funkce na zaklade vybrane hodnoty v combo boxu ODES_TYP zobrazi polozky pro rucni zadani adresy
 * nebo zobrazi pole pro vyhledani adresy pomoci autocomplete.
 * @param $typAdresata jQueryObject Combo box ODES_TYP.
 */
var toggleAdresa = function() {
  
  if (isUsedAutocomplete()) {
    $('[name="ODESL_PRIJMENI"]').parents('tr').hide();
    $('[name="ADRESAT"]').parents('tr').show();
    $('[name="VNEJSI_ADRESATI_SKUPINY"]').parents('tr').show();
  }
  else {
    $('[name="ODESL_PRIJMENI"]').parents('tr').show();
    $('[name="ADRESAT"]').parents('tr').hide();
    $('[name="VNEJSI_ADRESATI_SKUPINY"]').parents('tr').hide();
  }
}

/**
 * Funkce uvede block s autocompletem do vychoziho stavu (vymaze vsechna data).
 */
var clearAdresatAutocomplete = function() {
  
  var adresatHidden = $('[name="ADRESAT_ID"]');
  
  $('[name="ADRESAT"]').val('');
  adresatHidden[0].disabled = true;
  adresatHidden.val('');
  $('.autocomplete-result').text('');
}

/**
 * Funkce zjistuje zda ma byt pri zadavani adresy pouzivan autocomplete nebo ne.
 * @return bool Pokud existuje combobox ODES_TYP a zaroven aktualne vybrana polozka ma
 *  atribut data-autocomplete="true" pak true, jinak false.
 */
var isUsedAutocomplete = function() {
  
  var $typAdresata = $('[name="ODES_TYP"]');
  
  if ($typAdresata.length) {
    return $typAdresata.find('option:selected').filter('[data-autocomplete="true"]').length ? true : false;
  }
  else {
    return true;
  }
}

/**
 * Funkce zjistuje zda je adresat editovatelny (pro vyhodnoceni v multiedit formulari)
 * @return bool Pokud existuje checkbox ADRESAT_onoff a zaroven je zaskrtnuty pak true, jinak false.
 */
var isEditable = function() {
     
  var $adresatOnOff = $('[name="ADRESAT_onoff"]');
  
  if ($adresatOnOff.length) {
    return $adresatOnOff[0].checked;
  }
  else {
    return true;
  }
}
