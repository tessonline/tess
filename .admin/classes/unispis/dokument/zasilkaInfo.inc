<?php

/**
 * trida pro identifikaci Zasilky
 *
 * @author onma
 */
class zasilkaInfo {
  /** vyjadřuje, jakým způsobem byl dokumentu doručen
   *  
   *  Posta|Osobne|VerejnaVyhlaska|DetasovanaPosta|Kuryr|DorucovaciSluzba|ElektronickaPosta|
   *  Fax|DalnopisTelegram|Telefon|UstneDoProtokolu|EPodatelnaNosic|EPodatelnaWeb|EPodatelnaMail|
   *  EPodatelnaMailElPodpis|Rep|DatovaSchranka
   */
  var $ZpusobManipulaceId;
  /** vyjadřuje způsob zacházení se zásilkou nesoucí daný dokument
   *
   *  BezDoplnkoveSluzby|Dodejka|DodejkaModra|DodejkaCervena|Dodejka3D|
   *  DodejkaModra3D|DodejkaCervena3D|Dodejka10D|DodejkaModra10D|DodejkaCervena10D|
   *  Dodejka1M|DodejkaModra1M|DodejkaCervena1M
   */
  var $ZpusobZachazeniId;
  /** vyjadřuje jakým druhem zásilky byl daný dokument doručen
   *  Balik|CennePsani|CennyBalik|Psani|SlepeckaZasilka|PsaniStandard
   */
  var $DruhZasilkyId;
  /** datum, kdy byl dokument vypraven (odeslan) */
  var $DatumVypraveni;
  /** identifikace stavu odeslani zasilky 
   *  nevypraveno|vypraveno|doruceno */
  var $StavZasilky;
  /** identifikator zasilky, nejcasteji carovy kod */
  var $IdZasilky;
  /** odkazy na soubory, které jsou spojeny s dokumentem nebo spisem */
  var $OdkazyNaSoubory;
  /** ID datové zprávy */
  var $dmID;
  /** datum, kdy byl dokument dorucen (dodan) */
  var $DatumDoruceni;
  
  /**
  * konstruktor 
  *
  * @param array $zmocneni pole pro naplneni 
    */ 
  public function __construct($zasilka) {  
    $this->ZpusobManipulaceId = ($zasilka['ZpusobManipulaceId']);
    $this->ZpusobZachazeniId = ($zasilka['ZpusobZachazeniId']);
    $this->DruhZasilkyId = ($zasilka['DruhZasilkyId']);
    $this->DatumVypraveni = ($zasilka['DatumVypraveni']);
    $this->StavZasilky = ($zasilka['StavZasilky']);
    $this->IdZasilky = ($zasilka['IdZasilky']);
    $this->OdkazyNaSoubory = ($zasilka['OdkazyNaSoubory']);
    $this->dmID = ($zasilka['dmID']);
    $this->DatumDoruceni = ($zasilka['DatumDoruceni']);
  }

}
