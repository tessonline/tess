<?php
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$EedUser = LoadClass('EedUser', $USER_INFO['ID']);
$EedSql = LoadClass('EedSql');

$unit_id = $EedUser->odbor_id;
$user_id = $EedUser->id_user;

Access();

if (! HasRole('pristup')&&(!isset($GLOBALS['ZAKAZ_ROZSIRENI_VIDITELNOSTI']))){
  
  $text = 'EED se snažil pustit uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user . '), který nemá právo pristup do EED';
  EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
  echo '<h1>CHYBA:</h1><p>Váš účet nemá povolen přístup do ESS.</p>';
  require (FileUp2('html_footer.inc'));
  Die();
}

$pristup_prava = false;

if (HasRole('cteni_admin')){
  $where = "  ";
  $pristup_prava = true;
}

If (HasRole('cteni_zpracovatel') || HasRole('cteni_vse_pracoviste') || HasRole('cteni_uzel')){
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $uzel_id = VratOdbor();
  $pristupy[] = $USER_INFO["ID"];
  $unity = $USER_INFO['GROUP_ID'];
  $odbory = array();
  $podrizene_unity = $EedUser->VratNadrizeneUnity($unity);
  foreach ($podrizene_unity as $unita => $val){
    $temp = $EedUser->VratSpisUzelZOdboru($unita);
    if ($temp['ID'] > 0)
      $odbory[] = $temp['ID'];
  }
  $so = $EedUser->VratSpisUzelZOdboru($USER_INFO["PRACOVISTE"]);
  if ($so>0)
    $odbory[] = $so['ID'];
}

$rozsireni_viditelnosti = "";
if ((! isset($GLOBALS['ZAKAZ_ROZSIRENI_VIDITELNOSTI']))
    &&
   (HasRole('cteni_vse_pracoviste')
       ||HasRole('cteni_uzel')
       ||(HasRole('cteni_zpracovatel')&&!HasRole('omezeni-zpracovatele'))))
{
  if (count($odbory) == 0) $odbory[] = '-1';
  $rozsireni_viditelnosti = " OR exists (select posta_id from posta_pristupy where p.id=posta_pristupy.posta_id AND (referent=" . $USER_INFO['ID'] . " or (odbor in (" . implode(',', $odbory) . ")) and (referent is null or referent=0)))";
}

if (HasRole('cteni_vse_pracoviste')){
  // tak ukazeme pouze jedno pracoviste.
  // $where=" AND ((superodbor in (" . EedTools::VratSuperOdbor() . ") OR exists (select posta_id from posta_pristupy where p.id=posta_pristupy.posta_id AND (referent=".$USER_INFO['ID']." or odbor in (" . implode(',', $odbory). ")))))";
  $where = " AND ((superodbor in (" . EedTools::VratSuperOdbor() . ") " . $rozsireni_viditelnosti . "))";

  //zlobilo ve vyhledavani dle referenta
  $getAdd = $_GET['_twScrollTo'];
  if ($_GET['ORDER_BYdenik'] == 'o.zkratka asc,lname asc,fname asc' || $_GET['ORDER_BYdenik'] == 'o.zkratka desc,lname desc,fname desc' || $_GET['ORDER_BY'.$getAdd] == 'o.zkratka asc,lname asc,fname asc' || $_GET['ORDER_BY'.$getAdd] == 'o.zkratka desc,lname desc,fname desc')
    $where = " AND ((p.superodbor in (" . EedTools::VratSuperOdbor() . ") " . $rozsireni_viditelnosti . "))";

  $pristup_prava = true;
}

// fuknce pro upravu prav....
if (HasRole('cteni_uzel')){
  // tak ukazeme pouze jeden odbor.
  $uzel_id = VratOdbor();
  $EedSql = LoadClass('EedSql');
  // nacteme sql podminku pouze z unit_id, protoze jsou uzivatele, kteri nejsou ve spisovem uzlu
  if (! $where_app = $EedSql->WhereOdborAndPrac($uzel_id)){
    // prisel uzivatel, ktery nema spravne zadany odbor
    echo '<h1>CHYBA:</h1><p>Váš účet se nepovedlo lokalizovat v organizační struktuře organizace. Prosím požádejte Vašeho správce aplikace o opravu.</p>';
    $text = 'EED nenašla org. strukturu pro uživatele <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user . ')';
    EedTransakce::ZapisLog(0, $text, 'SYS', $user_id);
    require (FileUp2('html_footer.inc'));
    Die();
  }
  // nacteme sql podminku pouze z unit_id, protoze jsou uzivatele, kteri nejsou ve spisovem uzlu
  // $where_app = "(1=0) "; //a opet jsem to musel vypnout, protoze se nenacitali zpracovatele z poduzlu...
  if ($EedUser->VratSpisUzelZOdboru($unit_id) || HasRole('zpracovat-odbor')){
    $where .= " AND ((" . $where_app . " OR odbor in (" . $uzel_id . "))";
  }
  else
    $where .= " AND ((" . $where_app . " or referent=" . $USER_INFO['ID'] . ")";
  
  $odbor_pole = array();
  $odbor_pole[] = - 1; // aby nedoslo k sql chybe
  
  If (is_array($GLOBALS[CONFIG][UZIVATEL_PRAVA][$referenta]))
    $where = " AND ODBOR IN (" . $odbor_pole . "," . implode(', ', $GLOBALS[CONFIG][UZIVATEL_PRAVA][$referenta]) . ") ";
  $pristup_prava = true;
  // $where .= " OR exists (select posta_id from posta_pristupy where p.id=posta_pristupy.posta_id AND (referent=".$USER_INFO['ID']." or odbor in (" . implode(',', $odbory). "))))";
  $where .= $rozsireni_viditelnosti . " )";
}

$jen_zpracovatel = false;
// If (!(HasRole('spravce')||HasRole('podatelna')||HasRole('spisovna')||HasRole('spisovna-odbor')||HasRole('podatelna-odbor')) && (HasRole('zpracovatel'))) {
If ((HasRole('cteni_zpracovatel'))){
  if (HasRole('omezeni-zpracovatele')){
    $where .= " AND (referent=" . $USER_INFO['ID'] . " OR (odbor in (" . $uzel_id . ") and referent is null))";
  }
  else
    $where .= " AND ((referent=" . $USER_INFO['ID'] . ") " . $rozsireni_viditelnosti . ")";
    // $where.= " AND ((referent=".$USER_INFO['ID'].") OR exists (select posta_id from posta_pristupy where p.id=posta_pristupy.posta_id AND (referent=".$USER_INFO['ID']." or odbor in (" . implode(',', $odbory). "))))";
    // $where.= " AND (referent=".$USER_INFO['ID'].")";
  
  $jen_zpracovatel = true;
  $pristup_prava = true;
}

If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"])
  $where_prichozi = " AND (datum_predani is not null and odeslana_posta='f')";
If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"])
  $where_odchozi = " AND (datum_predani_ven is null and odeslana_posta='t')";

if ($PROPERTIES['AGENDA_IDENT'] == 'SKARTACNI_KNIHA')
  $pristup_prava = true;

if (isset($GLOBALS['ZAKAZ_ROZSIRENI_VIDITELNOSTI']))
  $pristup_prava = true;

if (! $pristup_prava){
  $text = 'EED se snažil pustit uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user . '), který nemá přiděleny práva na EED';
  EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
  echo '<h1>CHYBA:</h1><p>Váš účet nemá povolen přístup pro čtení do ESS.</p>';
  require (FileUp2('html_footer.inc'));
  Die();
}

