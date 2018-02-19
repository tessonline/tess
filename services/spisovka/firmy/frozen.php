<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');


$ttt=new DB_POSTA;
//$sqlaa="update posta SET frozen='".$frozen."',last_date='',last_time,last_user_id= where id IN (".$idaa.")";

$sqlaa="select * from posta where id = ".$idaa."";
$ttt->query($sqlaa);
$ttt->Next_Record();


//if ($ttt->Record["ODESL_JMENO"]=='NULL') Die(';stop');

$sqlaa = "
  update posta set
  frozen='".$frozen."',last_date='".$LAST_DATE."',last_time='".$LAST_TIME."',last_user_id=".$id_user."
  where id in( 
    select id
    from posta
    where 
    odes_typ LIKE '".$ttt->Record["ODES_TYP"]."'";
    
if (trim($ttt->Record["ODESL_ADRKOD"])) $sqlaa.=" and odesl_adrkod = '".$ttt->Record["ODESL_ADRKOD"]."'";
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.=" and odesl_prijmeni LIKE '".$ttt->Record["ODESL_PRIJMENI"]."'";
if (trim($ttt->Record["ODESL_JMENO"])) $sqlaa.=" and odesl_jmeno LIKE '".$ttt->Record["ODESL_JMENO"]."'";
if (trim($ttt->Record["ODESL_ULICE"])) $sqlaa.=" and odesl_ulice LIKE '".$ttt->Record["ODESL_ULICE"]."'";
if (trim($ttt->Record["ODESL_CP"])) $sqlaa.=" and odesl_cp = '".$ttt->Record["ODESL_CP"]."'";
if (trim($ttt->Record["ODESL_PSC"])) $sqlaa.=" and odesl_psc = '".$ttt->Record["ODESL_PSC"]."'";
if (trim($ttt->Record["ODESL_POSTA"])) $sqlaa.=" and odesl_posta LIKE '".$ttt->Record["ODESL_POSTA"]."'";
if (trim($ttt->Record["ODESL_OSOBA"])) $sqlaa.=" and odesl_osoba LIKE '".$ttt->Record["ODESL_OSOBA"]."'";
if (trim($ttt->Record["ODESL_ODD"])) $sqlaa.=" and odesl_odd LIKE '".$ttt->Record["ODESL_ODD"]."'";
if (trim($ttt->Record["REFERENT"])) $sqlaa.=" and referent =".$ttt->Record["REFERENT"]."";

$sqlaa.=")";
//    and referent = '".$ttt->Record["REFERENT"]."'

//    and odesl_osoba = (select odesl_osoba from posta where id = ".$idaa.")
//    and odesl_odd = (select odesl_odd from posta where id = ".$idaa.")
/*
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.=" odesl_prijmeni = '".$idaa."';
if (trim($ttt->Record["ODESL_JMENO"])) $sqlaa.="and odesl_jmeno = (select odesl_jmeno from posta where id = ".$idaa.")
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.="and odesl_ulice = (select odesl_ulice from posta where id = ".$idaa.")
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.="and odesl_cp = (select odesl_cp from posta where id = ".$idaa.")
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.="and odesl_psc = (select odesl_psc from posta where id = ".$idaa.")
if (trim($ttt->Record["ODESL_PRIJMENI"])) $sqlaa.="and odesl_posta = (select odesl_posta from posta where id = ".$idaa.")
if (trim($ttt->Record["ODESL_PRIJMENI"])) referent = (select referent from posta where id = ".$idaa.")
*/

//die($sqlaa);
$ttt->query($sqlaa);
echo $sqlaa;

echo "      <script language=\"JavaScript\" type=\"text/javascript\">
  window.opener.location.reload();
  window.close();
         
      //-->
      </script>
";
?>



