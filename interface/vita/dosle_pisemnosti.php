<?php
// ukazka volani funkce s parametry:
// https://a_login:a_heslo@project.tmapserver.cz/ost/posta/connect/dosle_pisemnosti.php?a_agenda=AGENDA&a_odbor=ODBOR&a_prac=PRAC

  require("tmapy_config.inc");
  include(FileUp2(".admin/brow_.inc"));
  include_once(FileUp2(".admin/security_obj.inc"));
  include_once(FileUp2(".admin/db/db_posta.inc"));

// funkce pro prevod kodovani ISO 8859-2 Latin 2 -> Windows 1250  
  function cs_isowin($cstr)
  {
    return StrTr($cstr,"šťžŠŤŽ","šťžŠŤŽ");
  }

// funkce pro konverzi datumu z formatu YYYY-MM-DD do formatu YYYYMMDD
  function dbdate2ymd($dstr)
  {
    $date_arr = Explode("-",$dstr);
    if (StrLen(Trim($date_arr[1]))==1) $date_arr[1] = "0".Trim($date_arr[1]);
    if (StrLen(Trim($date_arr[2]))==1) $date_arr[2] = "0".Trim($date_arr[2]);
    return Trim($date_arr[0]).Trim($date_arr[1]).Trim($date_arr[2]);
  }

// funkce pro konverzi datumu z formatu YYYYMMDD do formatu YYYY-MM-DD
  function ymd2dbdate($dstr)
  {
    return SubStr($dstr,0,4)."-".SubStr($dstr,4,2)."-".SubStr($dstr,6,2);
  }
  
// zjisteni uzivatele
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
// zjisteni skupin pro uzivatele
  $GROUP_INFO = $GLOBALS["POSTA_SECURITY"]->GetAllGroupsForUSer($USER_INFO["LOGIN"]);

// skupina pro cteni a pro zapis
  if (In_Array("conn_r",$GROUP_INFO)) $conn_r = true;
  if (In_Array("conn_w",$GROUP_INFO)) $conn_w = true;

// pouze pro ucely testovani
  $conn_r = true;
  $conn_w = true;
  
// test, zda ma uzivatel pristupova prava
  if ($conn_w)
  {

// povinne parametry
    if (!$a_odbor) die("chyba - neúplné povinné parametry");
// SQL dotaz
    $q=new DB_POSTA;
    $sql = "SELECT * FROM posta WHERE (odbor = '".$a_odbor."' or oddeleni='".$a_odbor."')";

    if ($a_odbor > 0) {
      $odbory = array();
      $odbory[] = $a_odbor;
      $user_obj = LoadClass('EedUser', 11);
      $unity = $user_obj->VratOdborZSpisUzlu($a_odbor);
      $podrizene_unity = $user_obj->VratPodrizeneUnity($unity);
      foreach($podrizene_unity as $unita => $val) {
        $temp = $user_obj->VratSpisUzelZOdboru($unita);
        if ($temp['ID']>0) $odbory[] = $temp['ID'];

      }
      $sql = "SELECT * FROM posta WHERE (odbor in (".implode(',',$odbory)."))";

    }

    if ($a_prac) $sql=" SELECT * FROM posta WHERE referent = '".$a_prac."' ";
    if ($a_idod) $sql.=" AND id > '".$a_idod."'";
    $sql.=" AND (stav=1) AND status<99 AND odeslana_posta='f' order by id;";

    if ($a_id) $sql="SELECT * FROM posta WHERE id = '".$a_id."'";

    $q->query($sql);
  
// hlavicka XML
    Header("Pragma: no-cache");
    Header("Cache-Control: no-cache");
    Header("Content-Type: text/xml");
  
    echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\" ?>\n";
  
    echo "<dosle_pisemnosti>\n";
    
    while($q->next_record())
    {
      $cislo_spisu=$q->Record["CISLO_SPISU1"]?$q->Record["CISLO_SPISU1"]."/".$q->Record["CISLO_SPISU2"]:'';
      $prijemce=StrTr($q->Record['ODESL_PRIJMENI'],"&<>","A()");
      $vec=StrTr($q->Record['VEC'],"&<>","A()");
     
      echo "  <pisemnost>\n";
      echo "    <b_id>".$q->Record["ID"]."</b_id>\n";
      echo "    <b_cp>".$q->Record["EV_CISLO"]."/".$q->Record["ROK"]."</b_cp>\n";
      echo "    <b_cj>".$q->Record["CISLO_JEDNACI1"]."/".$q->Record["CISLO_JEDNACI2"]."</b_cj>\n";
      echo "    <b_cs>".$cislo_spisu."</b_cs>\n";
      echo "    <b_rok>".$q->Record["ROK"]."</b_rok>\n";
      echo "    <b_ze_dne>".dbdate2ymd($q->Record["DATUM_PODATELNA_PRIJETI"])."</b_ze_dne>\n";
      echo "    <b_prac>".$q->Record["REFERENT"]."</b_prac>\n";
      echo "    <b_vec>".$vec."</b_vec>\n";
      echo "    <b_ds>".$q->Record["ODESL_DATSCHRANKA"]."</b_ds>\n";
      echo "    <b_odesilatel>".$q->Record["ODES_TYP"]."</b_odesilatel>\n";
      echo "    <b_prijobyv>".$prijemce."</b_prijobyv>\n";
      echo "    <b_jmobyv>".$q->Record["ODESL_JMENO"]."</b_jmobyv>\n";
      echo "    <b_obchjm>".$prijemce."</b_obchjm>\n";
//      echo "    <b_rric>".$q->Record["RRIC"]."</b_rric>\n";
      echo "    <b_cobce>".$q->Record["ODESL_ULICE"]."</b_cobce>\n";
      echo "    <b_cd>".$q->Record["ODESL_CPOP"]."</b_cd>\n";
//      echo "    <b_uvp>".$q->Record["UVP"]."</b_uvp>\n";
      echo "    <b_cor>".$q->Record["ODESL_COR"]."</b_cor>\n";
      echo "    <b_obec>".$q->Record["ODESL_POSTA"]."</b_obec>\n";
      echo "    <b_psc>".$q->Record["ODESL_PSC"]."</b_psc>\n";
      echo "    <b_stav>".$q->Record["ODESLANA_POSTA"]."</b_stav>\n";
      echo "    <b_vypraveno>".$q->Record["DATUM_VYPRAVENI"]."</b_vypraveno>\n";

      echo "  </pisemnost>\n";
    }
  
    echo "</dosle_pisemnosti>\n";
  
  }
  else
  {
    die ("chyba - nedostatečná přístupová práva");
  }
  
?>

