<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/edit_.inc"));
require(FileUp2(".admin/config.inc")); //ost/posta
require(FileUp2(".config/config.inc"));
require(FileUp2(".admin/fce.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/javascript.inc"));


if (!$GLOBALS['omez_zarizeni']) {
  $GLOBALS['omez_zarizeni'] = 103;
  $_GET['omez_zarizeni'] = 103;
}

if (HasRole('spravce')) {
  $action = 'synchro.php';
  $add_hidden_variables = array(
    'cacheid' => '1',
  );

  include_once(FileUp2('.admin/brow_superodbor.inc'));
}
else {
  $GLOBALS['omez_zarizeni'] = EedTools::VratSuperOdbor();
}

  echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

  echo '<form method="GET" action="synchro.php">
  <input type="hidden" name="insert" >
  <input type="hidden" name="cacheid" value="1">
  <input type="hidden" name="omez_zarizeni" value="'.$GLOBALS['omez_zarizeni'].'">
  Hledání: <input type="text" name="jmeno" placeholder="Zadejte jméno" value="' . $_GET['jmeno'] . '">
  <input type="text" name="prijmeni" placeholder="Zadejte příjmení" value="' . $_GET['prijmeni'] . '">
  <input type="submit" value="Vyhledat pracovníky" class="btn">
  </form>';
  echo '</div></div></div>';

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
}

{
  $vytvorene = NactiVytvoreneSpisy($GLOBALS['omez_zarizeni'], 'Z');

  echo "<i>Z TESS načteno " . count($vytvorene) .  " záznamů</i><br/>";
  $find = array();
  if ($_GET['jmeno']) $find['jmeno'] = $_GET['jmeno'];
  if ($_GET['prijmeni']) $find['prijmeni'] = $_GET['prijmeni'];
  $pracovnici_whois = $GLOBALS['TMAPY_SECURITY_WHOIS']->GetPracovnici($GLOBALS['omez_zarizeni'], $find);
  echo "<i>Z WhoIS načteno " . count($pracovnici_whois) .  " záznamů</i><br/>";
  $pole = array_diff_key($pracovnici_whois, $vytvorene);


  include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  $db_arr = new DB_Sql_Array;
  //$db_arr->Data = $pracovnici_whois;
  $db_arr->Data = $pole;

  //print_r($pracovnici_whois);
  if (count($pracovnici_whois)>0) {
    Access(array("agenda"=>"POSTA"));
    $GLOBALS['ODBOR'] = 0;
    Form_(array(
      "showaccess" => true,
      "caption" => 'Založit typové spisy pod uživatele:',
      "showbuttons" => false,
    //  "nocaption" => true,
      ));
    Access(array(
      "agenda"=>"POSTA_PLUGINS_UK_STUDENT",
      ));

    $GLOBALS['REFERENT'] == 0;
    Table(
      array(
        "db_connector" => &$db_arr,
        "caption" => "Chybějící typové spisy pracovníků",
        "showaccess" => true,
        "appendwhere" => $where2,
        "showedit" => false,
        "page_size" => 100,
        "select_id" => "CISLO_UK",
        "showdelete" => false,
        "showselect" => true,
        "multipleselect" => true,
        "formvars" => array("ODBOR","REFERENT","TYPOVY_SPIS"),
        "showinfo" => false,
        "multipleselectsupport" => true
      )
    );

  }
  else {
    echo "<h1>Nejsou žádné nové typové spisy.</h1>";
  }
}
// } else {
//   echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
//
//   echo '<form method="GET" action="synchro.php?insert">
//   <input type="hidden" name="insert">
//   <input type="hidden" name="cacheid" value="1">
//   <input type="submit" value="Vyhledat pracovníky">
//   </form>';
//   echo '</div></div></div>';
// }


require(FileUp2("html_footer.inc"));
