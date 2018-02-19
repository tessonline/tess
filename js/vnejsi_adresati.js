/**
 *  Skript zajistuje podporu pro pridavani prednastavenych vnejsich adresatu.
 */

$(document).ready(function() {
  
	
  /**
   * Udalost vyvolana pri kliknuti na tlacitko "Pridat" u prednastavenych adresatu
   * Handler provede HTTP GET request. Tim ziska data (JSON) obsahujici polozky adresatu.
   */
  $('form[name="frm_edit"] .pridatAdresaty').on('click', function (event) {
    
    event.preventDefault();
    
    var selectedSkupinaId = $(this).parents('tr').find('[name="VNEJSI_ADRESATI_SKUPINY"]').val();
    
    $.getJSON('/ost/posta/services/nastaveni/vnejsiadr/get_adresati.php?SKUPINA=' + selectedSkupinaId, function (data) {
      
      for (var item in data) {
        
        $('[name="ADRESAT_ID"]').after('<input type="hidden" name="ADRESAT_ID_' + data[item].id + '" value="' + data[item].id + '" />');        
        $('.autocomplete-result').after('<p>' + data[item].preview + '</p>');
      }
    });
  });
});