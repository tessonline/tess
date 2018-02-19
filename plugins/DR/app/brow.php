<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/table_func_DR.inc"));
include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once (FileUp2('.admin/el/of_select_.inc'));
include_once (FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));

require_once (Fileup2(".admin/classes/transformace/DatumFiltr.inc"));
require_once (Fileup2(".admin/classes/transformace/Sql.inc"));

require(FileUp2("html_header_full.inc"));

include('.admin/brow_func.inc');
include_once(FileUp2('plugins/filtry/brow_start.inc'));
include_once(FileUp2('plugins/DR/brow_start.inc'));
include('.admin/brow_filter.inc');
//echo '<div id="AJAX_FILTER"></div>';


function getOmezStavPart($os) {
  $part = "";
  if ($os && $os>7 && $os<100) {$part=" status = " . $os;}
  if ($os && $os<2) {$part=" status = " . $os;}

  if ($os==2) {$part=" (status in (2) or (status in (5,6) and referent is null))";}
  if ($os==3) {$part=" (status in (3) or (status in (5,6) and referent is not null and DATUM_REFERENT_PRIJETI is null))";}
  if ($os==4) {$part=" (status in (4) or (status in (5,6) and referent is not null and DATUM_VYRIZENI is null))";}
  if ($os==5) {$part=" status in (5)";}
  if ($os==6) {$part=" status in (6)";}
  //if ($os==7) {$part=" status in (7)";}
  if ($os==7) {$part="  ((status in (7) or (status in (5,6) and referent is null and odbor is null))) ";}
  if ($os==101) {$part=" status in (101)";}
  if ($os==199) {$part=" CISLO_SPISU1=0";}
  if ($os==200) {$part=" status < 0";}
  if ($os==201) {$part=" odeslana_posta='f'"; $GLOBALS['multipleedit']=true;}
  if ($os==202) {$part=" odeslana_posta='t'";}
  if ($os==203) {$part=" status > 1";}
  if ($os==204) {$part=" status > 1 AND status < 20 AND status<>9 ";}
  if ($os==205) {$part=" status in (5,6)";}
  If ($os==206) {$part=" main_doc=1 and (((DATUM_VYRIZENI)>lhuta_vyrizeni and datum_vyrizeni IS NOT NULL and lhuta_vyrizeni is not null) or (lhuta_vyrizeni<CURRENT_DATE and (status in (1,9,-3,-4)) and (datum_vyrizeni is null) and lhuta_vyrizeni is not null)) ";}
  If ($os==210) {$part=" not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id))  and p.main_doc=1 ";}
  // If ($os==220) {$part=" (not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id)) ) OR
  //  (exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id))  and p.main_doc=1";}
  If ($os==220) {$part=" ((exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id)) OR not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id))) and p.main_doc=1 and status>1";}
  if ($part =="") return "1=1";
  return "(".$part.")";
}

$show_predani = false;

if (isset($_GET['omez_stav']) && !is_array($_GET['omez_stav'])) {$GLOBALS['omez_stav'] = array(); $GLOBALS['omez_stav'][] = $_GET['omez_stav']; }
else {
  $GLOBALS['omez_stav'] = $_GET['omez_stav'];
}

if (is_array($GLOBALS['omez_stav'])) {
  $where.= " AND (";
  foreach ($GLOBALS['omez_stav'] as $omez) {
    $part = getOmezStavPart($omez);
    $where.=$part." AND ";
    if ($omez == 1 || $omez == 4) {
      // pro tisk predavaciho protokolu
        $show_predani = true;
        $multipleedit = true;
    }
    if ($omez == -7)
      $multipleedit = true;
  }
  $where.=" 1=1)";
//  $where.=" 0=1)";
} else {
  if ($GLOBALS['omez_stav']) {
    if ($GLOBALS['omez_stav']==201)
    {
      $multipleedit = true;
      $GLOBALS['ODESLANA_POSTA'] == 'f';
    }
  $where.=" AND ".getOmezStavPart($GLOBALS['omez_stav']);
  }

  if ($GLOBALS['omez_stav'] == 1 || $GLOBALS['omez_stav'] == 4) {
    // pro tisk predavaciho protokolu
      $show_predani = true;
      $multipleedit = true;
  }

  if ($GLOBALS['omez_stav'] == -7)
    $multipleedit = true;


}

if ($GLOBALS['omez_uzel']>0 ) {
  $EddSql = LoadClass('EedSql');
  $GLOBALS['omez_uzel'] = explode(',',$GLOBALS['omez_uzel']);
  foreach ($GLOBALS['omez_uzel'] as $uzel) {
    $where_app = $EddSql->WhereOdborAndPrac($uzel);
    //  $where.= " AND (".$where_app."  OR referent in (".$USER_INFO['ID']."))";
    $where.= " AND (".$where_app."  )";
  }

}

if ($GLOBALS['STAV_select']) {
  $app_id = floor(($GLOBALS['STAV_select']-1000)/10);
  $_GET['STAV_select'] = $GLOBALS['STAV_select'];
  $where .= " AND (stav in (".$GLOBALS['STAV_select'].",".($GLOBALS['STAV_select']+1).") OR dalsi_id_agenda like 'DR-".$app_id."-%')";
}

//foreach($_GET as $key => $val)
//  $formvars[] = $key;

  //zobrazime spisovku
$schema_file = 'plugins/DR/app/.admin/table_schema_spis.inc';
$where2 = " AND vlastnich_rukou like '9'";
$count = Table(array(
         "agenda" => "POSTA",
        'tablename' => 'denik',
         "appendwhere"=>$where . $where2,
         'schema_file' => $schema_file,
         "showdelete"=>false,
         "showedit"=>true,
         "showinfo"=>true,
         "caption" => "Datové zprávy v ESSS",
         "nocaption"=>false,
  	     "setvars"=>true,
         "showupload" => true,
         "showhistory" => true,
         "formvars" => array('STAV_select'),
//  	     "unsetvars"=>true,
));


require(FileUp2("html_footer.inc"));

