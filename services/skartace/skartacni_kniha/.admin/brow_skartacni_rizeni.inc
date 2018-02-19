<?php
  $q = new DB_POSTA;
  $sql = 'select * from posta_skartace where id='.$GLOBALS['SKARTACNI_RIZENI_ID'];
  $q->query($sql); $q->Next_Record();

  $sql_select=stripslashes($GLOBALS['TABLE_SELECT']);

  $show="<table width='100%'><td>   <div class=\"form dark-color\"> <div class=\"form-body\"> <div class=\"form-row\">";


  $show.="<form action='../../../brow.php?ID=".$q->Record['SPIS_ID']."' method='post'>";
  $show.="<input type='submit' name='' value='Zobrazit spis ".$q->Record['CJ']." v EED' class='btn'>";
  $show.="</form>";

  $show.="<table><tr><td><form action='../../../output/pdf/skartace.php' method='post' target=protokol><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='pismeno' value='S'>";
  $show.="<input type='submit' name='' value='Ukázat protokol pro S' class='btn'>";
  $show.="</form></td>";
  $show.="<td><form action='../../../output/pdf/skartace.php' method='post' target=protokol><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='pismeno' value='V'>";
  $show.="<input type='submit' name='' value='Ukázat protokol pro V' class='btn'>";
  $show.="</form></td>";
  $show.="<td><form action='../../../output/pdf/skartace.php' method='post' target=protokol><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='pismeno' value='A'>";
  $show.="<input type='submit' name='' value='Ukázat protokol pro A' class='btn'>";
  $show.="</form></tr></td></table>";

  $show.="<form action='rizeni_odeslat.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='skartacni_rizeni_id' value='".$GLOBALS['SKARTACNI_RIZENI_ID']."'>";
  $show.="<input type='submit' name='' value='Vytvořit žádost o provedení výběru archiválií' class='btn'>";
  $show.="</form>";

  if ($q->Record['DATUM_ODESLANI']) {


    $show.="<input type='button' onclick=\"NewWindowAgenda('edit.php?insert&app=import&SKARTACNI_RIZENI_ID=$SKARTACNI_RIZENI_ID');\" name='' value='Importovat výsledky z archivu' class='btn'>";
    $show.="</form>";

    $show.="<form action='rizeni_finalni.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="<input type='hidden' name='skartacni_rizeni_id' value='".$GLOBALS['SKARTACNI_RIZENI_ID']."'>";
    $show.="<input type='submit' name='' value='Vytvořit definitivní seznamy' class='btn'>";
    $show.="</form>";

//     $show.="<form action='skartace.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
//     $show.="<input type='submit' name='' value='Archivovat a skartovat' class='btn'></form>";

  }

  $show.="</td>";
  $show.="<td><p><span class='caption'>Odebrat dokumenty:</span>";
  $show.="<form action='rizeni_odebrat.php' method='post' onsubmit='insertIds(this);'><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='skartacni_rizeni_id' value='".$GLOBALS['SKARTACNI_RIZENI_ID']."'>";
  $show.="<input type='submit' name='' value='Odebrat ze skartačního řízení' class='btn'></p></form>";


  $show.="<table><tr><td><form action='../../../output/pdf/skartace.php' method='post' target=protokol onsubmit=''><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='submit' name='' value='Vytisknout protokol' class='btn'></form></td></tr>";
  if (HasRole('spisovna')||(HasRole('spisovna-odbor')&&$GLOBALS['CONFIG']['SPISOVNA_ODBOR_SMI_SKARTOVAT'])||HasRole('spravce')) {

    $show.="<tr><td><form action='sip_generate.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="<input type='submit' name='' value='Generovat SIP balíček pro rozhodnutí' class='btn'></form></td></tr>";

    $show.="<tr><td><form action='sip_generate.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="<input type='hidden' name='vcetne_priloh' value='1'>";
    $show.="<input type='hidden' name='typ' value='A'>";
    $show.="<input type='submit' name='' value='Generovat finální SIP balíček (jen A)' class='btn'></form></td></tr>";

    $show.="<tr><td><form action='soubory.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="<input type='hidden' name='typ' value='A'>";
    $show.="<input type='hidden' name='RIZENI_ID' value='" . $GLOBALS['SKARTACNI_RIZENI_ID'] . "'><input type='submit' name='' value='Vybrat soubory pro uchování' class='btn'></form></td></tr>";

    $show.="<tr><td><form action='skartace.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
    $show.="<input type='hidden' name='RIZENI_ID' value='" . $GLOBALS['SKARTACNI_RIZENI_ID'] . "'><input type='submit' name='' value='Archivovat a skartovat' class='btn'></form></td></tr>";


  }
  $show.="</td></tr></table>";

  $show.="</td></tr></table>";

  $show.="<form action='rizeni_ukoncit.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='hidden' name='skartacni_rizeni_id' value='".$GLOBALS['SKARTACNI_RIZENI_ID']."'>";
  $show.="<input type='submit' name='' value='Ukončit skartační řízení' class='btn'>";
  $show.="</form>";



IF (HasRole('spisovna-odbor')&&!$GLOBALS['CONFIG']['SPISOVNA_ODBOR_SMI_SKARTOVAT']) $show = '';