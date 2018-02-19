<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));
//If ($ODESL_PRIJMENI<>"") 
 {
  // uzivatel chce vyhledavat podle prijmeni ci nazvu firmy, musime proto prohledat i posta_cis_prijemci

  $q=new DB_POSTA;
  $sql="select id from cis_posta_prijemci where odesl_prijmeni ilike '%".$GLOBALS["ODESL_PRIJMENI"]."%'";
  If ($GLOBALS["CONFIG"]["DB"]=='mssql')
    $sql="select id from cis_posta_prijemci where odesl_prijmeni like '%".$GLOBALS["ODESL_PRIJMENI"]."%'";
//  die ('SQL '.$sql);
  $q->query ($sql);
  while($q->next_record())
  {
   $IDcka.=$q->Record["ID"].",";
  }
//   die($IDcka);
//    $IDcka=substr($IDcka,0,-1);

  If ($IDcka<>"") {$where.=" or (p.DALSI_PRIJEMCI like ('".$IDcka."%') or p.DALSI_PRIJEMCI like ('%,".$IDcka."%') )";}
  $GLOBALS["ODESL_PRIJMENI"]="*".$GLOBALS["ODESL_PRIJMENI"]."*";
 }

Table(array("showaccess" => false,"showselect"=>true,  "appendwhere"=>$where));  

require(FileUp2("html_footer.inc"));
?>
