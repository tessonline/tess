<?php
require("tmapy_config.inc");
/*require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
include(FileUp2(".admin/brow_func.inc"));
*/
include_once(FileUp2(".admin/db/db_default.inc"));
include_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
//security_func vraci odbory atd.
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include(FileUp2(".admin/brow_func.inc"));


$where="";
if (!(HasRole('podatelna') || HasRole('spravce') || HasRole('spisovna-odbor'))) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $where="AND pujceno_komu=".$id_user;
}

if (!$FILTR_ZAPUJCKY) $FILTR_ZAPUJCKY = 1;

if ($FILTR_ZAPUJCKY==1) {
  $where.=" AND vraceno is NULL AND stornovano is NULL";
}
if ($FILTR_ZAPUJCKY==5) {
  $where.=" AND vraceno is not NULL AND stornovano is NULL";
}

if ($FILTR_ZAPUJCKY==-1) {
  $where.=" AND stornovano is not NULL";
}
if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where .= " and z.superodbor in (" . EedTools::VratSuperOdbor() . ")";

/*
$sql_posta = Table(array(
  "agenda"=>"POSTA",
//  "showself"=>true,
  "return_sql"=>true,
));  
$q = new DB_POSTA;
$sql = 'select zapujcka_id from posta_spisovna_zapujcky_id where posta_id in ('.str_replace('p.*','p.ID',$sql_posta).')';
$sql = str_replace(",to_timestamp(DATUM_PODATELNA_PRIJETI, 'FMDD.FMMM.YYYY') as dat_podatelna_prijeti","",$sql);
$sql = str_replace("z.ID","p.ID",$sql);
//echo $sql;
$q->query($sql);
//while ($q->Next_Record()) $GLOBALS['ID'][] = $q->Record['ZAPUJCKA_ID'];
$GLOBALS['ID'] = array();
while ($q->Next_Record()) {
  if (!in_array($q->Record['ZAPUJCKA_ID'], $GLOBALS['ID'])) $GLOBALS['ID'][] = $q->Record['ZAPUJCKA_ID'];
//  $GLOBALS['ID'] = array_unique($GLOBALS['ID']);
}
*/

if ($FILTR_ZAPUJCKY==8) {
  unset($GLOBALS['ID']);
  $where.=" and rucne=1 AND vraceno is null AND stornovano is NULL";
}

echo '<p><div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
echo '<span class="text">Filtr:</span><div class="form dark-color"><div class="form-body"><div class="form-row">
<a href="?FILTR_ZAPUJCKY=1" class="'.($GLOBALS["FILTR_ZAPUJCKY"]==1?'':'btn').'">jen vypůjčené</a>&nbsp;
<a href="?FILTR_ZAPUJCKY=5" class="'.($GLOBALS["FILTR_ZAPUJCKY"]==5?'':'btn').'">jen vrácené</a>&nbsp;
<a href="?FILTR_ZAPUJCKY=-1" class="'.($GLOBALS["FILTR_ZAPUJCKY"]==-1?'':'btn').'">jen smazané</a>&nbsp;
<a href="?FILTR_ZAPUJCKY=8" class="'.($GLOBALS["FILTR_ZAPUJCKY"]==8?'':'btn').'">ručně vložené</a>&nbsp;
<a href="?FILTR_ZAPUJCKY=50" class="'.($GLOBALS["FILTR_ZAPUJCKY"]==50?'':'btn').'">všechny zápujčky</a>&nbsp;
</div></div></div>';
echo '</div> </div> </div><p>';



$count=Table(array(
  "showaccess" => true,
  "appendwhere"=>$where,
  "setvars"=>true,
//  "showself"=>true,
  "select_id"=>DOBA,
  "showinfo"=>false,
  "showedit"=>false,
  "showdelete"=>true,
  "showhistory"=>false,  
  "page_size"=>"25",
));  

require(FileUp2("html_footer.inc"));
