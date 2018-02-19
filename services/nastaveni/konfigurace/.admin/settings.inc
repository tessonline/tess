<?php

$settings=array(
  1=>array('name'=>'Nastavení jednacího čísla'),
  2=>array('name'=>'Zrušení storna u dokumentu'),
  3=>array('name'=>'Převod dokumentů na jiného zpracovatele'),
);

$settings[1][krok][1]='


 $sql="select * from posta_cislo_jednaci_seq";
 $q->query($sql); $q->Next_Record(); $cislo_jednaci=$q->Record[LAST_VALUE];
 if ($cislo_jednaci==1) $cj_text=1; else $cj_text=$cislo_jednaci+1;
 echo "Připravené číslo jednací pro další dokument je <b>".($cj_text)."</b><br/><br/>";

 echo "<div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">";
 echo "Nová hodnota*: <input type=text name=new_cj size=4 value=$cislo_jednaci><br/>
  <i>*) - Nastavte hodnotu, kterou dostane další dokument. ";
 echo "</div></div></div>";
';

$settings[1][krok][2]='
 $new_cj=$new_cj-1;
 if ($new_cj==0)
   $sql="drop sequence posta_cislo_jednaci_seq; CREATE SEQUENCE posta_cislo_jednaci_seq START 1 INCREMENT 1 MAXVALUE 2147483647 MINVALUE 1 CACHE 1;";
  else
   $sql="SELECT setval(\'posta_cislo_jednaci_seq\', $new_cj); COMMIT;";
  if ($q->query($sql)) echo "<span class=caption>Hodnota čj nastavena</span>"; 
 
';

$settings[2][krok][1]='
 echo "<p>Zadejte identifikátor ID dokumentu, který má být vrácen zpět do ostrého provozu:</p>";
 echo "<div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">";

 echo "ID dokumentu: <input type=text name=storno_id size=10 value=\"\" class=text>";
 echo "</div></div></div>";
';

$settings[2][krok][2]='
  if (!$storno_id) $storno_id=0;
  $sql="select stornovano from posta where id=".$storno_id;
  $q->query($sql);
  if ($q->Num_Rows()==0) 
  {
    echo "<span class=error>Dokument nenalezen!!!</span>";
    $storno_id=0;
  }
  else
  {
    $q->Next_Record();
    echo "<p>LOG: Dokument ID ".$storno_id." - ".$q->Record[STORNOVANO]."</p>";
    echo "<p>Kliknutím na Další zrušíte skutečně storno dokumentu.</p>";
    echo "<input type=hidden name=provest_ano value=1>";
    echo "<input type=hidden name=storno_id value=$storno_id>";
  }
';

$settings[2][krok][3]='
  if ($storno_id==0) echo "<script>document.location.href=\'settings.php\';</script>";
  if ($provest_ano) {
    $sql="select status from posta_h where id=".$storno_id." order by id desc";
    $q->query($sql); $q->Next_Record();
    $status = $q->Record[STATUS] ? $q->Record[STATUS] : 0;

    $sql="update posta set stornovano=NULL,status=$status,$add_info where id=".$storno_id;
    NastavStatus($storno_id, $OWNER_ID);
    $text = "Dne <b>".Date(\'d.m.Y\')."</b> v <b>".Date(\'H:i:s\')."</b> uživatel <b>$jmeno</b> obnovil tento záznam. ";
    EedTransakce::ZapisLog($storno_id, $text, \'DOC\', $id_user);
    if ($q->query($sql)) echo "<span class=caption>Dokument byl vrácen zpět</span>";
    else   echo "<span class=caption>Nastala chyba v databázi</span>";
  }
  
';

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$sql_add = "";
if (!HasRole('spravce')) 
  $sql_add = " WHERE pracoviste=".$USER_INFO["PRACOVISTE"]." ";


if (eregi('ceu',$GLOBALS['SERVER_CONFIG']['SECURITY']['AUTH_TYPE'])) {

  $settings[3][krok][1]='
    $db = new DB_POSTA;
    $sql = "select * from security_user '.$sql_add.' order by lname, fname asc";
    $db->query($sql);
    while ($db->Next_Record()) $users[logins][] = array(ID=>$db->Record[ID], LNAME=>$db->Record[LNAME] . " " . $db->Record[FNAME], SHORT =>$db->Record[LOGIN_NAME]);
    echo "<div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">";
    echo "<p><table><tr><td>Vyberte <b>původního</b> zpracovatele: ";
    echo "</td><td><select name=puvodni_referent>";
    foreach ($users["logins"] as $user) {
      echo "<option value=$user[ID]>$user[LNAME] ($user[SHORT])</option>";
    }
    echo "</select></td></tr>";
    echo "<tr><td>Vyberte <b>nového</b> zpracovatele: ";
    echo "</td><td><select name=novy_referent>";
    foreach ($users["logins"] as $user) {
      echo "<option value=$user[ID]>$user[LNAME] ($user[SHORT])</option>";
    }
    echo "</select></td></tr>";
    echo "</div></div></div>";

  ';
  
}
else {
  
  $settings[3][krok][1]='
    $db = new DB_POSTA;
    $sql = "select * from security_user '.$sql_add.' order by lname, fname asc";
    $db->query($sql);
    while ($db->Next_Record()) $users[] = array(ID=>$q->Record[ID], LNAME=>$q->Record[FNAME] . " " . $q->Record[LNAME], SHORT =>$q->Record[LOGIN]);
    echo "<p><table><tr><td>Vyberte <b>původního</b> zpracovatele: ";
    echo "</td><td><select name=puvodni_referent>";
    while (list($key,$val)=each($users))
      echo "<option value=$key>$val[1] ($val[0])</option>";
    echo "</select></td></tr>";
    reset($users);
    echo "<tr><td>Vyberte <b>nového</b> zpracovatele: ";
    echo "</td><td><select name=novy_referent>";
    while (list($key,$val)=each($users))
      echo "<option value=$key>$val[1] ($val[0])</option>";
    echo "</select></td></tr>";  
';

}

$settings[3][krok][1] .= '
  echo "  <tr>";
  echo "    <td>Datum od:</td>";
  echo "    <td><input type=\"text\" name=\"datum_od\" maxlength=\"10\" size=\"11\"> [d.m.yyyy]</td>";
  echo "  </tr>";
  echo "  <tr>";
  echo "    <td>Datum do:</td>";
  echo "    <td><input type=\"text\" name=\"datum_do\" maxlength=\"10\" size=\"11\"> [d.m.yyyy]</td>";
  echo "  </tr>";
  echo "</table></p>";
  ';

// Pridani podminky, ktere vyhovi pouze dokumenty, ktere byly prijaty v danem obdobi
$datum_od = $GLOBALS['datum_od'] ? htmlspecialchars(addslashes($GLOBALS['datum_od'])) : '';
$datum_do = $GLOBALS['datum_do'] ? htmlspecialchars(addslashes($GLOBALS['datum_do'])) : '';
$where = '';

switch ($GLOBALS['CONFIG']['DB']) {
  
  case 'psql':
    $where .= " AND (DATUM_PODATELNA_PRIJETI ) >=
                ('$datum_od' )";
    $where .= " AND (DATUM_PODATELNA_PRIJETI) <=
                ('$datum_do')";
    break;
  
  case 'mssql':
    $where .= " AND CONVERT(datetime, datum_podatelna_prijeti, 104) >=
                CONVERT(datetime, '$datum_od', 104)";
    $where .= " AND CONVERT(datetime, datum_podatelna_prijeti, 104) <=
                CONVERT(datetime, '$datum_do', 104)";
    break;
  
}

$settings[3][krok][2]='
  $odbor_puv = OdborPrac($puvodni_referent);
  $odbor_nov = OdborPrac($novy_referent);
  
  $sql_rozpracovane = "SELECT * FROM posta WHERE referent IN ($puvodni_referent) AND status > 1 $where";
  $q->query($sql_rozpracovane);
  $pocet_rozpracovanych = $q->Num_Rows();
  
  $sql_vsechny = "SELECT * FROM posta WHERE referent IN ($puvodni_referent) AND status > 0 $where";
  $q->query($sql_vsechny);
  $pocet_vsechny = $q->Num_Rows();
  
  $sql_uzavrene = "SELECT * FROM posta WHERE referent IN ($puvodni_referent) AND status = 1 $where";
  $q->query($sql_uzavrene);
  $pocet_uzavrenych = $q->Num_Rows();
  
  echo "<p>";
  echo "<span class=caption>Nalezeno:</span><br />";
  
  echo "<b>$pocet_rozpracovanych</b> rozpracovaných dokumentů (a spisů)<br />";
  echo "<b>$pocet_uzavrenych</b> uzavřených dokumentů (a spisů)<br />";
  echo "<b>$pocet_vsechny</b> celkem dokumentů (i uzavřených)<br />";
  echo "</p>";

  echo "<p>";
    echo "<div class=\"form darkest-color\"> <div class=\"form-body\"> <div class=\"form-row\">";
  echo "<span class=caption>Bude převedeno:</span><br />";
  
  echo "Od zpracovatele: <b>" . UkazUsera($puvodni_referent) . ", " . UkazOdbor($odbor_puv[odbor]) .
        ($odbor_puv[oddeleni] > 0 ? ", " . UkazOdbor($odbor_puv[oddeleni]) : "") . "</b><br />";
  echo "Na zpracovatele: <b>" . UkazUsera($novy_referent) . ", " . UkazOdbor($odbor_nov[odbor]) . 
        ($odbor_nov[oddeleni] > 0 ? ", " . UkazOdbor($odbor_nov[oddeleni]) : "") . "</b><br />";
  if ($datum_od || $datum_do) echo "V období: ";
  if ($datum_od) echo "od $datum_od ";
  if ($datum_do) echo "do $datum_do";
  if ($datum_od || $datum_do) echo "<br />";
  echo "Převést: ";
  echo "<select name=vybrano>";
  echo "  <option value=1>všechny dokumenty</option>";
  echo "  <option value=2>jen rozpracované dokumenty a spisy</option>";
  echo "  <option value=3>jen uzavřené dokumenty a spisy</option>";
  echo "</select>";
  echo "</p>";
    echo "</div></div></div>";

  echo "<input type=hidden name=puvodni_referent value=$puvodni_referent>";
  echo "<input type=hidden name=novy_referent value=$novy_referent>";
  echo "<input type=hidden name=datum_od value=$datum_od>";
  echo "<input type=hidden name=datum_do value=$datum_do>";
';

$settings[3][krok][3]='
  $odbor_puv = OdborPrac($novy_referent);
  $odbor = $odbor_puv[odbor];
  $oddeleni = $odbor_puv[oddeleni];
    
  switch ($vybrano) {
  
    case 1:
                $statusWhere = "status > 0 $where";
      break;
      
    case 2:
                $statusWhere = "status > 1 $where";
      break;
      
    case 3:
                $statusWhere = "status = 1 $where";
      break;
  }
  
  $data = array();
  $chyba = false;  
  $sql = "SELECT id FROM posta where referent = $puvodni_referent AND ".$statusWhere;
  $qi = new DB_POSTA();
  $q->query($sql);
  while ($q->Next_Record()) {
    $id = $q->Record["ID"];
    $sql = "UPDATE posta SET referent = $novy_referent,
                    odbor = $odbor,
                    oddeleni = \'$oddeleni\',
                    $add_info
                WHERE id=".$id;
    if (!$qi->query($sql)) $chyba=true;
    $cjObj = LoadClass(\'EedCj\', $id);
    $cj = $cjObj->cislo_jednaci;
    $vec = $cjObj->vec;
    $data[] = array(\'ID\' => $id, \'CJ\' => $cj, \'VEC\' => $vec);        
    $text = "dokument ".$id." byl převeden ze zpracovatele <b>".UkazUsera($puvodni_referent)."</b> (".$puvodni_referent.") na zpracovatele <b>".UkazUsera($novy_referent)."</b> (".$novy_referent.")";
    EedTransakce::ZapisLog($id, $text, \'DOC\', $id_user);
  }
  $pdf=new PDF_Predani("P","mm","A4", true, "UTF-8", true, true);
  $pdf->z = UkazUsera($puvodni_referent)." (".$puvodni_referent.")";
  $pdf->na = UkazUsera($novy_referent)." (".$novy_referent.")";
  $pdf->generovatPDF($data);
  $filename = \'protokol-\' . date(\'Ymdhis\').\'.pdf\';    
  $file = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$filename;
  $pdf->Output($file,\'F\');
  //echo $sql;
  if (!$chyba)
    echo "<p class=caption>Dokumenty převedeny.</p>";
  else 
    echo "<p class=caption>Nastala chyba v databázi</p>";
    
  echo TxtEncodingFromSoap("Vytvořen soubor $filename. <a href=\'getfile.php?file=$filename\'>Klikněte pro jeho stažení</a>.");
  require_once(Fileup2("html_footer.inc"));
  die();
';



/*
 $sql="select * from posta_cislo_jednaci_seq";

*/
