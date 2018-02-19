/**
 *  Skript zajistuje podporu pro vyhledaveni - simple i all
 */


function ReplaceIDSpan() {
  document.getElementById('ID_span').innerHTML='<textarea name=\"ID_pole\" rows=5 cols=10></textarea>';
  document.frm_edit.ID_pole.focus();
  return false;
}

/** UkazOdbor */



function UkazOdbor(SODBOR,vysledek) {
  newwindow = window.open('/ost/posta/services/spisovka/oddeleni/get_value_odb.php?ODBOR='+SODBOR.value+'&vysledek='+vysledek+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function UkazPracovnika(ODBOR,vysledek) {
  newwindow = window.open('/ost/posta/services/spisovka/oddeleni/get_value_prac.php?ODBOR='+ODBOR.value+'&vysledek='+vysledek+'','ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}
