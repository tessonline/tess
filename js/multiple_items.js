"use strict";
/*jshint undef: false */

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
    $clone.find("input, select").val(""); 
    
    //podpora select2
    $clone.find("span").remove();
    try {
    	$clone.find("[id^="+nameToClone+"]").select2();
    }
    catch(err) { }
    //podpora select2 end
    
    var zpracovatel = $clone.find("[name^="+nameToClone+"]").val("");
    //$clone.find("[name^='ZPRACOVATEL']").attr("disabled","disabled");
    $clone.setItemName(true);
    
    return $clone;
  };
  
    
  /**
   * Metoda nastavi atribut name polozky
   * @param bool newItem - Zda se jedna o novou polozku nebo ne.
   * @global integer newItemsCounter - Pocet novych polozek.
   */
  $.fn.setItemName = function (newItem) {
  
    newItemsCounter++;
    
    $(this).find("[data-multiple-item=true]").each(function () {

      var $item = $(this);
      var newFlag = "-NEW";
      var oldName = $item.attr("name");
      var newName = "";
      var oldNameArray = oldName.split("-");
      
      
     
      if (newItem || oldNameArray.length != 2) {
        newName = oldNameArray[0] + "-" + newItemsCounter + newFlag;
      }
      else {
        newName = oldName;
      }
      
      //podpora pro select2
      $item.parent().find("span[id^='select2']").each(function () {
    	  $(this).attr("id","select2-"+newName+"-container");
          $item.attr("id", newName);
      }
    );
      $item.parent().find("span[aria-labelledby^='select2']").each(function () {
    	  $(this).attr("aria-labelledby","select2-"+newName+"-container");
      }
    );
    //podpora pro select2 end
      	
      
      $item.attr("name", newName);
    });
  };
  
  
  /**
   * Metoda vytvori tlacitko pro pridani polozky
   */
  $.fn.addAddButton = function () {
    var $addButton = $("<a>", {
      "class": "add button",
      "title": "P\u0159idat polo\u017eku"
    });
    
    $(this).find(".form-item").last().find(".form-field").append($addButton);
  };
  
  /**
   * Metoda vytvori tlacitko pro odebrani polozky
   */
  $.fn.addRemoveButton = function () {

    var $removeButton = $("<a>", {
      "class": "remove button",
      "title": "Odebrat polo\u017eku"
    });
    
    $(this).each(function () {
      
      $(this).find(".form-item").last().find(".form-field").append($removeButton.clone());
    });
  };
  
  /**
   * Metoda aktualizuje tlacitka pro pridani a odebrani polozky u vsech polozek
   */
  $.fn.updateButtons = function () {
    
    var $multipleItemTr = $(this);
    
    // odebrani vsech tlacitek
    $multipleItemTr.find(".button").remove();
      
    // pokud polozka neni jen jedna, prida se vsem tlacitko pro odebrani
    if ($multipleItemTr.length > 1) {
      
      $multipleItemTr.addRemoveButton();
    }
    
    // posledni polozce se prida tlacitko pro pridani nove polozky
    $multipleItemTr.last().addAddButton();    
  };
  
  /**
   * Listener pro odchyceni udalosti pri kliknuti na nektere z tlacitek
   */
  $(".editForm").on("click", ".form-row", function (event) {
    
    var target = event.target || event.srcElement;
    var $target = $(target);      
    var $tr = $(this);
    
    if ($target.hasClass("add button")) {
      // Pridani polozky
      $tr.after($tr.prepareItem());
    }
    else if ($target.hasClass("remove button")) {
      // Odebrani polozky
      $tr.remove();
    }
    
    var $multipleItemTr = $(".form-row").has("[data-multiple-item=true]");
    
    $multipleItemTr.updateButtons();
  });
  
  // Atribut name prvniho elementu, ktery ma nastaveni atribut [data-multiple-item=true]
  var nameToClone = $(this).find("[data-multiple-item=true]").first().attr("name");
  
  // Pocitadlo novych polozek (generuje unikatni id)
  var newItemsCounter = 0;
  
  // Vybrani duplikovaneho radku
  var $multipleItemTr = $(".form-row").has("[data-multiple-item=true]");
  
  $multipleItemTr.setItemName(false);
  $multipleItemTr.updateButtons();
  
});
