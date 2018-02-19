<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

//$GLOBALS["PRAVA"]=implode(':',$KOD);

if ($KOD<>'') {
  $q=new DB_POSTA;
  $q->query ("select * from cis_posta_skartace order by id");
  $puvodni="";
  while($q->next_record())
  { $id=$q->Record["ID"];
    $kody=$q->Record["KOD"];

    If (array_key_exists($id,$KOD)) {$GLOBALS["PRAVA"].=$kody.":";}
  //  If (key_exists($id,$KOD)) {$GLOBALS["PRAVA"].=$kody.":";}
  }
}
else {
  $GLOBALS['PRAVA'] = '';
}
//echo $GLOBALS["PRAVA"];
if (!$GLOBALS['AKTIVNI']) $GLOBALS['AKTIVNI'] = 0; 

Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

?>

