<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once (FileUp2('.admin/el/of_select_.inc'));
include_once (FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));


require_once (Fileup2(".admin/classes/transformace/DatumFiltr.inc"));
require_once (Fileup2(".admin/classes/transformace/Sql.inc"));


UNSET($_SESSION['SPISOVNA_ID']);


//var_dump($GLOBALS['omez_stav']);
$df = new DatumFiltr();
$GLOBALS['DATUM_OD'] = $df->transform($GLOBALS['DATUM_OD']);
$GLOBALS['DATUM_DO'] = $df->transform($GLOBALS['DATUM_DO']);

$EddSql = LoadClass('EedSql');

require(FileUp2('html_header_full.inc'));

require(FileUp2('.admin/brow_access.inc'));

require(FileUp2('.admin/brow_func.inc'));

if ($GLOBALS["EXPORT_ALL_step"]>0 || $_GET['EDIT_ALL_rec'] == 1) {
  $show_alert = false;
  $show_filter = true;
}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/brow_start.inc');
		if (File_Exists($file)) include($file);
  }
}

$show_alert = true;
$show_filter = true;

if ($GLOBALS["EXPORT_ALL_step"]>0 || $_GET['EDIT_ALL_rec'] == 1) {
  $show_alert = false;
  $show_filter = false;
}

// export dokumentu, musime zapsat do trasakcniho protokolu
if ($GLOBALS["EXPORT_ALL_step"] > 1) {
  if ($_POST['SELECT_IDdenik']) $GLOBALS['ID'] = $_POST['SELECT_IDdenik'];
  if ($_POST['SELECT_ID_FILTERdenik']) $GLOBALS['ID'] = $_POST['SELECT_ID_FILTERdenik'];

  $where = str_replace('  ',' ', $where);
  if (strlen($where)<3) $where = '';

  $id_krizvazba = array();
  $sql = Table(array(
    'tablename' => 'denik',
    'appendwhere' => $where,
    'return_sql' => true
  ));
  $aa = NEW DB_POSTA;
  $q->query($sql);
  while ($q->Next_Record()) {
    $id[] = $q->Record['ID'];
    $sql = 'SELECT * FROM POSTA_KRIZOVY_SPIS WHERE NOVY_SPIS=' . $q->Record['ID'];
    $aa->query($sql);
    while ($aa->Next_Record()) {
      $id_kriz = $aa->Record['PUVODNI_SPIS'];
      $doc_temp = LoadClass('EedCj', $id_kriz);
      $dalsi_id = $doc_temp->GetDocsInCj($id_kriz);
      $id = array_merge($id, $dalsi_id);
      $id_krizvazba = array_merge($id_krizvazba, $dalsi_id);
    }
//    $text = 'Dokument <b>' . $id . '</b> byl exportován do formátu <b>' . $_POST['export_output'] . '</b>';
//    EedTransakce::ZapisLog($id, $text, 'EXPORT', $id_user);
  }
  $GLOBALS['ID'] = $id;
  $GLOBALS['KRIZ_VAZBA'] = $id_krizvazba;

}
if ($GLOBALS["EXPORT_ALL_step"] == 2) {
  //JEDNÁ SE O EXPORT, ZAPISEME DO TRANSAKCNIHO PROTOKOLU
  $text = 'Uživatel  <b>'.$USER_INFO['FNAME'].' '.$USER_INFO['LNAME'].'</b> (' . $USER_INFO['ID'] . ') spustil export dokumentů do formátu ' . $_POST['export_output'];
  EedTransakce::ZapisLog(0, $text, 'EXPORT', $id_user);
}

if ($GLOBALS['STATUS']) {$show_alert = false; $show_filter = false; }
if ($show_alert) {
  $alert = array();
  $where_filter = $where;
  if ($GLOBALS['MAIN_DOC']>0) $where_filter .= "AND main_doc=" . $GLOBALS['MAIN_DOC'];
  if (HasRole('cteni_uzel')) {
    $append_filter = "and ".$EddSql->WhereOdborAndPrac(VratOdbor()."");
  }
  else $append_filter = '';

  if ($GLOBALS['MAIN_DOC']>0) $append_filter .= "AND main_doc=" . $GLOBALS['MAIN_DOC'];
  if (EedTools::UkazPocetDleStatus(2, $where_filter)> 0 && (HasRole('vedouci-odbor')||HasRole('podatelna-odbor')))
    $alert[] = 'Máte nové dokumenty k přiřazení. <a href="brow.php?STATUS=2&MAIN_DOC='.$GLOBALS['MAIN_DOC'].'" class="btn btn-loading"><span class="btn-spinner"></span>přejít na přiřazení</a>';
  if (EedTools::UkazPocetDleStatus(3, $where_filter."and referent in (".$USER_INFO['ID'].")")> 0)
    $alert[] = 'Máte nové dokumenty k přečtení. <a href="brow.php?STATUS=3&MAIN_DOC='.$GLOBALS['MAIN_DOC'].'" class="btn btn-loading"><span class="btn-spinner"></span>přejít na přečtení</a>';
  if (EedTools::UkazPocetDleStatus(11, '')> 0 && count(SeznamKeSchvaleni($USER_INFO['ID']))>0)
    $alert[] = 'Máte nové dokumenty ke schválení. <a href="brow.php?STATUS=11" class="btn btn-loading"><span class="btn-spinner"></span>přejít na schválení</a>';

  if (count($alert)>0) {
    foreach ($alert as $show)
      echo '<p>
        <div class="alert alert-info dark-color">
          <img class="alert-img" src="' . FileUpImage('images/info') . ' ">
          <p class="alert-msg">' . $show . '</p>
        </div></p>';
  }
}



if ($show_filter) {
  include('.admin/brow_filter.inc');
  echo '<div id="AJAX_FILTER"></div>';
  
}


$multipleedit = false;

if ($GLOBALS['STATUS']) {
  unset($GLOBALS['omez_rok']);
  unset($GLOBALS['omez_stav']);
}
else {
//  if (!$_GET['VYHLEDAVANI'] && !$GLOBALS['omez_stav'] && !$GLOBALS['POSTA']['NEUKAZOVAT_PODACI_DENIK'])  $where .= " AND (MAIN_DOC > 0 OR ODES_TYP like 'X') ";
  if (!$_GET['VYHLEDAVANI'] && !$GLOBALS['omez_stav'] && !$GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZOVAT_OBALKY'])  $where .= " AND (MAIN_DOC > 0) ";
}

//$where.= " AND CISLO_SPISU2 in (".$omez_rok.")";
if ($GLOBALS['omez_rok'] && !$_GET['VYHLEDAVANI']) { $where.=" AND cislo_spisu2 in (" . $GLOBALS['omez_rok'] . ")";}
//if ($GLOBALS['omez_zarizeni']) { $where.=" AND superodbor in (" . $GLOBALS['omez_zarizeni'] . ")";}
if ($GLOBALS['omez_zarizeni']) { $where.=" AND superodbor in (" . $GLOBALS['omez_zarizeni'] . ")";}


//konstukce vyrazu $where omez stav pro vyhledávání



$show_predani = false;

$omez_stav_part = ""; 

if (is_array($GLOBALS['omez_stav'])) {
  $where.= " AND (";
  foreach ($GLOBALS['omez_stav'] as $omez) {
    $part = getOmezStavPart($omez);
    $omez_stav_part.=$part." AND ";
    if ($omez == 1 || $omez == 4) {
      // pro tisk predavaciho protokolu
        $show_predani = true;
        $multipleedit = true;
    }
    if ($omez == -7 || $omez == -5)
      $multipleedit = true;   
  }
  $omez_stav_part.=" 1=1)";
  $where.=$omez_stav_part;
//  $where.=" 0=1)";
} else {
  
  if ($GLOBALS['omez_stav']) {
    if ($GLOBALS['omez_stav']==201) 
    { 
      $multipleedit = true; 
      $GLOBALS['ODESLANA_POSTA'] == 'f'; 
    }
    $omez_stav_part.=" AND ".getOmezStavPart($GLOBALS['omez_stav']);
  }
  $where.=$omez_stav_part;
  
  
  if ($GLOBALS['omez_stav'] == 1 || $GLOBALS['omez_stav'] == 4) {
    // pro tisk predavaciho protokolu
      $show_predani = true;
      $multipleedit = true;
  }
  
  if ($GLOBALS['omez_stav'] == -7 || $GLOBALS['omez_stav'] == -5)
    $multipleedit = true;
    

}

//multieditace pro vedouci
if (($GLOBALS["STAV_POSTY"]=="Z"||$GLOBALS["STATUS"]==2||$GLOBALS["STATUS"]==7) && (HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('podatelna-odbor'))) {
  $multipleedit = true;
  $caption = 'Přiřazení dokumentů';
}
if ($GLOBALS['STATUS'] == 2) {

  $ws=" AND (status in (2) or (status in (5,6) and referent is null))";
  $omez_stav_part.= $ws;
  $where.= $ws;

  if (HasRole('vedouci-odbor')) {
    $where .= "and (".$EddSql->WhereOdborAndPrac(VratOdbor()."").")";
  }
//      UNSET($GLOBALS['STATUS']);
//  $GLOBALS['STATUS'] = '2,5,6';

}

if ($GLOBALS['omez_uzel']>0 ) {
  
  $GLOBALS['omez_uzel'] = is_array($GLOBALS['omez_uzel']) ? $GLOBALS['omez_uzel'] : explode(',',$GLOBALS['omez_uzel']) ;
  foreach ($GLOBALS['omez_uzel'] as $uzel) {
    $where_app = $EddSql->WhereOdborAndPrac($uzel);
    //  $where.= " AND (".$where_app."  OR referent in (".$USER_INFO['ID']."))";
    $where.= " AND (".$where_app."  )";
  }

}


//onma, odstranil
//if ($GLOBALS['omez_prac']) {$where.=" AND referent in (".$GLOBALS['omez_prac'].")";}

//multieditace pro vedouci


if (HasRole('hromadna-editace') && ($GLOBALS['ODESLANA_POSTA']=='f' || $GLOBALS['omez_stav']==201)) {$multipleedit = true; }

if ($GLOBALS["ID_pole"]) $multipleedit=true;

if ($GLOBALS["ID_pole"]) $multipleedit=true;


$schema_file = '.admin/table_schema_spis.inc';
if ($GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZOVAT_OBALKY'] == 0) {
  $schema_file = '.admin/table_schema.inc';
}

if ($GLOBALS[STATUS]>0 && $GLOBALS['STATUS']<>2) {
  $schema_file = '.admin/table_schema_spis.inc';
}

$no_find = '<h1>Upozornění</h1>Nebyly nalezeny žádné dokumenty';


if ($GLOBALS[STATUS] == 11 || $GLOBALS['STATUS'] == 12) {
  include_once(FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));
  if ($GLOBALS['STATUS'] == 11) {
    $page_size = 100;
    $stat_pom = $GLOBALS['STATUS'];
    UNSET($GLOBALS['SUPERODBOR']);
    if ($GLOBALS['podpis'] == 1) {
      $seznam = SeznamKPodpisu($USER_INFO['ID']);
      UNSET($GLOBALS['STATUS']);
    }
    else
      $seznam = SeznamKeSchvaleni($USER_INFO['ID']);

    if(count($seznam)>0)
      $where=' AND p.ID IN('.implode(',',$seznam).')';
    else
      $where=' AND 1=2';

  }
  $schema_file = '.admin/table_schema_podpis.inc';
  $caption = 'Schvalování dokumentů';
  unset($GLOBALS['STATUS']);
  $no_find = '<h1>V pořádku</h1>Všechny dokumenty máte schváleny. Pokračujte kliknutím na Přehled.';

}

if ($GLOBALS[STATUS]==3) {
//  $where .= " and referent in (".$USER_INFO['ID'].")";
  $no_find = '<h1>V pořádku</h1>Všechny nové dokumenty máte označeny jako přečtené. Pokračujte kliknutím na Přehled.';
}

if ($GLOBALS[STATUS]==2) {
  $no_find = '<h1>V pořádku</h1>Všechny nové dokumenty máte přiřazeny zpracovatelům. Pokračujte kliknutím na Přehled.';
}

$ws = "";
if (!$_GET['VYHLEDAVANI'] && !$_GET['omez_stav']) {
  If ($GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_STORNOVANO']) $ws.=" AND STATUS<>-1 ";
  If ($GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VYRAZENE']) $ws.=" AND STATUS>-3 ";
  If ($GLOBALS['CONFIG_POSTA_DEFAULT']['SKRYT_VE_SPISOVNE']) $ws.=" AND STATUS<>-3 ";
}

$where.=$ws;
$omez_stav_part.=$ws;

if ($GLOBALS['REFERENT'] && isset($GLOBALS['ODBOR'])) {
  UNSET($GLOBALS['ODBOR']);
}
$where = str_replace('  ',' ', $where);
if (strlen($where)<3) $where = '';

echo '<p>';

$where .= " AND (1=1 ";

if ($GLOBALS['TYP_POSTY']=="" && $GLOBALS['AGENDA_DOKUMENTU']!="") {
  $ad = $GLOBALS['AGENDA_DOKUMENTU'];
  if (is_array($ad)) {
    $ad = implode(',',$GLOBALS['AGENDA_DOKUMENTU']);
  }
   
  $where.=" AND typ_posty in (select id from cis_posta_typ where id_agendy in (".$ad."))";
}

if (HasRole('odeprit-dz')) {
  $where.=" AND ((odeslana_posta is true) OR (vlastnich_rukou<>'9') OR (vlastnich_rukou is null))";
}

if (HasRole('odeprit-odchozi-dz')) {
  $where.=" AND ((odeslana_posta is false) OR (vlastnich_rukou<>'9') OR (vlastnich_rukou is null) OR (referent=".$USER_INFO['ID']."))";
}
    
$zobrazit_dz = HasRole('zobrazit-dz');
$dz_uk = HasRole('dz-uk');
$dz_odbor = HasRole('dz-odbor');
$dz_soucast = HasRole('dz-soucast');
$dz_zpracovatel = HasRole('dz-zpracovatel');       

$w = "";
if ($zobrazit_dz||$dz_uk|| $dz_odbor || $dz_soucast || $dz_zpracovatel) {
  $where = str_replace(" WHERE ", " WHERE (", $where);
  $wt = trim($where);
  if ($wt[0]=="A")
    $where = preg_replace("/AND/", " AND (", $where, 1);
  
   if ($dz_soucast) {
      $omezeni_soucast = "(superodbor in (". EedTools::VratSuperOdbor() ."))"  ;
   } 
   elseif ($dz_odbor) {
      $odbor = array();
      $odbor[]=VratOdbor($USER_INFO['GROUP_ID']);
      $omezeni_odbor = "(odbor in (".implode(",",$odbor)."))";
    }
    
  elseif ($dz_zpracovatel) {
    $omezeni_zpracovatel = "(referent=".$USER_INFO['ID'].")"; 
  }
  
  $omezeni = $dz_soucast ? $omezeni_soucast : ($dz_odbor ? $omezeni_odbor : ($dz_zpracovatel ? $omezeni_zpracovatel : "(1=1)") );
  $omezeni = ($dz_uk||$zobrazit_dz) ? "(1=1)" : $omezeni;
  
  if ($omez_stav_part && strtolower(substr($omez_stav_part, 0, 4 )) !== " and") { 
    $omez_stav_part = " AND ".rtrim ($omez_stav_part,")");
  }
    
  $omezeni.= $omez_stav_part;
 // $where.=" OR ((odeslana_posta is false) and (vlastnich_rukou='9') and ".$omezeni."))";
   $w=" ) OR ((odeslana_posta is false) and (vlastnich_rukou='9') and ".$omezeni.")";
}

$where.=")".$w;

//if (isset($GLOBALS['SELECT_IDdenik'])&&($GLOBALS['omez_stav']!=1)) $GLOBALS['ID'] = $GLOBALS['SELECT_IDdenik'];

if (strlen($where)>2) {
  if ($GLOBALS['omez_stav']==144 || $GLOBALS['omez_stav']==145) {

    //prohledame i historii
    $sql = Table(array(
      'tablename' => '',
      'setvars' => true,
      'appendwhere' => $where,
      'return_sql' => true,
      'formvars'=>array('STAV_POSTY'),
    ));
    $where_temp = $where;
    $sqla = str_replace('SELECT p.* from posta p', 'SELECT DISTINCT(p.id) from posta_h p', $sql);

    $sqla = str_replace($rozsireni_viditelnosti, '', $sqla);
    $where_temp= str_replace($rozsireni_viditelnosti, '', $where_temp); //musime odebrat rozsireni viditelnosti

    $q->query($sqla);
    $add_id = array();
    while ($q->Next_Record()) {
      $add_id[] = $q->Record['ID'];
    }
//     if (count($add_id)>0) {
//       $where .= " OR (p.ID IN (".implode(',', $add_id).") )";
//     }
    if ($GLOBALS['omez_stav']==144)  {
      $where = " AND (p.ID IN (".implode(',', $add_id).")) AND status > 1 AND status < 20 and status<>9 AND p.ID NOT IN (SELECT ID from posta where 1=1 ".$where_temp.")";
    }
    if ($GLOBALS['omez_stav']==145)  {
      $where = " AND (p.ID IN (".implode(',', $add_id).")) AND (status <2 OR  status=9) AND p.ID NOT IN (SELECT ID from posta where 1=1 ".$where_temp.")";
    }
  }
}



if ($GLOBALS['FULLTEXT_SEARCH']) {

  $sql = Table(array(
    'tablename' => 'sql_posta',
    'appendwhere' => $where,
    'setvars' => true,
    'formvars'=>array('STAV_POSTY','REFERENT'),
    'return_sql'=> true,
  ));

  $sql = substr($sql, 0, (strpos($sql, 'ORDER BY'))); //odebereme order by, protoze pri return_sql to nefunguje
  $t = new Sql($RESOURCE_STRING['content_type_charset']);
  $sql = $t->transform($sql);

  $count = Table(array(
    'tablename' => 'denik',
    'setvars' => true,
    'caption' => $caption,
    'showupload' => ($GLOBALS[CONFIG][VLASTNI_UPLOAD] ? false : true),
    'showhistory' => true,
    'sql' => $sql,
    'schema_file' => $schema_file,
    'showselect' => $multipleedit,
    'multipleselect' => $multipleedit,
    'multipleselectsupport' => $multipleedit,
    'showeditall' => ($multipleedit&&($GLOBALS['omez_stav']!=-7)),
    'page_size' => $GLOBALS['CONFIG_POSTA_DEFAULT']['NA_STRANKU'],
    'formvars'=>array('STAV_POSTY','REFERENT'),
  ));
}
else {
  $count = Table(array(
    'tablename' => 'denik',
    'setvars' => true,
    'caption' => $caption,
    'showupload' => ($GLOBALS[CONFIG][VLASTNI_UPLOAD] ? false : true),
    'showhistory' => true,
    'showexport' => true,
    'showexportall' => true,
    'appendwhere' => $where,
    'schema_file' => $schema_file,
    'showselect' => $multipleedit,
    'multipleselect' => $multipleedit,
    'multipleselectsupport' => $multipleedit,
    'showeditall' => ($multipleedit&&($GLOBALS['omez_stav']!=-7)),
    'page_size' => $GLOBALS['CONFIG_POSTA_DEFAULT']['NA_STRANKU'],
    'formvars'=>array('STAV_POSTY','REFERENT'),
  ));

}

if ($count ==0) echo '<p>' . $no_find . '</p>';

if ($show_predani == true) {
echo "<script>
function insertIds(el) {
       var tablename = 'denik';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].checked) {
                var input = document.createElement('INPUT');
                input.setAttribute('type', 'hidden');
                input.setAttribute('name', 'SELECT_ID'+tablename+'[]');
                input.setAttribute('value', f_t[i].value);
                el.appendChild(input);
            }
          }
        }

       var tablename = 'denik';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].type =='hidden') {
                var input = document.createElement('INPUT');
                input.setAttribute('type', 'hidden');
                input.setAttribute('name', 'SELECT_ID'+tablename+'[]');
                input.setAttribute('value', f_t[i].value);
                el.appendChild(input);
            }
          }
        }
}
function insertIdsSpis(el) {
       var tablename = 'denik';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].checked) {
                var input = document.createElement('INPUT');
                input.setAttribute('type', 'hidden');
                input.setAttribute('name', 'ID[]');
                input.setAttribute('value', f_t[i].value);
                el.appendChild(input);
            }
          }
        }
}
</script>
";
  echo "<p><form action='./output/pdf/spisovna.php' method='post' target=protokol onsubmit='insertIds(this);'>
  <input type='hidden' name='box' value='".$GLOBALS['SHOW_BOX']."'>
  <input type='hidden' name='sql' value=\"".$sql."\">";
  echo "<input type='submit' name='nahled' value='   Náhled protokolu  ' class='btn'>&nbsp;&nbsp;&nbsp;<input type='submit' name='tisk' value='   Vytisknout protokol  ' class='btn'>
  </form></p>";;

  access(array('agenda'=>'SKARTACNI_KNIHA'));
  if (HasRole('spisovna') || HasRole('spisovna-odbor')) {
  echo "<p><form action='./services/skartace/skartacni_kniha/brow.php' method='POST' target='' onsubmit='insertIds(this);'>
  <input type='hidden' name='sql' value=\"".$sql."\">
  <input type='hidden' name='PREDANI' value=\"1\">";
  
  echo "<input type='submit' value='Předat do spisovny' class='btn'>
  </form></p>";;

  }
  access(array('agenda'=>'POSTA'));
}



//If (!$GLOBALS['STATUS'])
echo "
<script>
  function ShowLegend()
  {
//      alert(document.getElementById('legenda').style.display);
    if(document.getElementById('legenda').style.display=='none') document.getElementById('legenda').style.display = 'inline';
    else
      document.getElementById('legenda').style.display = 'none';
  }
</script>

<input type='button' onclick='ShowLegend();' value='>> Legenda barev <<' class='btn'/>
<div id='legenda' class='text'>
<table width=\"100%\">
<tr>
<td width=\"50%\"><b>Legenda příchozích dokumentů:</b><br/>
<font color=\"#FF9933\">oranžová</font> - dokument je na podatelně</font><br/>
<font color=\"green\">zelená</font> - dokument čeká na zpracování vedoucím<br/>
<font color=\"darkblue\">modrá</font> - dokument je zpracován vedoucím, čeká na přečtení zpracovatelem<br/>
<font color=\"black\">černá</font> - zpracovatel si dokument přečetl, záležitost se vyřizuje<br/>
<font color=\"gray\">šedivá</font> - dokument je vyřízen</font><br/>
<font color=\"yellow\">žlutá</font> - dokument není vyřízen a zbývá již jen 5 dnů<br/>
<font color=\"red\">červená</font> - je překročena lhůta k vyřízení!<br/>
</td>
<td width=\"50%\" valign=\"top\"><b>Legenda odchozích dokumentů:</b><br/>
<font color=\"brown\">fialová</font> - dokument není vypraven nebo není zadáno datum doručenky<br/>
<font color=\"black\">černá</font> - dokument je ve schvalovacím řízení<br/>
<font color=\"gray\">šedivá</font> - dokument je odeslán a vyřízen
</td>
</tr>
</table>
</div>
<script>
document.getElementById('legenda').style.display = 'none';


</script>
";



if ($show_filter && $GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_BAREVNY_FILTR']) {
  echo '
  <script>
  $( document ).ready(function() {
    $( "#AJAX_FILTER" ).load( "ajax.php?cmd=pocty" );
  });
  </script>
  ';
}


$verze = LoadClass('EedVersion', '');
echo '<hr/><p><small>EED verze: ';

if (HasRole('spravce')) echo '<a href="'.getAgendaPath('POSTA', 0, 1).'/services/nastaveni/verze/verze.php">';
echo $verze->verze;
if (HasRole('spravce')) echo '</a>';
echo ', ' . $verze->datum . '</small></p>';
require(FileUp2('html_footer.inc'));
