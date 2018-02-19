<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/brow_func.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.admin/has_access.inc'));

Access(array('agenda' => 'SKARTACNI_KNIHA'));
if (HasRole('spisovna') || HasRole('spisovna-odbor')) $je_spisovak = true;
else $je_spisovak = false;

Access(array('agenda' => 'POSTA'));

require(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
require(FileUp2('html_header_full.inc'));

if ($GLOBALS['CONFIG_POSTA_DEFAULT']['UKAZAT_FILTR_V_DETAILU']) include('.admin/brow_filter.inc');

$EddSql = LoadClass('EedSql');

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));
NewWindow(array("fname" => "Guide", "name" => "Guide", "header" => true, "cache" => false, "window" => "edit"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/brow_spis_start.php');
		if (File_Exists($file)) include($file);
  }
}
$doc_id = $_GET['doc_id'];
if ($_GET['dil_id']) {
	$dil = (integer) $_GET['dil_id'];
    $cj_obj = LoadClass('EedCj', 0);
    $dil_array = $cj_obj->GetDil($dil);
	$typovy_spis_id = $dil_array['TYPOVY_SPIS_ID'];
	$soucast = $dil_array['SOUCAST'];
	$dil = $dil_array['DIL'];
    $cj = $cj_obj->SeznamCJvTypovemSpisu($typovy_spis_id, $soucast, $dil);

    if (count($cj) == 0) {

    	echo 'Upozornění: Díl je prázdný';
    	echo "<br/><a  class=\"btn btn-loading\" href=\"brow_typspis.php?doc_id=$typovy_spis_id\">Zobrazit obsah typového spisu</a>&nbsp;&nbsp;&nbsp;";
    	include(FileUp2('html_footer.inc'));
       Die();    	 
    }
    else {
    	$doc_id = $cj[0];
    }
}


$spis_id = $doc_id;
$cj_obj = LoadClass('EedCj',$doc_id);
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

if (!$cislo_spisu1) $cislo_spisu1 = $cj_info['CISLO_JEDNACI1'];
if (!$cislo_spisu2) $cislo_spisu2 = $cj_info['CISLO_JEDNACI2'];

if ($cj_info['JE_TYPOVY_SPIS']>0) {
	$nazev = $cj_obj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);

	$cj_info['CELY_NAZEV'] = $nazev;
}


$hlavni_doc = $doc_id;

$spis_uzavren = false;
$lze_editovat = true;
$lze_uzavrit = LzeUzavritSpis_Obj($doc_id);
$mamPravaNaSpis = false;

include_once('.admin/has_access.inc');
$ma_pristup = false;
$cj = $cj_obj->GetDocsInCj($spis_id); //musime projit vsecny cj, jestli ma prava aspon na nejaky dokument
foreach ($cj as $doc_id) {
  if (MaPristupKCteniDokumentu($doc_id)) $ma_pristup = true;
}

if (!$ma_pristup) {
	EedTools::MaPristupKDokumentu($spis_id, 'zobrazeni detailu cj. ');
}

$GLOBALS['EDIT_ID'] = $doc_id; //kvuli MaPristupKDokumentu_table
if ($USER_INFO[ID] == $cj_info['REFERENT']) $mamPravaNaSpis = true;
if (MaPristupKDokumentu_old($doc_id)) $mamPravaNaSpis = true;


$q = new DB_POSTA;
if ($cj_info['SPIS_VYRIZEN']) $datum_uzavreni_spisu = $q->dbdate2str($cj_info['SPIS_VYRIZEN']);
else $datum_uzvreni_spisu = '';

echo '<h1> ';

If ($datum_uzavreni_spisu) {
  $spis_uzavren = true;
  $lze_editovat = false;

 echo "".$cj_info['CELY_NAZEV']." - uzavřeno dne ".$datum_uzavreni_spisu;
}

else {
  $spis_uzavren = false;
  echo $cj_info['CELY_NAZEV'];
}

//pokud ukazuju cely typovy spis, tak nebudu ukazovat editaci
if ($GLOBALS['SHOW_CELY_SPIS']) {$mamPravaNaSpis = false;}


$spis4p = 'spisu';
if ($cj_info['TYPOVY_SPIS_ID']>0) {
	$spis4p = 'dílu';
	$id_typ_spis = $cj_info['TYPOVY_SPIS_MAINID'];
	echo '<br/>(šablona typového spisu: '.$cj_obj->NazevSablonyTypovehoSpisu($cj_info['TYPOVY_SPIS_ID']) . ')';
    echo "<br/><a  class=\"btn btn-loading\" href=\"brow_typspis.php?cislo_spisu1=$cislo_spisu1&$cislo_spisu2=$cislo_spisu2&doc_id=$id_typ_spis\">Zobrazit obsah typového spisu</a>&nbsp;&nbsp;&nbsp;";
}

echo '</h1>';
if ($cj_info['JID_SPISU'] && !$cj_info['JE_TYPOVY_SPIS']) {
  echo '<p><table><tr><td>Identifikátor spisu:</td><td><b>' . $cj_info['JID_SPISU'] . '</b></td></tr>';
  echo '<tr><td>Spisový uzel:</td><td><b>' . $cj_obj->odbor_text . '</b></td></tr>';
  echo '<tr><td>Vlastník:</td><td><b>' . $cj_obj->referent_text . '</b></td></tr>';
  echo '<tr><td>Schvalovatel:</td><td><i>' . $cj_obj->referent_text . '</td></td></tr>';
  echo '<tr><td>Zpracovatel:</td><td><b>' . $cj_obj->referent_text . '</b></tr></table></p>';
}

if ($dil_array['JID'] && $cj_info['JE_TYPOVY_SPIS']) {
  echo '<p>Identifikátor dílu: <b>' . $dil_array['JID'] . '</b><br/>';
  echo 'Název dílu: <b>' . $dil_array['NAZEV_SPISU'] . '</b></p>';
}
$q = new DB_POSTA;

EedLog::writeLog('Zobrazení čj/spisu', array('ID' => $GLOBALS['spis_id']));

// ukazujeme pouze jeden spis...
UNSET($GLOBALS['SUPERODBOR']);

echo "<table width='100%' border=0><tr><td width='50%' valign='top' align='left'>";
  
$spis_where = $cj_obj->GetWhereForCJ($GLOBALS['spis_id']);


if ($main_doc<100) {
    $count=Table(array(
      "agenda" => "POSTA_SPIS_SPISOVNA",
      "tablename" => "posta_spis_spisovna",
      "appendwhere" => "and dokument_id=".$spis_id,
  //    "maxnumrows" => 1,
      "showdelete" => false,
      "showhistory" => true,
      'showcount' => false, //protahuje to tabulku
  //    "showedit" => $lze_editovat,
   		"showedit"=>!$spis_uzavren && $mamPravaNaSpis,
      "showinfo" => false,
      //"nocaption" => true,
      "showaccess" => true,
      "setvars" => true,
      "unsetvars" => true,
      "emptyoutput" => false,

    ));
    if ($count==0 && $mamPravaNaSpis) {

  //    if ($lze_editovat)
      if (!$cj_info['JE_TYPOVY_SPIS']) echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath("POSTA_SPIS_SPISOVNA",false,true)."/edit.php?insert&DOKUMENT_ID=".$spis_id."')\">Zadat údaje</a>&nbsp;&nbsp;&nbsp;";

    }
    if ($spis_uzavren && $mamPravaNaSpis && ($cj_info['STATUS']>0 || $cj_info['STATUS']==-4 || $cj_info['STATUS']==-5) && $je_spisovak ) echo "<a  class=\"btn btn-loading\" href=\"".GetAgendaPath("SKARTACNI_KNIHA",false,true)."/brow.php?ID=".$spis_id."&PREDANI=1\">Předat do spisovny</a>";

  If (!$spis_uzavren && !$GLOBALS["FROM_EVIDENCE"]) {
    if ($GLOBALS[CONFIG]["SHOW_C_JEDNACI"])
      echo "<br/><br/><input type=button class=button onclick=\"javascript:newfrom2()\" value='Přiřadit k ".$GLOBALS["CONFIG"]["CISLO_SPISU_3P"]." ".$text_cislospisu." další ".$GLOBALS["CONFIG"]["CISLO_SPISU_4P"]."'>";
    else
    {
    }

  //  NewWindow(array("fname" => "Spis", "name" => "spis_editovat", "header" => true, "cache" => false, "window" => "edit","height" => 500,"width" => 800));



      if (!$cj_info['JE_SPIS'] && $mamPravaNaSpis) echo "<a  class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/dalsi_spis/edit.php?insert&cacheid=&spis1=".$cislo_spisu1."&spis2=".$cislo_spisu2."&SPIS_ID=".$spis_id."&DALSI_SPIS_ID=".$spis_id."&');\">Vytvořit spis</a>&nbsp&nbsp&nbsp;";
    if (!$cj_info['JE_SPIS'] && $mamPravaNaSpis) echo "<a  class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/typovy_spis/edit.php?insert&cacheid=&spis1=".$cislo_spisu1."&spis2=".$cislo_spisu2."&SPIS_ID=".$spis_id."&DALSI_SPIS_ID=".$spis_id."&');\">Vytvořit typový spis</a>&nbsp&nbsp&nbsp;";
      if ($cj_info['JE_SPIS'] && $mamPravaNaSpis  && !$cj_info['JE_TYPOVY_SPIS']) {
//        $sql = 'select * from cis_posta_spisy where spis_id='.$GLOBALS['spis_id'].' and dalsi_spis_id=0';
        $sql = 'select * from cis_posta_spisy where spis_id='.$GLOBALS['spis_id'].' order by id asc';
        $q->query($sql);
        $q->Next_Record();

        echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/dalsi_spis/edit.php?edit&cacheid=&EDIT_ID=".$q->Record['ID']."')\">Opravit název $spis4p</a>&nbsp&nbsp&nbsp;";
      }


      if ($cj_info['JE_SPIS'] && $mamPravaNaSpis && !$cj_info['JE_TYPOVY_SPIS']) echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/smazani_spisu/edit.php?edit&cacheid=&spis_id=".$spis_id."')\">Smazat spis</a>&nbsp&nbsp&nbsp;";

      if ($cj_info['JE_SPIS'] && !$cj_info['JE_TYPOVY_SPIS'] && $mamPravaNaSpis) echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_dalsicjspisy&SPIS_ID=".$spis_id."');\">Přidat do tohoto spisu čj./arch</a></p>";
      if ($cj_info['JE_SPIS'] && !$cj_info['JE_TYPOVY_SPIS'] && $mamPravaNaSpis) echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_dalsicj&SPIS_ID=".$spis_id."');\">Předat do jiného spisu</a>&nbsp&nbsp&nbsp;";
      if ($cj_info['JE_SPIS'] && $cj_info['JE_TYPOVY_SPIS'] && $mamPravaNaSpis) echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_dalsicjspisy&SPIS_ID=".$spis_id."');\">Přidat do tohoto dílu čj./arch</a></p>";
      if (!$cj_info['JE_SPIS'] && $mamPravaNaSpis) echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath('POSTA',false,true)."/guide.php?G_NAME=posta_dalsicj&SPIS_ID=".$spis_id."');\">Přidat do spisu</a></p>";

  }
  //else

  //If ($mamPravaNaSpis &&  (HasRole('spravce') || HasRole('vedouci')) && !$spis_uzavren && !$GLOBALS["FROM_EVIDENCE"])  {
//  If ((HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('editace_uzel')||HasRole('editace_admin')||HasRole('vedouci-odd')) && $mamPravaNaSpis && !$spis_uzavren && !$GLOBALS["FROM_EVIDENCE"] && !$cj_info['JE_TYPOVY_SPIS'])  {
  If (HasRole('zmena-spisoveho-uzlu') && (HasRole('editace_zpracovatel')||HasRole('editace_uzel')||HasRole('editace_vse_pracoviste')||HasRole('editace_admin'))&& $mamPravaNaSpis && !$spis_uzavren && !$GLOBALS["FROM_EVIDENCE"] && !$cj_info['JE_TYPOVY_SPIS'])  {
//    echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/predani_spisu/edit.php?insert&cacheid=&OLD_REFERENT=".$referent."&OLD_ODBOR=".$odbor."&OLD_SO=".$so."&spis1=".$cislo_spisu1."&spis2=".$cislo_spisu2."&referent=".$referent."&SPIS_ID=".$GLOBALS['spis_id']."')\">Předat ".$cj_info['CELY_NAZEV']." jinému útvaru nebo zpracovateli</a></p>";
    echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/predani_spisu/edit.php?insert&cacheid=&OLD_REFERENT=".$referent."&OLD_ODBOR=".$odbor."&OLD_SO=".$so."&spis1=".$cislo_spisu1."&spis2=".$cislo_spisu2."&referent=".$referent."&SPIS_ID=".$GLOBALS['spis_id']."')\">Předat jinému útvaru nebo zpracovateli</a></p>";
  }
  
 

  $cj_obj = LoadClass('EedCj',$spis_id);
  $pid_arr = $cj_obj->GetDocsInCj($spis_id);
  $pid = implode(',',$pid_arr);

    //$spis_where="AND POSTA_ID in (".$spis_id.")"; 
    $spis_where="AND POSTA_ID in (".$pid.")";
    $spis_order=" order by pp.spis desc, su.lname, su.fname";
    $count=Table(array(
    		"agenda"=>"POSTA_PRISTUPY",
    		"tablename"=>"POSTA_PRISTUPY",
    		"appendwhere"=>$spis_where,
    		"showdelete"=>!$spis_uzavren && $mamPravaNaSpis,
    		"showedit"=>!$spis_uzavren && $mamPravaNaSpis,
    		"caption"=>"Oprávnění k čj./spisu",
        "sql" => "SELECT DISTINCT ON (pp.spis,su.lname, su.fname,pp.referent,pp.access,pp.odbor) pp.*, su.fname, su.lname"
            ." FROM posta_pristupy pp left join security_user su on pp.referent = su.id WHERE 1=1  ".$spis_where.$spis_order,
    		"showinfo"=>false,
    		"showaccess"=>true,
    		"setvars"=>true,
    		"unsetvars"=>true,
    		"emptyoutput"=>false,
    ));
    if (!$spis_uzavren && $mamPravaNaSpis) echo "
<a  class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('".GetAgendaPath("POSTA_PRISTUPY",false,true)."/edit.php?insert&POSTA_ID=".$spis_id."')\">Přidat oprávnění</a>
<br/>";

    $docs = $cj_obj->GetDocsInCj($GLOBALS['spis_id']);
    if (count($docs)<1) $docs[0] = -1;
    echo "</td><td width='50%' valign='top'>";
      echo "<p>
      		<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('history.php?HISTORY_ID=".$spis_id."&typ=SPIS')\">Historie</a>";
        if (!$GLOBALS['SHOW_CELE_CJ_CHRONOLOGICKY']) echo "&nbsp;&nbsp;&nbsp;<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('tisk.php?SPISID=".$spis_id."')\">Export</a>";
      	echo "&nbsp;&nbsp;&nbsp;<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('exportXML.php?ID=".$spis_id."')\">Export do XML</a>";
      	if (!$cj_info['JE_TYPOVY_SPIS'] && !$GLOBALS['SHOW_CELE_CJ_CHRONOLOGICKY']) echo "&nbsp;&nbsp;&nbsp;<a class=\"btn btn-loading\" href=\"brow_spis.php?doc_id=".$hlavni_doc."&SHOW_CELE_CJ_CHRONOLOGICKY=1\">Zobrazit celý spis chronologicky</a>";

		echo "</p>";


      $spis_where="AND NOVY_SPIS in (".implode(', ',$docs).")"; $GLOBALS['SMER_KRIZ']=1;
      $count=Table(array(
      		"agenda"=>"POSTA_KRIZOVY_SPIS",
      		"tablename"=>"POSTA_KRIZOVY_SPIS_1",
      		"appendwhere"=>$spis_where,
      		"showdelete"=>!$spis_uzavren,
      		"showedit"=>false,
      		"caption"=>"Křížová vazba",
      		"showinfo"=>false,
      		"showaccess"=>true,
      		"setvars"=>true,
      		"unsetvars"=>true,
      		"emptyoutput"=>false,
      ));
      if (!$spis_uzavren && $mamPravaNaSpis) echo "
  <a  class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./guide.php?G_NAME=posta_krizspisy&IDPK=".$GLOBALS['spis_id']."&smer_krize=1')\">Přidat předcházející čj</a>
  <br/>";
      
      //  $spis_where="AND PUVODNI_SPIS=".$GLOBALS['spis_id'];$GLOBALS['SMER_KRIZ']=2;
      $spis_where="AND PUVODNI_SPIS in (".implode(', ',$docs).")"; $GLOBALS['SMER_KRIZ']=2;
      $count=Table(array(
      		"agenda"=>"POSTA_KRIZOVY_SPIS",
      		"tablename"=>"POSTA_KRIZOVY_SPIS_1",
      		"appendwhere"=>$spis_where,
      		"showdelete"=>false,
      		"showedit"=>false,
      		"showinfo"=>false,
      		"nocaption"=>true,
      		"showaccess"=>true,
      		"setvars"=>true,
      		"unsetvars"=>true,
      		"emptyoutput"=>true,
      ));
      
      

    echo '<p>
    <div class="form dark-color"> <div class="form-body"> <div class="form-row">';
    //  echo "<br/><br/><input type=button class=button onclick=\"javascript:NewWindow2('output/pdf/spisobalka.php?cislo_spisu1=".$cislo_spisu1."&cislo_spisu2=".$cislo_spisu2."&SPIS_ID=".$spis_id."&referent_spis=".$referent."&')\" value='Vytisknout spisový přebal (referátník) '><br/>";
      echo "<form method='GET\' action='output/pdf/spisobalka.php' target='ífrm_get_value'>";
      echo "<input type='hidden' name='sablona' value='prehled'>
      <input type='hidden' name='cislo_spisu1' value='".$cislo_spisu1."'>
      <input type='hidden' name='cislo_spisu2' value='".$cislo_spisu2."'>
      <input type='hidden' name='SPIS_ID' value='".$spis_id."'>
      <input type='hidden' name='referent_spis' value='".$referent."&'>
      <input type='hidden' name='DIL_ID' value='".$dil."'>";
      
  //     echo "Spisový přebal:&nbsp;&nbsp;
  //     <span class=\"form-checkbox-field\"><input type='checkbox' name='format' value='A3'></span>
  //     formát&nbsp;A3
  //     <input type=submit value='Vytisknout spisový přebal (referátník)' class=\"btn\">
  //     </form>";

  echo '
  <div class="form-item ">
    <label class="form-label">Spisový přebal: </label>
    <label class="form-field-wrapper" for="60">
      <span class="form-checkbox-field">
        <input type="checkbox" name="format"  value="A3" id="60"/>
      </span>
      <span class="form-checkbox-label">formát&nbsp;A3</span>
    </label>
  </div>
  <div class="form-item ">
    <label class="form-label">&nbsp;</label>
    <label class="form-field-wrapper" for="63">
      <span class="form-checkbox-field">
        <input type=submit value="Vytisknout spisový přebal" class=\"btn button\">
      </span>
    </label>
  </div>';
  echo '</form>';
  echo '</div></div></div></p>';
    echo '<p>
    <div class="form dark-color"> <div class="form-body"> <div class="form-row">';
      echo "<form method='POST\' action='output/doc/send_to_word.php' target='ífrm_get_value'>";
      echo "<input type='hidden' name='sablona' value='prehled'>
      <input type='hidden' name='cislo_spisu1' value='".$cislo_spisu1."'>
      <input type='hidden' name='cislo_spisu2' value='".$cislo_spisu2."'>
      <input type='hidden' name='ID' value='".$spis_id."'>
      <input type='hidden' name='referent_spis' value='".$referent."&'>
      <input type='hidden' name='format' value='pdf'>
      <input type='hidden' name='DIL_ID' value='".$dil."'>";
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
    //    echo "&nbsp;<input type=button class=button onclick=\"javascript:NewWindow2('output/doc/send_to_word.php?sablona=prehled&obal=1&cislo_spisu1=".$cislo_spisu1."&cislo_spisu2=".$cislo_spisu2."&ID=".$GLOBALS[id]."&referent_spis=".$referent."&format=pdf&')\" value='Vytisknout spisový přehled včetně spisového přebalu '>";

  //   $count=Table(array(
  //     "agenda" => "POSTA_TYP_POSTY",
  //     "appendwhere" => "AND ID IN (" . $GLOBALS['spis_id']. ")",
  //     "caption" => "Věcná klasifikace",
  //     "showinfo" => false,
  //     "showedit" => !$spis_uzavren,
  //     "showdelete" => false,
  //     "showaccess" => true,
  //     "setvars" => true,
  //     "unsetvars" => true,
  //     "emptyoutput" => false,
  //   ));
    echo '<br/>';

    echo "</td></tr></table>";

  echo "</td></tr></table>";

  $cislo_spisu1=$cj_info['CJ1'];
  $cislo_spisu2=$cj_info['CJ2'];
  $odbor = $cj_info['ODBOR'];
  $so = $cj_info['SUPERODBOR'];
  $text_cislospisu=$cj_info['CJ1'].'/'.$cj_info['CJ2'];
  $cislospisu = $text_cislospisu.'/'.$cj_info['SUPERODBOR'];

  //print_r($cj_info);

  //  echo "AAA ".$referent." BBB ".$odbor."<br/>";

  echo "<table border=0 width='100%'><tr><td width='70%' valign='top'>";

  $nazev="Seznam dokumentů vztahující se k ".$GLOBALS["CONFIG"]["CISLO_SPISU_2P"]." ".$text_cislospisu;
  UNSET($GLOBALS[REFERENT]);
  UNSET($GLOBALS['ODBOR']);
  UNSET($GLOBALS['ODDELENI']);
  UNSET($GLOBALS['NAZEV_SPISU']);
  UNSET($GLOBALS['SUPERODBOR']);
  UNSET($GLOBALS['PODCISLO_SPISU']);
  UNSET($GLOBALS['CISLO_SPISU1']);
  UNSET($GLOBALS['CISLO_SPISU2']);

  //HistorieSpisu($cislo_spisu1,$cislo_spisu2,$GLOBALS['spis_id']);
  //If (!$GLOBALS["FROM_EVIDENCE"])
  //



  echo "</td><td width='30%' valign='top'>";
  /*
    $count=Table(array(
      "agenda" => "POSTA_UKLZNACKA",
      //"tablename" => "posta_uklznacka",
      "appendwhere" => "and spis_id=".$spis_id,
      "maxnumrows" => 1,
      //"showdelete" => false,
      "showhistory" => true,
      "showedit" => false,
      "showdelete" => $lze_editovat,
      "showinfo" => false,
      "nocaption" => false,
      //"showaccess" => true,
      //"setvars" => true,
      //"unsetvars" => true,
    //    "emptyoutput" => false,
    ));

    {
      NewWindow(array("fname" => "Spis", "name" => "spis_znacka", "header" => true, "cache" => false, "window" => "edit"));

      echo "<form name=\"spis_pridat\" method=\"GET\">\n";
      if ($lze_editovat) echo "<input type=\"bnt\" class=\"button\" value=\"Přidat ukládací značku\"
      onClick=\"javascript:NewWindowSpis('".GetAgendaPath("POSTA_UKLZNACKA",false,true)."/edit.php?insert&SPIS_ID=".$spis_id."');return false;\">\n";
  if ($lze_editovat) echo "&nbsp;&nbsp;&nbsp;<input type=\"bnt\" class=\"button\" value=\"Spravovat ukládací značky\"
      onClick=\"javascript:window.open('http://monumnet.npu.cz/spis/essznacky.php?Name=SPIS_ZNACKY_HLED&Table=SpisHledZnac&Select=insert','MonumNet');return false;\">\n";

      echo "</form>";
    }
  */
  echo "</td></tr></table>";
}
$GLOBALS["ukaz_ovladaci_prvky"]=false;

include_once(FileUp2('.admin/brow_access.inc'));

  if ($GLOBALS['SHOW_CELY_SPIS']  == 1)
    $GLOBALS['ID'] = $cj_obj->GetDocsInTypSpis($spis_id);
  else
    $GLOBALS['ID'] = $cj_obj->GetDocsInSimpleCj($spis_id);

  //pokud mam pristup k celemu spisu, tak zrusim where podminku
  $pristupy = LoadClass('EedPristupy', 0);
  if ($pristupy->MamPristupKeSpisu($spis_id)) $where = '';

//$GLOBALS['SHOW_CELE_CJ_CHRONOLOGICKY'] = true;

if (!$GLOBALS['SHOW_CELE_CJ_CHRONOLOGICKY']) {
  $sql = Table(array(
    "tablename" => $spis_id,
    "caption" => "Dokumenty k " . $cj_info['CELE_CISLO'],
//    "sql" => "select * from posta WHERE ".$where_cj.  "  order by id desc",
    //"showaccess" => true,
    "showupload" => false,
    "appendwhere" => $where,
    "modaldialogs" => false,
    "schema_file" => '.admin/table_schema_spis.inc',
    "setvars" => true,
    'showcount' => false, //protahuje to tabulku
    "showhistory" => true,
    "showupload" => true,
    "select_id" => "ID" ,
    "unsetvars" => true ,
    ));
  $GLOBALS["ukaz_ovladaci_prvky"]=true;
  //$majitelspisu=MajitelSpisu($cislo_spisu1,$cislo_spisu2);



    $dalsi_cj=$cj_obj->SeznamCJvSpisu($GLOBALS['spis_id']);

  //jdeme z evidence, tak ukazeme tlacitko zpet.
  If ($GLOBALS["FROM_EVIDENCE"])
    echo "<input type=button class=button onclick=\"history.back(-1)\" value='   Zpět   '>";

  if ($cj_info['JE_TYPOVY_SPIS'] && count($dalsi_cj) == 0 && $cj_info['STATUS']>1) {
    $sql = 'select * from cis_posta_spisy where spis_id=' . $spis_id . ' and dalsi_spis_id=0';
    $q->query($sql);
    $q->Next_Record();
    $delete_id = $q->Record['ID'];
    if ($delete_id>0) echo "<p><a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/dalsi_spis/delete.php?DELETE_ID=".$delete_id."')\">Odebrat dokument z dílu</a></p>";

  }


  //if (!$cj_info['JE_TYPOVY_SPIS'])
  {
    if (count($dalsi_cj)>0) echo '<br/><p><h1>Do '.$spis4p.' je vloženo ' . count($dalsi_cj) . ' čj.';

    $pocet = 0;
    if (!$dalsi) $dalsi = 0;
    if (count($dalsi_cj)>10) echo ' - zobrazuji pozici ' . ($dalsi) . ' až ' . ($dalsi+10).'';
    echo '</h1></p>';
    while (list ($key, $val) = each ($dalsi_cj)) {
      $pocet ++;
      if ($pocet<$dalsi) continue;
      $cj_obj_temp = new EedCj($val);
      $cj_obj_info = $cj_obj_temp->GetCjInfo($val,1);
      $spis_vazba = $cj_obj_temp ->SpisVazba($GLOBALS['spis_id'], $val);
      UkazSpis_Obj($val,$spis_vazba['OWNER_ID']);
      $idcko=$spis_vazba['ID'];
      If ($idcko<>"" && !$spis_uzavren && ($mamPravaNaSpis || $spis_vazba['OWNER_ID']==$USER_INFO['ID']) && !$cj_info['JE_TYPOVY_SPIS']) {
         echo "<p><a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/dalsi_spis/delete.php?DELETE_ID=".$idcko."')\">Smazat vazbu mezi ".$text_cislospisu." a ".$cj_obj_info['CISLO_SPISU1']."/".$cj_obj_info['CISLO_SPISU2']."</a></p>";
      }
      If ($idcko<>"" && !$spis_uzavren && ($mamPravaNaSpis || $spis_vazba['OWNER_ID']==$USER_INFO['ID']) && $cj_info['JE_TYPOVY_SPIS']) {
        echo "<p><a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('./services/spisovka/dalsi_spis/delete.php?DELETE_ID=".$idcko."')\">Odebrat dokument z dílu</a></p>";
      }
      if (($pocet) > ($dalsi+10) && count($dalsi_cj)>=$pocet) {
         echo "<a class=\"btn btn-loading\" href=\"brow_spis.php?doc_id=".$hlavni_doc."&dalsi=".($pocet)."\" >Zobrazit další čj...</a>";
      break;
     }
    }
  }


} else {
  $temp = array();
  UNSET($GLOBALS['ID']);
  if ($GLOBALS['SHOW_CELY_SPIS']  == 1)
    $temp = $cj_obj->GetDocsInTypSpis($spis_id);
  else
    $temp = $cj_obj->GetDocsInCj($spis_id);
  foreach($temp as $val) $GLOBALS['ID'][] = $val;

  $sql = Table(array(
    "tablename" => '',
    "agenda" => "POSTA",
    "caption" => $cj_info['CELY_NAZEV'] . ' - chronologicky',
//    "sql" => "select * from posta WHERE ".$where_cj.  "  order by id desc",
    "appendwhere" => $where,
    "schema_file" => '.admin/table_schema_spis.inc',
    "setvars" => true,
//    'showcount' => false, //protahuje to tabulku
    "showhistory" => true,
    "showupload" => true,
    "showexportall" => true,
//    'formvars'=>array('EXPORT_ALL_step'),
    "select_id" => "ID" ,
//    "unsetvars" => true ,
    ));

}

if ($cj_info['ODBOR']) {
  $ret = $EddSql->user->VratUzlyAOdborPrac($cj_info['ODBOR']?$cj_info['ODBOR']:0);
  $zpracovatele = array($majitelspisu);

  foreach($ret['odborprac'] as $odbor => $prac) {
    $zpracovatele = array_merge($zpracovatele, $prac);
  }
}

echo '<p>';
If (!$lze_uzavrit && (in_array($USER_INFO[ID], $zpracovatele)|| HasRole('spisovna')) && !$GLOBALS["FROM_EVIDENCE"])
  echo '<div class="alert alert-info darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'"> <h4 class="alert-title">Upozornění:</h4> <p class="info-msg">Čj./spis nelze uzavřít, některý z dokumentů není vyřízen (není datum nebo způsob vyřízení nebo datum doručenky). </p> </div>';
If (!$spis_uzavren  && ($mamPravaNaSpis || HasRole('spisovna')) && $lze_uzavrit && !$cj_info['TYPOVY_SPIS_ID'])
  echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('services/spisovka/uzavreni_spisu/uzavrit.php?spis_id=".$GLOBALS['spis_id']."&cacheid=')\">Uzavřít ".$cj_info['CELY_NAZEV']."</a>";
echo '</p>';


If ($spis_uzavren  && ($mamPravaNaSpis || HasRole('spisovna'))  && ($cj_info['STATUS']>0||$cj_info['STATUS']==-4)  && !$GLOBALS["FROM_EVIDENCE"] && !$cj_info['TYPOVY_SPIS_ID']) {
// print_r($GLOBALS['STATUS']);
   echo "<a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('services/spisovka/uzavreni_spisu/otevrit.php?spis_id=".$GLOBALS['spis_id']."&cacheid=')\">Otevřít ".$cj_info['CELY_NAZEV']."</a>";

  if ($cj_info['STATUS'] == 1) {
    echo '<p><div class="alert alert-info darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'"> <h4 class="alert-title">Upozornění:</h4> <p class="info-msg">
    Pro uložení do příruční registratury vyplňte odpovídající registraturu ve volbě Zadat údaje (Údaje o čj.). Pro uložení do spisovny předejte dokument k uložení pracovníkovi spisovny.</p> </div>';
    echo '</p>';
  }
}



  //pokud je zapnuto pridavani dalsich zaznamu do spisu
if ($GLOBALS["CONFIG"]["SPIS_PREHLED_DALSI_ZAZNAMY"]) {
  if (!JeUzavrenSpis($cislo_spisu1,$cislo_spisu2,$referent) && !$GLOBALS["FROM_EVIDENCE"]) {
    $spis_where = " and cislo_spisu1 = $cislo_spisu1 and cislo_spisu2 = $cislo_spisu2";
    Table(array(
      "agenda"=>"POSTA_SPISPREHLED_ZAZNAMY",
      "tablename"=>"posta_spisprehled_zaznamy",
      "appendwhere"=>$spis_where,
      "maxnumrows"=>25,
      "nopaging"=>true,
      "showdelete"=>true,
      "showedit"=>true,
      "showinfo"=>true,
      "nocaption"=>false,
      "showaccess"=>true,
      "setvars"=>true,
      "unsetvars"=>true,
      "emptyoutput"=>true,
    ));
    $xx=new DB_POSTA;
  	$sql="select id,nazev_spisu from posta where cislo_spisu1='".$cislo_spisu1."' and cislo_spisu2='".$cislo_spisu2."'";
    $xx->query($sql);
  //	echo $sql;
  	$xx->Next_Record();
   	$nazev_spisu = $xx->Record["NAZEV_SPISU"];
    echo "
    <a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('services/spisovka/spisprehled/edit.php?insert&cislo_spisu1=".$cislo_spisu1."&cislo_spisu2=".$cislo_spisu2."&referent=".$referent."&nazev_spisu=".$nazev_spisu."&cacheid=')\">Přidat dokument k ".$GLOBALS["CONFIG"]["CISLO_SPISU_3P"]." ".$cislospisu."</a>
    <br /><br />";
  }
}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/brow_spis_end.php');
		if (File_Exists($file)) include($file);
  }
}

require(FileUp2('html_footer.inc'));

//  print_r($vysledek);
