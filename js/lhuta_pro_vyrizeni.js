/**
 * Tyto funkce jsou pouzite ve formulari pri editaci a vkladani prichoziho dokumentu.
 * Pracuje se s poli LHUTA, LHUTA_VYRIZENI, DATUM_PODATELNA_PRIJETI a TYP_POSTY
 * @author mier
 */


/**
 * V IE7 a IE8 nema trida Array definovanou funkci indexOf.
 */
if (!Array.prototype.indexOf) {
  Array.prototype.indexOf = function (obj) {
    for (var i = 0; i < this.length; i++) {
      if (this[i] == obj) {
        return i;
      }
    }
    return -1;
  }
}


/**
 * V IE7 a IE8 nema trida String definovanou funkci trim.
 */
if(!String.prototype.trim) {
  String.prototype.trim = function () {
    return this.replace(/^\s+|\s+$/g,'');
  };
}


/**
 * @var holidays array Pole obsahujici datumy statnich svatku.
 */
var holidays = [
  '2012-01-21',
  '2012-05-22',
  '2011-11-24',
  '2012-07-16'
];


/**
 * Funkce na zklade hodnot v polich DATUM_PODATELNA_PRIJETI a LHUTA_VYRIZENI nastavi odpovidajici
 * hodnotu v poli LHUTA. Neboli zajisti prepocet poctu dnu (lhuta) na zaklade
 * datumu prijeti a pozadovaneho datumu vyrizeni. Je zavolana v pripade, ze je vyvolana
 * udalost onChange na poli LHUTA_VYRIZENI.
 * @param datumPrijetiField HTMLInputElement Formularovy prvek DATUM_PODATELNA_PRIJETI.
 * @param doDneField HTMLInputElement Formularovy prvek LHUTA_VYRIZENI.
 * @param lhutaField HTMLInputElement Formularovy prvek LHUTA.
 * @param holidays Array Pole datumu. Polozky pole jsou retezce ve formatu YYYY-MM-DD.
 */
var updateLhutaField = function (datumPrijetiField, doDneField, lhutaField, holidays) {
  
  return function () {
    
    var datumPrijeti = parseDate(datumPrijetiField.value, 'DD.MM.YYYY', ' ');
    var doDne = parseDate(doDneField.value, 'DD.MM.YYYY');


    
    if (!(isNaN(datumPrijeti) || isNaN(doDne))) {
     
      lhutaField.value = Math.round(daysDifference(doDne, datumPrijeti));
//      lhutaField.value = Math.round(daysDifference(doDne, datumPrijeti)) + 1;
    }
  }
}


/**
 * Funkce na zklade hodnot v polich DATUM_PODATELNA_PRIJETI a LHUTA nastavi odpovidajici
 * hodnotu v poli LHUTA_VYRIZENI. Neboli zajisti prepocet data (do dne) na zaklade
 * datumu prijeti a lhuty k vyrizeni. Je zavolana v pripade, ze je vyvolana
 * udalost onChange na poli DATUM_PODATELNA_PRIJETI nebo LHUTA.
 * @param datumPrijetiField HTMLInputElement Formularovy prvek DATUM_PODATELNA_PRIJETI.
 * @param doDneField HTMLInputElement Formularovy prvek LHUTA_VYRIZENI.
 * @param lhutaField HTMLInputElement Formularovy prvek LHUTA.
 * @param holidays Array Pole datumu. Polozky pole jsou retezce ve formatu YYYY-MM-DD.
 */
var updateDoDneField = function (datumPrijetiField, doDneField, lhutaField, holidays) {
  
  return function () {
    
    var datumPrijeti = parseDate(datumPrijetiField.value, 'DD.MM.YYYY', ' '); 
    var lhuta = parseInt(lhutaField.value);
    var color = 'black';

    if (!(isNaN(datumPrijeti) || isNaN(lhuta))) {
        
      var doDne = addDays(datumPrijeti, lhuta);
      var doDneString = getDateAsString(doDne, 'Y-M-D');
      
      if (isWeekend(doDneString) || isHoliday(doDneString, holidays)) {
        
        doDne = getNextWorkingDay(doDne, holidays);
        color = 'red';
      }
      
      doDneField.style.color = color;
      doDneField.value = getDateAsString(doDne, 'D.M.Y');
    }
  }
}


/**
 * Funkce vraci nasledujici pracovni den vzhledem k zadanemu datu.
 * @param date Date Datum, od ktereho se zacne hledat nasledujic pracovni den.
 * @param holidays Array Pole datumu. Polozky pole jsou retezce ve formatu YYYY-MM-DD.
 * @return Date Datum nejblizsiho pracovniho dne od zadaneho data.
 */
var getNextWorkingDay = function (date, holidays) {
  
  var dateString = getDateAsString(date, 'Y-M-D');
  
  while (isWeekend(dateString) || isHoliday(dateString, holidays)) {
    date = addDays(date, 1);
    dateString = getDateAsString(date, 'Y-M-D');
  }
  
  return date;
}


/**
 * Funkce oznaci dana formularova pole, pokud se je v dane datum svatek nebo vikend.
 * Pokud ne vrati barvu formularovych poli na puvodni hodnotu.
 * @param dateString string Datum ve formatu YYY-MM-DD.
 * @param holidays Array Pole datumu. Polozky pole jsou retezce ve formatu YYYY-MM-DD.
 * 
 */
var highlightNonWorkingDay = function (dateString, holidays, fields) {
  
  var color = 'black'; // Lepsi by byla hodnota 'inherit', ale IE7 ji nepodporuje.
  
  if (isWeekend(dateString) || isHoliday(dateString, holidays)) {
    color = 'red';
  }
  
  for (index in fields) {
    if (typeof fields[index] != 'function') {
      fields[index].style.color = color;
    }
  }
}


/**
 * Funkce pricte k danemu datumu dany pocete dni.
 * @param date Date Datum, ke kteremu se pricitaji dny.
 * @param daysCount int Pocet dni, ktere jsou pricteny k datumu.
 * @return Date Datum = datum + pocet dni
 */
var addDays = function (date, daysCount) {
  var miliseconds = daysCount * 24 * 60 * 60 * 1000;
  
  return new Date(date.valueOf() + miliseconds);
}


/**
 * Funkce zjisti pocet dnu mezi dvema datumy.
 * @param laterDate Date Pozdejsi datum.
 * @param earlierDate Date Drivejsi datum.
 * @return int Pocet dnu.
 */
var daysDifference = function (laterDate, earlierDate) {
  var dateDifference = laterDate - earlierDate;
  
  return dateDifference / (1000 * 60 * 60 * 24);
}


/**
 * Funkce prevodi objekt Date na retezec v danem formatu.
 * @param date Date Datum.
 * @param format string Format vystupniho retezce (napr.: Y-M-D, M.D.Y).
 * @return string Datum v textove podobe.
 */
var getDateAsString = function (date, format) {
  var year = date.getFullYear();
  var month = date.getMonth() + 1;
  var day = date.getDate();
  
  // Add leading zero
  month = ('0' + month).slice(-2);
  day = ('0' + day).slice(-2);
  
  var dateString = format;
  
  dateString = dateString.replace('D', day, 'gi');
  dateString = dateString.replace('M', month, 'gi');
  dateString = dateString.replace('Y', year, 'gi');
  
  return dateString;
}


/**
 * Funkce zjisti, zda je v zadany datum vikend.
 * @param dateString string Datum ve formatu YYYY-MM-DD.
 * @return bool Kdyz je v dany datum vikend pak true, jinak false.
 */
var isWeekend = function (dateString) {
  var date = parseDate(dateString, 'YYYY-MM-DD');
  var dayOfWeek = date.getDay();
  
  return dayOfWeek == 0 || dayOfWeek == 6 ? true : false;
}


/**
 * Funkce zjisti, zda je v zadany datum svatek.
 * @param dateString string Datum ve formatu YYYY-MM-DD.
 * @param holidays Array Pole datumu. Polozky pole jsou retezce ve formatu YYYY-MM-DD.
 * @return bool Kdyz je v dany datum svatek pak true, jinak false.
 */
var isHoliday = function (dateString, holidays) {
  return holidays.indexOf(dateString) >= 0 ? true : false;
}


/**
 * Funkce prevede datum z textoveho retezce na objekt Date.
 * Pokud datum obsahuje i casovou slozku, tak je tato slozka zahozena.
 * @param dateTimeString string Datum ve formatu D.M.YYYY.
 * @param parseType[DD.MM.YYYY | YYYY-MM-DD] string Oznacuje zpusob parsovani rertezce.
 * @param dateTimeSeparator[optional] string Oddelovac datumu a casu.
 * @return Date Datum jako objekt Date.
 */
var parseDate = function (dateTimeString, parseType, dateTimeSeparator) {
  dateTimeString = dateTimeString.trim();
  var date = null;
  var dateParts = null;
  
  // Pokud retezec dateTimeString obsahuje datum i cas, ziskame pouze datum:
  if (dateTimeSeparator) {
    var dateTimeSeparatorIndex = dateTimeString.indexOf(dateTimeSeparator);
    var dateString = dateTimeString.substring(0, dateTimeSeparatorIndex);
  }
  else {
    dateString = dateTimeString;
  }
  
  switch (parseType) {
    
    case 'DD.MM.YYYY':
      dateParts = dateString.split('.');
      date = new Date(dateParts[2], (dateParts[1] - 1), dateParts[0]);
      break;
      
    case 'YYYY-MM-DD':
      dateParts = dateString.split('-');
      date = new Date(dateParts[0], (dateParts[1] - 1), dateParts[2]);
      break;
      
    default:
      console.log('Function: parseDate(), bad value of parameter parseType' + parseType);    
  }
  
  return date;
}

/**
 * Funkce zajistuje registraci listeneru.
 */
var listenersRegistration = function () {
  
  var datumPrijetiField = document.frm_edit.DATUM_PODATELNA_PRIJETI;
  var doDneField = document.frm_edit.LHUTA_VYRIZENI;
  var lhutaField = document.frm_edit.LHUTA;
  var typPostyField = document.frm_edit.TYP_POSTY;

  if (window.addEventListener) {
    lhutaField.addEventListener('blur', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays), false);
    datumPrijetiField.addEventListener('blur', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays), false);
    doDneField.addEventListener('blur', updateLhutaField(datumPrijetiField, doDneField, lhutaField, holidays), false);
    typPostyField.addEventListener('change', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays), false);

    var odeslat = document.frm_edit.__;
    odeslat.addEventListener("click",updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays),false);
    odeslat.addEventListener("click",updateLhutaField(datumPrijetiField, doDneField, lhutaField, holidays),false);


  }
  else if (window.attachEvent) {
    lhutaField.attachEvent('onblur', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays));
    datumPrijetiField.attachEvent('onblur', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays));
    doDneField.attachEvent('onblur', updateLhutaField(datumPrijetiField, doDneField, lhutaField, holidays));
    typPostyField.attachEvent('onchange', updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays));

    var odeslat = document.frm_edit.__;
    odeslat.addEventListener("click",updateDoDneField(datumPrijetiField, doDneField, lhutaField, holidays),false);
    odeslat.addEventListener("click",updateLhutaField(datumPrijetiField, doDneField, lhutaField, holidays),false);

  }  
}

/**
 * Spusteni registrace listeneru po nacteni stranky.
 */
if (window.addEventListener) {
  window.addEventListener('load', listenersRegistration, false);
}
else if (window.attachEvent) {
  window.attachEvent('onload', listenersRegistration);
} 