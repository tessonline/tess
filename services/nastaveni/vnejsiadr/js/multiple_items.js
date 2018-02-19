/**
 *  Skript zajistuje podporu pro duplikovani polozky resp. polozek pokud jsou soucasti jednoho radku.
 *  Podminky:
 *   Duplikovane polozky musi mit atribut data-multiple-item="true".
 *   Duplikovane polozky musi byt soucasti jednoho radku formulare (tabulky).
 *   Duplikovane polozky musi mit atribut name ve tvaru NAZEV_POLOZKY-ID_POLOZKY
 */ 

$(document).ready(function() {

  /**
   * Funkce predpripravi radek pro jeho duplikaci:
   * Vynuluje hodnotu polozky, upravi atribut name na tvar: NAZEV_POLOZKY-ID-NEW.
   * @return jQueryCollection - Novy radek formulare.
   */
  $.fn.prepareItem = function () {
    
    var $clone = $(this).first().clone();
    var adresat = $clone.find('[name^=ADRESAT]').val('');
    
    $clone.find('input, select').val(''); 
	
    //zpracovatel[0].disabled = true;
    //$clone.setItemName(true);
    //autocomplete(); //bind autocomplete to new element
	/*						*/
	 $('[name="ADRESAT"]').autocomplete({
		source: "get_adresat.php",
		minLength: 5,
		
		}); 
    return $clone;
  }
  
  /**
   * Metoda nastavi atribut name polozky
   * @param bool newItem - Zda se jedna o novou polozku nebo ne.
   * @global integer newItemsCounter - Pocet novych polozek.
   */
  $.fn.setItemName = function (newItem) {
  
    newItemsCounter++;
  
    $(this).find('[data-multiple-item="true"]').each(function () {
    
      var $item = $(this);
      var newFlag = '-NEW';
      var oldName = $item.attr('name');
      var newName = '';
      var oldNameArray = oldName.split('-');
      
      if (newItem || oldNameArray.length != 2) {
        newName = oldNameArray[0] + '-' + newItemsCounter + newFlag;
      }
      else {
        newName = oldName;
      }
      
      //$item.attr('name', newName);
    });
  }
  
  /**
   * Metoda vytvori tlacitko pro pridani polozky
   */
  $.fn.addAddButton = function () {

    var $addButton = $('<a>', {
      'class': 'add button',
      'title': 'P\u0159idat polo\u017eku'
    });
    
    $(this).find('td').last().append($addButton);
  }
  
  /**
   * Metoda vytvori tlacitko pro odebrani polozky
   */
  $.fn.addRemoveButton = function () {

    var $removeButton = $('<a>', {
      'class': 'remove button',
      'title': 'Odebrat polo\u017eku'
    });
    
    $(this).each(function () {
      
      $(this).find('td').last().append($removeButton.clone());
    });
  }
  
  /**
   * Metoda aktualizuje tlacitka pro pridani a odebrani polozky u vsech polozek
   */
  $.fn.updateButtons = function () {
    
    var $multipleItemTr = $(this);
    
    // odebrani vsech tlacitek
    $multipleItemTr.find('.button').remove();
      
    // pokud polozka neni jen jedna, prida se vsem tlacitko pro odebrani
    if ($multipleItemTr.length > 1) {
      
      $multipleItemTr.addRemoveButton();
    }
    
    // posledni polozce se prida tlacitko pro pridani nove polozky
    $multipleItemTr.last().addAddButton();    
  }
  
  /**
   * Listener pro odchyceni udalosti pri kliknuti na nektere z tlacitek
   */
  $('table').on('click', 'tr', function (event) {
    
    var target = event.target || event.srcElement;
    var $target = $(target);      
    var $tr = $(this);
    
    if ($target.hasClass('add button')) {
      // Pridani polozky
      $tr.after($tr.prepareItem());
	  
	  //alert($tr.prepareItem());
	//autocomplete
	$('.adr').autocomplete({
    
    source: "get_adresat.php",
    minLength: 4,
    
    select: function(event, ui) {
      
      if (ui.item.id) {
		 $(this).attr('name','');
		 //nastavi name na ADRESAT-ID-NEW
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
  
    }
    else if ($target.hasClass('remove button')) {
      // Odebrani polozky
      $tr.remove();
	  
    }
    
    var $multipleItemTr = $('tr').has('[data-multiple-item="true"]');
    
    $multipleItemTr.updateButtons();
  });
  
  // Pocitadlo novych polozek (generuje unikatni id)
  newItemsCounter = 0;
  
  // Vybrani duplikovaneho radku
  var $multipleItemTr = $('tr').has('[data-multiple-item="true"]');
  
  $multipleItemTr.setItemName(false);
  $multipleItemTr.updateButtons();
  
});