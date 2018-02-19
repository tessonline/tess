<?php
// ukazka volani funkce s parametry:
// https://a_login:a_heslo@project.tmapserver.cz/ost/posta/connect/dosle_pisemnosti.php?a_agenda=AGENDA&a_odbor=ODBOR&a_prac=PRAC

  require("tmapy_config.inc");
  include(FileUp2(".admin/brow_.inc"));
  include_once(FileUp2(".admin/security_obj.inc"));
  include_once(FileUp2(".admin/security_func.inc"));
  include_once(FileUp2(".admin/db/db_posta.inc"));

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

    $q=new DB_POSTA;

    If ($GLOBALS["CONFIG"]["ODDELENI"])
    {
       $b_odbor=UkazOdbor($a_odbor,0,0,1);
       If ((GetParentGroup($b_odbor))>0)
          $where=" OR g.parent_group_id=".GetParentGroup($b_odbor)." or g.id=".GetParentGroup($b_odbor);
        else
          $where=" OR g.parent_group_id=".$b_odbor." or g.id=".$b_odbor;
      
      $sql="SELECT u.* FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where u.group_id=".$b_odbor." $where ";    
      $sql.=" order by u.group_id;";
      //echo $sql;    
    }
    else
    {
      $sql = "SELECT * FROM security_user ";
      $b_odbor=UkazOdbor($a_odbor,0,0,1);
      if ($a_odbor) $sql.=" WHERE group_id = '".$b_odbor."'";
  /*    if ($a_id) $sql.=" AND id = '".$a_prac."'";
      if ($a_idod) $sql.=" AND id > '".$a_idod."'";*/
      $sql.=" order by group_id;";
    }
    $q->query($sql);
  
// hlavicka XML
    Header("Pragma: no-cache");
    Header("Cache-Control: no-cache");
    Header("Content-Type: text/xml");
  
    echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\" ?>\n";
  
    echo "<seznam_referent>\n";
    
    while($q->next_record())
    {
      echo "  <referent>\n";

      echo "    <b_id>".$q->Record["ID"]."</b_id>\n";
      echo "    <b_jmeno>".$q->Record["FNAME"]."</b_jmeno>\n";
      echo "    <b_prijmeni>".$q->Record["LNAME"]."</b_prijmeni>\n";
//      echo "    <b_odbor>".$odbor."</b_odbor>\n";

      echo "  </referent>\n";
    }
  
    echo "</seznam_referent>\n";
  
  }
  else
  {
    die ("chyba - nedostatečná přístupová práva");
  }
  
?>

