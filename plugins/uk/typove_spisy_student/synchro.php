<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/edit_.inc"));
require(FileUp2(".admin/config.inc")); //ost/posta
require(FileUp2(".config/config.inc"));
require(FileUp2(".admin/fce.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/javascript.inc"));

$action = 'synchro.php?insert&cacheid=&';
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

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']){ ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
}

  $studia = $GLOBALS["TMAPY_SECURITY_WHOIS"]->getTypStudia();
  $obor = $GLOBALS["TMAPY_SECURITY_WHOIS"]->getOborStudia();


  echo '<form method="GET" action="synchro.php">
  <input type="hidden" name="insert" >
  <input type="hidden" name="cacheid" value="1">
  <input type="hidden" name="omez_zarizeni" value="'.$GLOBALS['omez_zarizeni'].'">

  Vyberte druh studia:<select name="omez_typ" style="width:200px">
';
  //echo <option value="">vše</option> //nelze vyhledavat podle vseho, co kdyz ma aktivni dva obory (doktorske + bakalarske treba)
  foreach($studia as $key => $val)
    echo '<option value="' . $key . '" ' . ($_GET['omez_typ'] == $key ? 'SELECTED':'') . '>' . $val . '</option>';

  echo '
  </select>
  a případně obor studia:<select name="omez_obor" class="js-omez-odbor">
';
  echo '<option value="">vše</option>';
  foreach($obor as $key => $val)
    echo '<option value="' . $key . '" ' . ($_GET['omez_obor'] == $key ? 'SELECTED':'') . '>'.$key.' - ' . $val . '</option>';

  echo '
  </select>
  <br/>nebo:<br/><input type="text" name="jmeno" placeholder="Zadejte jméno" value="' . $_GET['jmeno'] . '">
  <input type="text" name="prijmeni" placeholder="Zadejte příjmení" value="' . $_GET['prijmeni'] . '">
  <input type="text" name="cislo" placeholder="Zadejte WhoIS číslo" value="' . $_GET['cislo'] . '">
  <input type="submit" value="Vyhledat studenty" class="btn">
  </form>';

echo "
<script>
$(document).ready(function() {
    $('.js-omez-odbor').select2();
});
</script>

";

  echo '</div></div></div>';


if (isset($_GET['omez_typ'])) {
  $vytvorene = NactiVytvoreneSpisy($GLOBALS['omez_zarizeni'], 'S');

  echo "<i>Z TESS načteno " . count($vytvorene) .  " záznamů</i><br/>";
  $find = array();
  if ($_GET['jmeno']) $find['jmeno'] = $_GET['jmeno'];
  if ($_GET['prijmeni']) $find['prijmeni'] = $_GET['prijmeni'];
  if ($_GET['omez_typ']) $find['omez_typ'] = $_GET['omez_typ'];
  if ($_GET['omez_obor']) $find['omez_obor'] = $_GET['omez_obor'];
  if ($_GET['cislo']) $find['cislo_uk'] = $_GET['cislo'];
  $studenti_whois = $GLOBALS['TMAPY_SECURITY_WHOIS']->GetStudents($GLOBALS['omez_zarizeni'], $find);
  echo "<i>Z WhoIS načteno " . count($studenti_whois) .  " záznamů</i><br/>";

//print_r($studenti_whois);
//print_r($vytvorene);
  $pole = array_diff_key($studenti_whois, $vytvorene);


  include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  $db_arr = new DB_Sql_Array;
  //$db_arr->Data = $studenti_whois;
  $db_arr->Data = $pole;

  //print_r($studenti_whois);
  if (count($studenti_whois)>0) {
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
        "caption" => "Chybějící typové spisy studentů",
        "showaccess" => true,
        "appendwhere" => $where2,
        "showedit" => false,
        "page_size" => 10000,
        "select_id" => "STUD_ID",
        "showdelete" => false,
        "showselect" => true,
        "multipleselect" => true,
        "formvars" => array("ODBOR","REFERENT","TYPOVY_SPIS","TYP_STUDIA"),
        "showinfo" => false,
        "multipleselectsupport" => true,
        "form_method" => "POST",
      )
    );

  }
  else {
    echo "<h1>Nejsou žádné nové typové spisy.</h1>";
  }
} else {
  echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
/*
  echo '<form method="GET" action="synchro.php?insert">
  <input type="hidden" name="insert">
  <input type="hidden" name="cacheid" value="1">
  <input type="submit" value="Vyhledat studenty">
  </form>';
  echo '</div></div></div>';
*/
}


require(FileUp2("html_footer.inc"));
