"use strict";
/*jshint undef: false */

/**
 *  Skript zajistuje podporu pro duplikovane polozky.
 *  Resi kontrolu required polozek a zmenu nabizenych hodnot v combo boxu zpracovatel v zavislosti
 *  na hodnote v combo boxu organizacni utvar.
 */

$(document).ready(function() {

  var $form = $("form[name=frm_edit]");
  
  /**
   * Udalost vyvolana pri odesilani formulare.
   * Handler kontroluje u polozek s atributem "data-required", zda jsou opravdu hodnoty vyplnene.
   * @return Pokud nejaka polozka vyplnena neni, pak false, jinak true.
   */
  $form.on("submit", function () {
    
    var $form = $(this);
  
    // Definovani required polozek
    var requiredItems = {
      "ORGANIZACNI_VYBOR": "Org. útvar",
      "ZPRACOVATEL": "Zpracovatel"
    };
    
    for (var item in requiredItems) {
      
      var $items = $form.find("[data-required=" + item + "]");
      var isEmpty = false;
      
      $items.each(function () {

        if ($(this).val() == "") {
          
          isEmpty = true;
          return false;
        }      
      });
      
      if ((isEmpty)&& $(this).find("[name=ODES_TYP]").val()=="S") {        
        window.alert("Hodnota v poli \"" + requiredItems[item] + "\" nesmí být prázdná!");
        // Pokud implicitni (jaderna) kontrola polozek formulare v T-WIST nezjisti chybu, nastavi ukladaci
        // tlacitko jako disabled. To je nezadouci pri zpracovani teto kontroly (nelze po oprave
        // znovu formular odeslat).
        $(this).find("[name=__]")[0].disabled = false;
        
        return false;
      }     
    }
    
    return true;
  });
  
  /**
   * Udalost vyvolana pri zmene hodnoty v polozce ORGANIZACNI_VYBOR.
   * Handler provede HTTP GET request. Tim ziska data (JSON) obsahujici
   * polozky zpracovatele, kterymi naplni combobox ZPRACOVATEL.
   */
  $form.on("change", "[name^=ORGANIZACNI_VYBOR]", function () {
    var organizacniVyborId = this.value;
    var $zpracovatele = $(this).parents(".form-row").find("[name^=ZPRACOVATEL]");
    
    $zpracovatele[0].disabled = true;
    
    if (organizacniVyborId) {      
    
      $zpracovatele.find("option").remove();
      $zpracovatele.append('<option value="">Nahrávám zpracovatele.....</option>');
      $.getJSON("/ost/posta/get_zpracovatel.php?ORGANIZACNI_VYBOR=" + organizacniVyborId, function (data) {
        $zpracovatele.find("option").remove();

        for (var item in data) {
          $zpracovatele.append("<option value=" + data[item].value + ">" + data[item].label + "</option>");
        }

        $zpracovatele[0].disabled = false;
      }
);

    }
  });

  /**
   * Udalost vyvolana pri kliknuti na tlacitko "Pridat" u prednastavenych adresatu
   * Handler provede HTTP GET request. Tim ziska data (JSON) obsahujici polozky adresatu.
   */
  $form.on("click", "[name=pridatAdresaty]", function (event) {
    event.preventDefault();

    var selectedSkupinaId = $(this).parents(".form-row").find("[name=VNITRNI_ADRESATI_SKUPINY]").val();

    $.getJSON("/ost/posta/services/nastaveni/vnitrniadr/get_adresati.php?SKUPINA=" + selectedSkupinaId, function (data) {
    		
      var adresatSelector = "[name^=ORGANIZACNI_VYBOR]";
      var $adresatTemplate = $(adresatSelector).first().parents(".form-row").clone();

      for (var item in data) {
        
        $adresatTemplate.setItemName(true);
        $adresatTemplate.set(data[item].organizacniVybor, data[item].zpracovatel, data[item].zpracovatele);        
        $(".form-row").has(adresatSelector).last().after($adresatTemplate);
        $adresatTemplate = $adresatTemplate.clone();
      }
      
      $(".form-row").has(adresatSelector).updateButtons();
    });
  });
  
  /**
   * Metoda nastavi cely radek s adresatem, konkretne:
   *  Hodnotu v comboboxu organizacni utvar.
   *  Polozky v comboboxu zpracovatel.
   *  Hodnotu v comboboxu zpracovatel.
   * @param integer organizacniVyborId Id polozky organizacni vybor.
   * @param integer zpracovatelId Id polozky zpracovatel.
   * @param array zpracovatele Pole zpracovatelu, kterym se naplni combobox zpracovatel.
   */
  $.fn.set = function (organizacniVyborId, zpracovatelId, zpracovatele) {
    
    return $(this).each(function () {
      
      var $adresat = $(this);
      var $organizacniVybor = $adresat.find("[name^=ORGANIZACNI_VYBOR]");
      var $zpracovatele = $adresat.find("[name^=ZPRACOVATEL]");
      
      // Nasatveni polozky organizacni vybor
      
      $organizacniVybor.find("option[value=" + organizacniVyborId + "]")[0].selected = true;
            
      try {
    	  $organizacniVybor.closest(".form-item").find("span").remove();
    	  $organizacniVybor.select2();
      }
      catch(err) { }
      
      // Aktualizace polozek zpracovatele
      $zpracovatele.find("option").remove(); 
      
      for (var item in zpracovatele) {
        $zpracovatele.append("<option value=" + zpracovatele[item].value + ">" + zpracovatele[item].label + "</option>");
      }
      // Nastaveni polozky zpracovatele
      $zpracovatele.attr("disabled",false);
      $zpracovatele.find("option[value=" + zpracovatelId + "]")[0].selected = true;
    });
    
  };
});