<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header.inc"));
require(FileUp2(".admin/config.inc"));

require_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//print_r($GLOBALS);
//print_r($GLOBALS["SELECT_IDposta"]);
if (!$GLOBALS["SELECT_IDposta"]) {
  echo "Nebyly vybrány žádné záznamy k přesunu z historie!";
  die();
  require(FileUp2("html_footer.inc"));
}
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
//print_r($USER_INFO);
if (!$USER_INFO["ID"]) {
  echo "Nelze provést!";
  require(FileUp2("html_footer.inc"));
  die();
} 

$retezec = implode(",",$GLOBALS["SELECT_IDposta"]);
//$pole_uniq = array_unique($GLOBALS["SELECT_IDposta"]);
if (count($GLOBALS["SELECT_IDposta"]) != count(array_unique($GLOBALS["SELECT_IDposta"]))) {
  echo "
    <center>
    <br />
    <b>Ve výběru existují duplicitní záznamy, které nelze přesunout zpět!</b><br /><br />
    <form>
      <input name='__x' value='  Zpět  ' type='button' class='button btn' onclick='javascript:history.go(-1)'>
    </form>
    </center>
  ";
  require(FileUp2("html_footer.inc"));
  die();
}
$r = new DB_default;
$r -> Error_Die = true;
$r -> ShowError = true;

$select1 = "
  select count(*) as pocet
  from posta
  where id in (".$retezec.")
";
$r->query($select1);
$r->next_record();
$pocet = $r->Record["POCET"];
//echo $select1."<br />".$pocet." ****<br />$retezec";
if ($pocet != "0") {
  echo "
    <center>
    <br />
    Ve výběru existuje <b>".$pocet."</b> záznamů, které nelze přesunout zpět!<br /><br />
    <form>
      <input name='__x' value='  Zpět  ' type='button' class='button btn' onclick='javascript:history.go(-1)'>
    </form>
    </center>
  ";
  require(FileUp2("html_footer.inc"));
  die();
}

$insert = "
  insert into posta
  select * from posta_stare_zaznamy
  where id in (".$retezec.")
";
if ($r->query($insert)) {
  $insert_mess = true;
  $insert_h = "
    insert into posta_h
    select * from posta_stare_zaznamy_h
    where id in (".$retezec.")
  ";
  if ($r->query($insert_h)) {
    $insert_h_mess = true;
    $update = "
      update posta set
      last_date = current_date,
      last_time = current_time,
      last_user_id = ".$USER_INFO["ID"]."
      where id in (".$retezec.")
    ";
    if ($r->query($update))
      $update_mess = true;
    $delete_h = "delete from posta_stare_zaznamy_h where id in (".$retezec.")";
    if ($r->query($delete_h))
      $delete_h_mess = true;
  }
  $delete = "delete from posta_stare_zaznamy where id in (".$retezec.")";
  if ($r->query($delete))
    $delete_mess = true;
}
if (!$insert_mess) $insert_ne = "ne";
if (!$insert_h_mess) $$insert_h_ne = "ne";
if (!$update_mess) $update_ne = "ne";
if (!$delete_mess) $delete_ne = "ne";
if (!$delete_h_mess) $delete_h_ne = "ne";

echo "<b>Kopírování z následné historie(1) se ".$insert_ne."zdařilo.</b><br />";
echo "<b>Kopírování z následné historie(2) se ".$$insert_h_ne."zdařilo.</b><br />";
echo "<b>Nastavení uživatele se ".$update_ne."zdařilo.</b><br />";
echo "<b>Následné vymazání z historické tabulky(1) se ".$delete_ne."zdařilo.</b><br />";
echo "<b>Následné vymazání z historické tabulky(2) se ".$delete_h_ne."zdařilo.</b><br />";

/*    }
      $dotaz1 = "
        select * 
        from posta_stare_zaznamy 
        where id in (".$retezec.")
      ";
      $r->query($dotaz1);
      while ($r->next_record()){
        $pocet = $r->Record["POCET"];
        echo $r->Record["ID"]."<br />";
      }
*/
require(FileUp2("html_footer.inc"));
?>
