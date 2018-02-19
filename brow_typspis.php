<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/brow_func.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.admin/has_access.inc'));
require_once(FileUp2('.admin/table_func.inc'));
include_once(FileUp2('.admin/table_funkce_denik.inc'));

require(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
require(FileUp2('html_header_full.inc'));
require_once(FileUp2('.admin/typspis_fce.inc'));
//TODO: Pridat podminku na vyhodnocovani dokumentu
/*
         $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
         $user_id = $USER_INFO['ID'];
         $EedUser = LoadClass('EedUser', $USER_INFO['ID']);
         $text = 'Uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. ') se snažil číst soubory u dokumentu <b>' . $GLOBALS['RECORD_ID'] . '</b>, na které nemá oprávnění.';
         EedTransakce::ZapisLog(0, $text, 'SYS', $user_id);

 */



if ($GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_FILTR_V_DETAILU']) include('.admin/brow_filter.inc');

$EddSql = LoadClass('EedSql');

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));
NewWindow(array("fname" => "Guide", "name" => "Guide", "header" => true, "cache" => false, "window" => "edit"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();



$doc_id = $_GET['doc_id'];
$spis_id = $doc_id;
$cj_obj = LoadClass('EedCj',$doc_id);
$cislo_jednaci = $cj_obj->cislo_jednaci;
$cj_info = $cj_obj->GetCjInfo($doc_id);
$main_doc = $cj_info['MAIN_DOC'];
$where_cj = $cj_obj->GetWhereForCJ($doc_id);
$spis_id = $cj_info['SPIS_ID'];
if ($spis_id <> $doc_id) {
  $doc_id = $spis_id;
  $cj_obj = LoadClass('EedCj',$doc_id);
  $cj_info = $cj_obj->GetCjInfo($doc_id);
  $main_doc = $cj_info['MAIN_DOC'];
  $where_cj = $cj_obj->GetWhereForCJ($doc_id);
}

$jid_ts = $cj_info['JID_SPISU'];
if (!$cislo_spisu1) $cislo_spisu1 = $cj_info['CISLO_JEDNACI1'];
if (!$cislo_spisu2) $cislo_spisu2 = $cj_info['CISLO_JEDNACI2'];

$hlavni_doc = $doc_id;

$nazev_typoveho_spisu = $cj_obj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
$skartaceTYPSPIS = $cj_obj->SpisZnakTypSpis($cj_info['TYPOVY_SPIS_MAINID']);
$spis_uzavren = false;
$lze_editovat = true;
$lze_uzavrit = LzeUzavritSpis_Obj($doc_id);

$mamPravaNaSpis = false;
if ($USER_INFO[ID] == $cj_info['REFERENT']) $mamPravaNaSpis = true;
if (HasRole('admin-typspis')) $mamPravaNaSpis = true;

if ($cj_info['SPIS_VYRIZEN']) $datum_uzavreni_spisu = $q->dbdate2str($cj_info['SPIS_VYRIZEN']);
else $datum_uzvreni_spisu = '';

$url = GetAgendaPath('POSTA_PRIDANI_SPISU', 1, 1);
$url_edit = GetAgendaPath('POSTA_PRIDANI_SPISU', 1, 1);

$GLOBALS['TYP_SPIS_ID'] = $GLOBALS['spis_id'];

if ($cj_info['TYPOVY_SPIS_MAINID']>0) {
  $sql = 'select * from cis_posta_spisy where typovy_spis_id=' . $cj_info['TYPOVY_SPIS_MAINID'] . ' and dil=0 and soucast=0 ';
  $q->query($sql);
  $q->Next_Record();
  $id_typ_spis_cis = $q->Record['ID'];

  $datum_uzavreni_spisu = $q->Record['DATUM_UZAVRENI'];
}



If ($datum_uzavreni_spisu) {
	$spis_uzavren = true;
	$lze_editovat = false;

}

else {
	$spis_uzavren = false;
}
$nazev = '<h1>Typový spis: ' . $cislo_jednaci . '';
$nazev .= '<br/>Název: ' . $nazev_typoveho_spisu . '</h1>';
echo $nazev;
echo '<p>Identifikátor typového spisu: ' . $jid_ts . '<br/>';
echo 'spisový a skartační znak: ' . $skartaceTYPSPIS['KOD'] . ' - '.$skartaceTYPSPIS['ZNAK'].'/'.$skartaceTYPSPIS['DOBA'].'</p>';

if ($spis_uzavren) echo '<p><b>Uzavřeno dne ' . $datum_uzavreni_spisu . '</b></p>';
$fce = array();



echo "<table width='100%' border=0><tr><td width='50%' valign='top' align='left'>";

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/brow_typspis_start.php');
		if (File_Exists($file)) include($file);
  }
}



if($GLOBALS['SHOW_CELE_CJ_CHRONOLOGICKY'] == 1) {

  UNSET($GLOBALS['ID']);
  if ($GLOBALS['SHOW_CELY_SPIS']  == 1)
    $temp = $cj_obj->GetDocsInTypSpis($spis_id);
  else
    $temp = $cj_obj->GetDocsInCj($spis_id);
  foreach($temp as $val) $GLOBALS['ID'][] = $val;

  $sql = Table(array(
    "tablename" => '',
    "agenda" => "POSTA",
    "caption" => $nazev_typoveho_spisu . ' - chronologicky',
    "appendwhere" => $where,
    "schema_file" => '.admin/table_schema_spis.inc',
    "setvars" => true,
    "showhistory" => true,
    "showupload" => true,
    "showexportall" => true,
    "select_id" => "ID" ,
    ));
  $fce[] = '<a class="btn" href="brow_typspis.php?doc_id='.$cj_info['TYPOVY_SPIS_MAINID'].'">Zobrazit podle součástí</a>';
  echo '<p>';
  	foreach($fce as $funkce ) echo $funkce .'&nbsp;';
 echo '</p>';
 }
else {
if ($mamPravaNaSpis && $id_typ_spis_cis>0 && $lze_editovat) $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'../'.$url.'/edit.php?edit&cache_id&DALSI_SPIS_ID=0&EDIT_ID='.$id_typ_spis_cis.'\')">Přejmenovat typový spis</a>';






foreach($fce as $funkce ) echo $funkce .'&nbsp;';

echo "</td><td width='50%' valign='bottom'>";


echo '<p>
    <div class="form dark-color"> <div class="form-body"> <div class="form-row">';
echo "<form method='POST\' action='output/doc/send_to_word.php' target='ífrm_get_value'>";
echo "<input type='hidden' name='sablona' value='prehled_dilu'>
      <input type='hidden' name='main_id' value='".$cj_info['TYPOVY_SPIS_MAINID']."'>
      <input type='hidden' name='cislo_spisu1' value='".$cislo_spisu1."'>
      <input type='hidden' name='cislo_spisu2' value='".$cislo_spisu2."'>
      <input type='hidden' name='referent_spis' value='".$referent."&'>
      <input type='hidden' name='ID' value='".$hlavni_doc."'>
      <input type='hidden' name='format' value='pdf'>";
//    echo "<b>Spisový přehled:</b>&nbsp;&nbsp;<span class=\"form-checkbox-field\"><input type='checkbox' name='obal' value='1'></span>&nbsp;započítat přebal
//  <span class=\"form-checkbox-field\"><input type='checkbox' name='prodomo' value='1'></span>&nbsp;včetně prodomo&nbsp;&nbsp;
//    <input type=submit value='Vytisknout spisový přehled' class=\"btn\">
//    </form>";

echo '
  <div class="form-item ">
    <label class="form-label">Spisový přehled: </label>
    <label class="form-field-wrapper" for="61">
      <span class="form-checkbox-field">
        <input type="checkbox" name="obal"  value="1" id="61" />
      </span>
      <span class="form-checkbox-label">započítat přebal</span>
    </label>
  </div>
  <div class="form-item ">
    <label class="form-label">&nbsp;</label>
    <label class="form-field-wrapper" for="62">
      <span class="form-checkbox-field">
        <input type="checkbox" name="prodomo"  value="1" id="62" />
      </span>
      <span class="form-checkbox-label">včetně poznámek</span>
    </label>
  </div>
  <div class="form-item ">
    <label class="form-label">&nbsp;</label>
    <label class="form-field-wrapper" for="63">
      <span class="form-checkbox-field">
        <input type="checkbox" name="format"  value="rtf" id="63" />
      </span>
      <span class="form-checkbox-label">v editovatelném formátu</span>
    </label>
  </div>
  <div class="form-item ">
    <label class="form-label">&nbsp;</label>
    <label class="form-field-wrapper" for="64">
      <span class="form-checkbox-field">
        <input type=submit value="Vytisknout spisový přehled" class=\"btn\">
      </span>
    </label>
  </div>';
echo '</div>';
echo '</form>';
echo '</div></div></div></p>';


echo '</td></table>';

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));
  $pocet = 0;
  $casti = EedTools::GetSoucastiTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
  while (list($idSoucast, $soucast) = each($casti)) {
  	  $data = array();
  	  $pocet = 0;
  	  $id_posledni_soucasti = $soucast['ID'];
      $caption = $soucast['JID'] . ' - ' . $soucast['NAZEV_SPISU'];

      if ($skartaceTYPSPIS[$id_posledni_soucasti]['DOBA']>0)
        $caption .= '&nbsp;&nbsp;&nbsp;- ('.($skartaceTYPSPIS[$id_posledni_soucasti]['KOD'] ? $skartaceTYPSPIS[$id_posledni_soucasti]['KOD'] . ' - ' : '') .$skartaceTYPSPIS[$id_posledni_soucasti]['ZNAK'].'/'.$skartaceTYPSPIS[$id_posledni_soucasti]['DOBA'].')';
      $caption .= ', otevřeno ' . CZDate($soucast['DATUM_OTEVRENI']);

  //		$pocet++;
  //	$data[$pocet]['JID'] = 'TS' . $idSoucast;
  //	$data[$pocet]['NAZEV'] = $nazevSoucast;
  //	$data[$pocet]['DATUM_OTEVRENI'] = '';
  //	$data[$pocet]['DATUM_UZAVRENI'] = '';
  //	$data[$pocet]['FUNKCE'] = 'x';
  	//$data[$pocet]['FUNKCE'] = '<a href="brow_typspis.php?command=closeSOUCAST&ID='.$dil['SPIS_ID'].'">Uzavřít součást</a>';
      $dily = $cj_obj->SeznamDiluvTypovemSpisuSoucasti($cj_info['TYPOVY_SPIS_MAINID'], $soucast['SOUCAST']);
          $fce = array();
      if ($soucast['DATUM_UZAVRENI'] == '' && HasRole('admin-typspis')) {
        $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'../'.$url_edit.'/edit.php?edit&cache_id&typovy_spis=1&DALSI_SPIS_ID=-1&EDIT_ID='.$idSoucast.'\')">Upravit součást</a>';
        $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=closeSOUCAST&ID='.$idSoucast.'\')">Uzavřít součást</a>';
      }
      else {
        if (HasRole('admin-typspis')) $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=openSOUCAST&ID='.$idSoucast.'\')">Otevřít součást</a>';
      }
      if ($soucast['DATUM_UZAVRENI'] <> '') $caption .= ', uzavřeno ' . CZDate($soucast['DATUM_UZAVRENI']);

      $pocet_doc = 0;
      $celkovy_pocet_doc_v_soucasti = 0;
      $add_new_dil = true;
  	foreach($dily as $idckoDilu => $dil) {
  		$pocet++;
          $href = '<a href="brow_spis.php?dil_id='. $dil['ID'] .'">';
  		$data[$pocet]['JID'] = '<b>' . $href . $dil['JID'] . '</a><b>';
  		//$data[$pocet]['NAZEV'] = '<b>Díl:&nbsp;' . $dil['NAZEV_SPISU'] . '</b>';
  		$data[$pocet]['NAZEV'] = '<b>Díl:&nbsp;</b>';
    	$data[$pocet]['VEC'] = '';
  		$data[$pocet]['DATUM_OTEVRENI'] = $dil['DATUM_OTEVRENI'];
  		$data[$pocet]['DATUM_UZAVRENI'] = $dil['DATUM_UZAVRENI'];
    	$data[$pocet]['STAV'] = '';

      if ($skartaceTYPSPIS[$id_posledni_soucasti][$idckoDilu]['DOBA'] > 0) {
         $data[$pocet]['NAZEV'] .= '&nbsp;&nbsp;&nbsp;('.$skartaceTYPSPIS[$id_posledni_soucasti][$idckoDilu]['KOD'] . ' - '.$skartaceTYPSPIS[$id_posledni_soucasti][$idckoDilu]['ZNAK'].'/'.$skartaceTYPSPIS[$id_posledni_soucasti][$idckoDilu]['DOBA'].')';
      }

      $dalsi_id = $cj_obj->SeznamCJvTypovemSpisu($cj_info['TYPOVY_SPIS_MAINID'], $soucast['SOUCAST'],  $idckoDilu);

      $pocet_doc = 0;
  		foreach($dalsi_id as $key => $val) {
        $celkovy_pocet_doc_v_soucasti ++;
  			$pocet_doc++;
  			$cj_typdil = LoadClass('EedCj', $val);
  			$pocet++;
  			$data[$pocet]['JID'] = $cj_typdil->barcode;
  			$data[$pocet]['NAZEV'] = '&nbsp;&nbsp;&nbsp;' . $cj_typdil->cislo_jednaci_zaklad;
  			$data[$pocet]['VEC'] = TableVec($val);
  			$data[$pocet]['DATUM_OTEVRENI'] = '';
  			$data[$pocet]['DATUM_UZAVRENI'] = '';
  			$data[$pocet]['FUNKCE'] = '';
       	$data[$pocet]['STAV'] = ShowStatus($cj_typdil->status);

        //zjistime krizovou vazbu
        $predchozi = $cj_typdil->GetPredchoziCJ($val);
       		foreach($predchozi as $key2 => $val2) {
            $celkovy_pocet_doc_v_soucasti ++;
      			$pocet_doc++;
      			$cj_typdil2 = LoadClass('EedCj', $val2);
      			$pocet++;
      			$data[$pocet]['JID'] = $cj_typdil2->barcode;
      			$data[$pocet]['NAZEV'] = '&nbsp;&nbsp;&nbsp;kříž.&nbsp;vazba:&nbsp;' . $cj_typdil2->cislo_jednaci_zaklad;
      			$data[$pocet]['VEC'] = TableVec($val2);
      			$data[$pocet]['DATUM_OTEVRENI'] = '';
      			$data[$pocet]['DATUM_UZAVRENI'] = '';
      			$data[$pocet]['FUNKCE'] = '';
           	$data[$pocet]['STAV'] = ShowStatus($cj_typdil->status);
          }

  		}
    		if ($dil['DATUM_UZAVRENI'] == '' && HasRole('admin-typspis')) {
  //  			$fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'../'.$url_edit.'/edit.php?edit&cache_id&DALSI_SPIS_ID=-1&EDIT_ID='.$dil['ID'].'\')">Přejmenovat aktuální díl</a>';
    		}
    		if ($celkovy_pocet_doc_v_soucasti  == 0 && count($casti)>1 && HasRole('admin-typspis')) {
    			$url = GetAgendaPath('POSTA_TYP_SPIS_SOUCASTI', 1, 1);
    			$fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'../'.$url.'/delete.php?cache_id&DELETE_ID='.$id_posledni_soucasti.'\')">Smazat součást</a>';

    		}
    		if ($dil['DATUM_UZAVRENI'] == '' && $pocet_doc == 0 && count($dily)>1 && HasRole('admin-typspis')) {
    			$fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=smazatDIL&doc_id='.$doc_id.'&ID='.$dil['ID'].'\')">Smazat prázdný díl</a>';

    		}
        if ($dil['DATUM_UZAVRENI'] == '' && $pocet_doc > 0 && HasRole('admin-typspis') && $add_new_dil) {
          $add_new_dil = false; // abychom to nenacitali znovu
    			$fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=closeDIL&doc_id='.$doc_id.'&ID='.$dil['ID'].'\')">Přidat nový díl</a>';

    		}
  	}

  	include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  	$db_arr = new DB_Sql_Array;
  	$db_arr->Data=$data;
  	//print_r($DS_DATA);
  	if (count($data)>0)
  		Table(array(
  				"db_connector" => &$db_arr,
  				"showaccess" => true,
  				'caption' => $caption,
  				'schema_file' => GetAgendaPath('POSTA_TYP_SPIS_SOUCASTIADILY', 0, 1) . '/.admin/table_schema_TYPSPIS.inc',
  				"showedit"=>false,
  				"showdelete"=>false,
  				"showselect"=>false,
  				"showinfo"=>false,
          "showcount" => false,

  		));
  	if ($lze_editovat) foreach($fce as $funkce ) echo $funkce .'&nbsp;';
    echo '<p>&nbsp;</p>';
  }
  $fce = array();

  $url = GetAgendaPath('POSTA_TYP_SPIS_SOUCASTI', 1, 1);

  $fce[] = '<a class="btn" href="brow_typspis.php?doc_id='.$cj_info['TYPOVY_SPIS_MAINID'].'&SHOW_CELY_SPIS=1&SHOW_CELE_CJ_CHRONOLOGICKY=1">Zobrazit celý spis chronologicky</a>';
  if (HasRole('admin-typspis')) $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'../'.$url.'/edit.php?insertfrom&cache_id&DALSI_SPIS_ID=-1&EDIT_ID='.$id_posledni_soucasti.'\')">Přidat součást</a>';
  if ($mamPravaNaSpis) $fce[] = '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=closeTYPSPIS&doc_id='.$cj_info['TYPOVY_SPIS_MAINID'].'&typ_spis='.$id_typ_spis_cis.'\')">Uzavřít typový spis</a>';
  echo '<p>';
  	if ($lze_editovat) foreach($fce as $funkce ) echo $funkce .'&nbsp;';
  echo '</p>';

  if ($mamPravaNaSpis && $spis_uzavren) echo '<a class="btn" href="#" onclick="NewWindowAgendaSpis(\'brow_typspis.php?command=openTYPSPIS&doc_id='.$cj_info['TYPOVY_SPIS_MAINID'].'&typ_spis='.$id_typ_spis_cis.'\')">Otevřít typový spis</a>';
}




require(FileUp2('html_footer.inc'));

//  print_r($vysledek);
