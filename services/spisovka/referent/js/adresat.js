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
   
  //$('[name="ADRESAT"]').autocomplete({
  $('.adr').autocomplete({
    
    source: "get_adresat.php",
    minLength: 4,
    
    select: function(event, ui) {
      
      if (ui.item.id) {
        $('[name="ADRESAT_ID"]').val(ui.item.id);
		 var pom = 'ADRESAT-'+ui.item.id+'-NEW';
		 $(this).attr('name',pom);	
        $('.autocomplete-result').text('Vybráno: ' + ui.item.preview).show();
      }
    },
    
    response: function(event, ui) {
      
      if (!ui.content.length) {
        
        ui.content[0] = {label: 'Zadanému textu neodpovídá \u017eádná adresa'};
      }
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
  }
  else {
    $('[name="ODESL_PRIJMENI"]').parents('tr').show();
    $('[name="ADRESAT"]').parents('tr').hide();
  }
}

/**
 * Funkce uvede block s autocompletem do vychoziho stavu (vymaze vsechna data).
 */
var clearAutocomplete = function() {
  
  $('[name="ADRESAT"]').val('');
  $('[name="ADRESAT_ID"]').val('');
  $('.autocomplete-result').text('').hide();
}

/**
 * Funkce zjistuje zda je pri zadavani adresy pouzivan autocomplete nebo ne.
 * @return bool Pokud je pouzivan autocomplete pak true, jinak false.
 */
var isUsedAutocomplete = function() {
  
  return $('[name="ODES_TYP"] option:selected').filter('[data-autocomplete="true"]').length ? true : false;
}

/**
 * Zobrazi uvodni autocomplete input
 */
  $(document).ready(function() {
   $(".adr").closest("tr").removeAttr('style');
});



