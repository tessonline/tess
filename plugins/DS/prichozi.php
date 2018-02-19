<?php
if (!$_SERVER['HTTPS'] == 'on') Die();
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/nastaveni.inc"));
require_once(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/isds_.inc"));
require_once(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2("interface/.admin/certifikat_funkce.inc"));
require_once(FileUp2(".admin/classes/EedDatovaZprava.inc"));


if (!HasRole('cist_prichozi_DS') && !HasRole('access_all')) {
  require(FileUp2("html_footer.inc"));
  Die();
}

set_time_limit(600);
function array_msort($array, $cols)
{
    $colarr = array();
    foreach ($cols as $col => $order) {
        $colarr[$col] = array();
        foreach ($array as $k => $row) { $colarr[$col]['_'.$k] = strtolower($row[$col]); }
    }
    $eval = 'array_multisort(';
    foreach ($cols as $col => $order) {
        $eval .= '$colarr[\''.$col.'\'],'.$order.',';
    }
    $eval = substr($eval,0,-1).');';
    eval($eval);
    $ret = array();
    foreach ($colarr as $col => $arr) {
        foreach ($arr as $k => $v) {
            $k = substr($k,1);
            if (!isset($ret[$k])) $ret[$k] = $array[$k];
            $ret[$k][$col] = $array[$k][$col];
        }
    }
    return $ret;

}

//$prac=VratPracovniky();
$prac = array();
$form_prac='<form name="frm_privatni" method="get" action="receive.php"><select name="prac_id"><option value=""></option>';
while (list($key,$val)=each($prac))
  $form_prac.='<option value="'.$key.'">'.$val.'</option>';
$form_prac.="</select>";

//pridame vyhledani jedne datovky
if ($_GET['SELECT_ID']) {
  $_GET['SELECT_ID'] = trim($_GET['SELECT_ID']);
  $_POST['SELECT_ID'] = array(0=>$_GET['SELECT_ID']);
  $nacist_soubory_prichozi=true;
  $statusDS = 128;
  $GLOBALS['status'] = 128;

  $statusDS = 129;
  $GLOBALS['status'] = 129;

}


echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Kontaktuji datovou schránku...'</script>";Flush();
if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else 
$certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
if (!$schranka->ValidLogin)
{
	echo ("<span class='caption'>Nepodařilo se připojit k ISDS.</span><br/><span class='text'>Zkontrolujte uživatelské jméno a heslo.<br/>".$schranka->ErrorInfo."</span>");
  echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
  require(FileUp2("html_footer.inc"));
	exit();
}


echo '<p><div class="form darkest-color"> <div class="form-body"> <div class="form-row">';


echo '<span class="text">Filtr datových zpráv:</span><div class="form dark-color"><div class="form-body"><div class="form-row">
<a href="?statusDS=-1" class="'.($GLOBALS["status"]==-1?'':'btn').'">Vše</a>&nbsp;
<a href="?statusDS=96" class="'.($GLOBALS["status"]==96?'':'btn').'">nepřečtené</a>&nbsp;
<a href="?statusDS=128" class="'.($GLOBALS["status"]==128?'':'btn').'">přečtené</a>&nbsp;
<a href="?statusDS=256" class="'.($GLOBALS["status"]==258?'':'btn').'">nedoručitelné</a>&nbsp;
<a href="?statusDS=999" class="'.($GLOBALS["status"]==999?'':'btn').'">Přečtené a nezpracovávané v ED</a>
<a href="?statusDS=-2" class="'.($GLOBALS["status"]==-2?'':'btn').'">Aktualizovat</a>
nebo&nbsp;vyhledat&nbsp;zprávu:&nbsp;<input placeholder="zapište ID DZ" type="text" id="X_ID" name="X_ID" value="'.$_GET['SELECT_ID'].'">

</div></div></div>';

echo '</div> </div> </div><p>';
echo "

    <script>
    <!--
  function navigate(e) {
    if (!e) {
      e = window.event;
    }
    if(e.keyCode == 13)  //enter pressed
        Prehled_Vyhledat(this);
  }
  document.onkeypress=navigate;


 function Prehled_Vyhledat(hodnota) {
   if(document.getElementById('wait_label')) document.getElementById('wait_label').style.display = 'block';
    var frm = document.prehled_vyhledavani;
    var input1 = document.createElement('INPUT');
    input1.setAttribute('type', 'hidden');
    input1.setAttribute('name', 'SELECT_ID');
    input1.setAttribute('value', document.getElementById('X_ID').value);

    frm.appendChild(input1);
    frm.method='GET';
    var act = frm.action;
    frm.action = 'prichozi.php';
    frm.submit();

  }
  </script>
  <form name='prehled_vyhledavani'>
  </form>
";
echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Kontaktuji datovou schránku...'</script>";Flush();





$q=new DB_POSTA;
$a=new DB_POSTA;

if (!$statusDS) $statusDS=96;

if ($statusDS==-2) {$text='aktualizace'; $nacist_soubory_prichozi = false;}
if ($statusDS==96) $text='nepřečtené zprávy';                                            
if ($statusDS==128) $text='přečtené zprávy';                                            
if ($statusDS==256) $text='nedoručitelné zprávy';                                            
if ($statusDS==999) $text='přečtené a nezpracovávané v EED';                                            

if ($statusDS<>128 && $statusDS<>-1) $nacist_soubory=true;
//if ($nacist_soubory_prichozi) {Die(print_r($_POST));}
//Seznam dorucenych zprav
$dnes='2009-05-10T00:00:00';	
//$zitra='2009-05-19T00:00:00';



echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načítám seznam z DS...'</script>";Flush();

// if ($statusDS<>999)
//   $res=$schranka->GetListOfReceivedMessages($dnes,$zitra,0,10000,$statusDS);
// else
//   $res=$schranka->GetListOfReceivedMessages($dnes,$zitra,0,10000,128);

//pri aktualizaci vklada do db vsechny zpravy, ZOBRAZI $res
$ds = new EedDatovaZprava();
//aktualizace - vklada vsechny zpravy, zobrazi $res
if ($statusDS == - 2){
	$res = $schranka->GetListOfReceivedMessages($dnes, $zitra, 0, 10000, 128);
	$ds->VlozNoveZpravy($res);
} else
// vsechy zpravy - vklada pouze nove, zobrazi zpravy $res.=$prectene,  neprectene zpravy - vklada pouze nove, zobrazi $res
if (($statusDS == - 1)||($statusDS == 96)){
	$res = $schranka->GetListOfReceivedMessages($dnes, $zitra, 0, 10000, 96);
	$ds->VlozNoveZpravy($res);
	if ($statusDS==-1) {
		$z = $ds->NactiZpravy('7,10');
		if ($res['dmRecord']) {
			$r['dmRecord'] = array(array_merge($res['dmRecord'],$z['dmRecord']));
			$res = $r;
		}
		else 
			$res = $z;
	}
} else
	//prectene zpravy, zobrazi $res = $prectene;
if ($statusDS == 128){
   $res=$ds->NactiZpravy('7');
} else
//nedorucitelne vzdy nacitat
if ($statusDS == 258){
   $res = $schranka->GetListOfReceivedMessages($dnes, $zitra, 0, 10000, -1);
}

if ($statusDS == 999) {
   $res=$ds->NactiZpravy('5,6,7');

}

/*
if ($schranka->StatusCode<>'0000') {
  echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b>";
  require(FileUp2("html_footer.inc"));
  Die();
}*/

//print_r($res[dmRecord]);
if (!$res) $res=array();

if ($res[dmRecord][dmID]) $pole[dmRecord][0]=$res[dmRecord]; else $pole[dmRecord]=$res[dmRecord];

$b=0;
$pocet_zprav=count($pole[dmRecord]);

if ($statusDS==999)
{
  $a=new DB_POSTA;
  echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Porovnávám s databází...'</script>";Flush();

  $sql="select posta_id from posta_DS where odeslana_posta='f'";
  $a->query($sql); while ($a->Next_Record()) $nactene_zpravy[]=$a->Record['POSTA_ID'];
  //echo "Nacteno je ".count($nactene_zpravy);
  //jeste to musime omezit o stornovane dokumenty
  $sql="select id from posta where id in (".implode(',',$nactene_zpravy).") and stornovano is null";
  $nactene_zpravy=array(); $a->query($sql); while ($a->Next_Record()) $nactene_zpravy[]=$a->Record['ID'];
  //echo "Nestornovanych je ".count($nactene_zpravy);
  //print_r($nactene_zpravy); 
  //a nacteme DS ID u tech posta_id, ktere nejsou stornovane
  $sql="select DS_id from posta_DS where posta_id in (".implode(',',$nactene_zpravy).")";
  $nutno_nacist=array(); $a->query($sql); while ($a->Next_Record()) $nutno_nacist[]=$a->Record['DS_ID'];
  $nacitat=array(); 
  while (list($key,$val)=each($pole[dmRecord]))
  //while (list($key,$val)=each($res[dmRecord]))
  {
    if (!in_array($val[dmID],$nutno_nacist)) $nacitat[]=$val;
  }
  $pole=array();
  $pole[dmRecord]=$nacitat;
  $nacist_soubory=false;

}

while (list($key,$val)=@each($pole[dmRecord]))
//while (list($key,$val)=each($res[dmRecord]))
{
  $b++;
  if ($nacist_soubory || $nacist_soubory_prichozi) $href="<a title='Uložit dokument do EED' href='receive.php?ID_DOSLE=".$val[dmID]."'><img src='".FileUp2('images/ok_check.gif')."' border='0'></a>";
//  if ($val[dmMessageStatus]<>6 && $val[dmMessageStatus]<>5) $href="";
  if (($val[dmID] && !$nacist_soubory_prichozi) || ($nacist_soubory_prichozi && in_array($val[dmID],$_POST['SELECT_ID'])))
  {
     echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Zpracovávám zprávu ".$val[dmID]." - ".$b."/".$pocet_zprav."'</script>";Flush();
     $odkaz_soubor=array();
     if ($nacist_soubory || ($nacist_soubory_prichozi && in_array($val[dmID],$_POST['SELECT_ID'])))
     {
        $soubor=GetSouborzDS($val[dmID],$schranka);
        //print_r($soubor);
        //ulozime lokalne soubory, pro cteni
        $cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val[dmID].'/';
        if (!is_dir($cesta)) mkdir($cesta);
        $ulozeno=array();
        $citac=0;
        while (list($keyz,$valz)=each($soubor))
        {
          $citac++;
          $fname=$valz[filename];
          $pripona=substr($fname,strpos($fname,'.'));
          //$fname=TxtEncodingFromSoap($fname);
          $fname=str_replace("\\","",$fname);
          $add_text='';
          //pokud nemame nazev souboru, nebo pokud je nulovy, nebo pokud poslali dva soubory se stejnym nazvem
          if (strlen(TxtEncodingFromSoap($fname))<1 || in_array($fname,$ulozeno)) {$fname='soubor_'.$val[dmID].'-'.$citac.$pripona; $add_text='<br/>&nbsp;<i>zmena nazvu '.$valz[filename].'</i>';}
          $valz[filename]=$val[dmID].'-'.$citac;

          $ulozeno[]=$valz[filename]; //ulozime nazev souboru, obcas poslou soubory s duplicitnim nazvem

          $fp = fopen($cesta.$valz[filename], "w");
          fwrite($fp, base64_decode($valz[filecont]));
          fclose($fp);
          $velikost=round(strlen(base64_decode($valz[filecont]))/1024);
          if (strlen(base64_decode($valz[filecont]))<2) $velikost="<b><font color=red>000</font>";
          if ($fname<>'prichozi_datova_zprava.zfo' && $fname<>'dorucenka_'.$val[dmID].'.zfo' && $fname<>'kontrola_podpisu.pdf' && $val[dmPersonalDelivery]=='true')
            $odkaz_soubor[]="".$fname."</a>&nbsp;-&nbsp;".$velikost."&nbsp;kB".$add_text;
          if ($fname<>'prichozi_datova_zprava.zfo' && $fname<>'dorucenka_'.$val[dmID].'.zfo' && $fname<>'kontrola_podpisu.pdf' && $val[dmPersonalDelivery]!='true')
            $odkaz_soubor[]="<a title='".str_replace("'","",$val[filedesc])."' href='getfile_DS.php?dmID=".$val[dmID]."&fileDZ=".$valz[filename]."&name=".$fname."' target='frame'>".$fname."</a>&nbsp;-&nbsp;".$velikost."&nbsp;kB".$add_text;

        }
      }
      else
        $odkaz_soubor[]='------';

      $vec='';
      $vec.=TxtEncodingFromSoap($val[dmAnnotation]);

      $from=TxtEncodingFromSoap("<b>".$val[dmSender]."</b><br/>".$val[dmSenderAddress]);
      if ($val[dmToHands]<>'') $from.="<br/><b>K rukám:</b> ".TxtEncodingFromSoap($val[dmToHands])."";
      if ($val[dmPersonalDelivery]=='true') $from.='<br/><b><font color=red>DO VLASTNÍCH RUKOU</font></b>';
      if ($val[dmPersonalDelivery]=='true' && $GLOBALS[CONFIG_POSTA][DS][ds_vlastnich_rukou]>0) 
      {  
        $href=$form_prac.'<input type="hidden" name="ID_DOSLE" value="'.$val[dmID].'"><input type="button" class="button" value="Předat" onclick="javascript:document.frm_privatni.submit();"></form>';
//        $href=$form_prac.'<input type="hidden" name="ID_DOSLE" value="'.$val[dmID].'"><input type="submit" class="button" value="Předat"></form>';
      }

      //koukneme, jeslti uz mame tuhle zpravu v EED, pokud ano, dame info uzivateli
      $output_info='<b>JID v EED:</b><br/>';
      $sql='select * from posta_DS where ds_id='.$val[dmID].' order by posta_id asc';
//      echo $sql;
      $q->query($sql);
      $pocet=$q->Num_Rows();
      if ($pocet>0)
        while ($q->Next_Record())
        {
          $id=$q->Record['POSTA_ID'];
          $a->query('select * from posta where id='.$id);
          $a->Next_Record();
          $cislo_jednaci = $id;
          if ($a->Record[STORNOVANO]<>'')
            $output_info.="&nbsp;<a class='pages' title='".strip_tags($a->Record[STORNOVANO])."'><strike>".$cislo_jednaci."</strike></a>&nbsp;<br/>";
          else
            $output_info.="&nbsp;<a class='pages' target='posta' title='Ukázat záznam v EED' href='/".GetAgendaPath('POSTA')."/brow.php?frame&ID=".$id."'>".$cislo_jednaci."</a>&nbsp;<br/>";
        
        }
  
      if (!$nacist_soubory && !$nacist_soubory_prichozi) $href=$output_info;
      //print_r($soubor);
      $DS_DATA[]=array(
      "ID"=>$val[dmID],
      "jejich_cj"=>TxtEncodingFromSoap($val[dmSenderRefNumber].'<br/>'.$val[dmSenderIdent].'&nbsp;'),
      "nase_cj"=>TxtEncodingFromSoap($val[dmRecipientRefNumber].'<br/>'.$val[dmRecipientIdent].'&nbsp;'),
      "datum"=>ConvertDatumToString($val[dmDeliveryTime]),
      "from"=>$from,
      "vec"=>$vec,
      "soubory"=>TxtEncodingFromSoap(implode('<br/>',$odkaz_soubor)),
      "doruceni"=>TxtEncodingFromSoap($GetListOfMessagesResponse[$val[dmMessageStatus]]),
      "odkaz"=>$href
    );
  }
}
echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";

if (count($DS_DATA)>1)
  $DS_DATA = array_msort($DS_DATA, array('ID'=>SORT_DESC));
//print_r($DS_DATA2);
include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$DS_DATA;
//print_r($DS_DATA);

$GLOBALS['nacist_soubory']=$nacist_soubory;
if ($nacist_soubory_prichozi) $GLOBALS['nacist_soubory']=true;
if (count($DS_DATA)>0)
  Table(array("db_connector" => &$db_arr,"showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showdelete"=>false,"showselect"=>true,"multipleselect"=>true,"showinfo"=>false,"multipleselectsupport"=>true));
else
  echo "<h1><br/>Příchozí datové zprávy</h1><span class='text'><br/>Danému filtru - <b>".$text."</b> - neodpovídá žádná datová zpráva.</span>";


require(FileUp2("html_footer.inc"));
