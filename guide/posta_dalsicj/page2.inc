<?php
include_once(FileUp2('.admin/adresati_func.inc'));
//$where.=" AND p.CISLO_SPISU1<>0 and p.spis_vyrizen is null and p.MAIN_DOC=1";

$wheretypspis =  ' and (typovy_spis=0 or (typovy_spis>0 and dil=0 and soucast=0))';

$where.="AND p.MAIN_DOC=1";
if (!$GLOBALS['NAZEV_SPISU'])
  $where .= "  and EXISTS (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id $wheretypspis ) ";
else
  $where .= "  and EXISTS (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id $wheretypspis AND nazev_spisu ilike '%".$GLOBALS['NAZEV_SPISU']."%') ";

UNSET($GLOBALS['NAZEV_SPISU']);

$where.="  and (status>0 or status=-7)";
if ($GLOBALS["CONFIG"]["DB"]=="mssql")
  $GLOBALS["ZADEJ_SQL"]="p.*";
else
  $GLOBALS["ZADEJ_SQL"]="DISTINCT ON (cislo_spisu1,cislo_spisu2) p.*";
$GLOBALS["ZADEJ_ORDER_BY"]="cislo_spisu1 ASC, cislo_spisu2 ASC";


$where_temp = $where;
include_once(FileUp2('.admin/brow_access.inc'));
$where = $where_temp . $where;

if ($GLOBALS['ODBOR'] > 0) {
  $odbory = array();
  $odbory[] = $GLOBALS['ODBOR'];
  $user_obj = LoadClass('EedUser', 11);
  $unity = $user_obj->VratOdborZSpisUzlu($GLOBALS['ODBOR']);
  $podrizene_unity = $user_obj->VratPodrizeneUnity($unity);
  foreach($podrizene_unity as $unita => $val) {
    $temp = $user_obj->VratSpisUzelZOdboru($unita);
    if ($temp['ID']>0) $odbory[] = $temp['ID'];
  }


  $unity = $user_obj->VratOdborZSpisUzlu($GLOBALS['ODBOR']);
  $podrizene_unity = $user_obj->VratNadrizeneUnity($unity);
  foreach($podrizene_unity as $unita => $val) {
    $temp = $user_obj->VratSpisUzelZOdboru($unita);
    if ($temp['ID']>0) $odbory[] = $temp['ID'];
  }

  $GLOBALS['ODBOR'] = $odbory;
}

$GLOBALS['GUIDE_DIRECTION'] = 0;



$count = Table(array("agenda" => "POSTA", "showselect"=>true, "showedit"=>false,"appendwhere"=>$where,multipleselect=>false,
  "schema_file" => '.admin/table_schema_guide.inc', "maxnumrows" => 100, "nocaption" => true,
"showdelete"=>false, "showguide"=>true,"setvars"=>true, "nopaging"=>true,"showinfo"=>true,"showhistory"=>false
,

//"action"=>"./guide/posta_dalsispisy/page3.inc"
));


if ($count == 0) {
  echo '<p><div class="alert alert-info darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'"> <h4 class="alert-title">Upozornění:</h4> <p class="info-msg">Vyhledávacím kritériím neodpovídá žádný dokument. Proveďte vyhledání znovu podle jiných kritérií.</div></p>';
  echo '<input type="button" value="Zpět na vyhledávání" onclick="ShowBack();" class="btn">';
/*
echo '<script>
  function ShowBack() {
    action="guide.php?G_NAME=posta_dalsispisy&SPIS_ID='.$GLOBALS['SPIS_ID'].'";
    window.opener.NewWindowGuide(action);
  }
  </script>
';
*/
  echo '';
}
/*
if ($count<5) {

  echo '<table height=400><tr><td valign=top>';
  echo '</td></tr></table>';
}
*/