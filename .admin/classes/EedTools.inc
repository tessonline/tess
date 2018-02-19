<?php
include('db.inc');
class EedTools extends eed_db_object {
  

   /** vrati cislo jednaci k id dokumentu
   */  
  function getCJ($id) {
    $id = (int) $id;
    if ($id<1) return false;
    $class = LoadClass('EedDokument', $id);
    $res = $class->FormatCisloJednaci($id);
    return $res; 
  }

  function UkazPocetDleStatus($status, $where="") {
    $db = eed_db_object::getInstanceDb();
    $pocet = 0;
    if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $add = 'AND SUPERODBOR IN (' . EedTools::VratSuperOdbor() . ')';
    $sql = "SELECT id FROM posta p WHERE (1=1 $where) and status IN (".$status.") $add and stornovano is null" ;
    $db->query($sql);
    $pocet = $db->Num_Rows();
    return $pocet ;
  }

  function VratOdbor() {
    $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
    $prac = $USER_INFO["ID"];
    $prac = $prac ? $prac : 0;
    $class = LoadClass('EedUser', $prac);
    $odbor = $class->VratSpisovyUzelPracovnika($prac);
    return $odbor;
  }
  
  function VratOdborId($id_odbor) {
    $q = eed_db_object::getInstanceDb();
    $sql = "select id from cis_posta_odbory where id_odbor=".$id_odbor;
    $q->query($sql);
    $q->Next_Record();
    return $q->Record['ID'];    
  }
  
  function VratIdOdbor($id_odbor) {
    $q = eed_db_object::getInstanceDb();
    $sql = "select id_odbor from cis_posta_odbory where id=".$id_odbor;
    $q->query($sql);
    $q->Next_Record();
    return $q->Record['ID_ODBOR'];
  }

  function JeDocVeSpisu($doc_id = 0) {
    if ($doc_id>0) {
      $class = LoadClass('EedCj', $doc_id);
      $cj = $class->GetCjInfo($doc_id);
      if ($cj['JE_SPIS']) return true;
      else
        return false;
    }
    return false;
  }


  function VratSuperOdbor($odbor = 0) {
//     if ($odbor == 0) {
//       $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
//       $odbor = $USER_INFO["GROUP_ID"];
//     }
//     $id=$odbor;
//     $last_odbor=0;
//     if ($id==0) return $GLOBALS['CONFIG']['DEFAULT_SUPERODBOR']?$GLOBALS['CONFIG']['DEFAULT_SUPERODBOR']:0;
//     while ($id>0) {
//       $a=$id;
//       $last_odbor=$id;
//        if (!$id=GetParentGroup($id)) break;
//     }
//     //echo "nad odbor je".$last_odbor;
   $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
   $prac = $USER_INFO["PRACOVISTE"];
   if (!$prac) $prac = 0;
    return $prac;
  }

  function VratNazevSuperOdbor($odbor = 0) {
    $class = LoadClass('EedUser', 0);
    $odbor = $class->GetUnitName($odbor);
    return $odbor;
  }

  function NajdiSuperOdborId($uzel_id = 0, $unit_id = 0)  {
     if (!$class) $class = LoadClass('EedUser', 0);
     if ($unit_id == 0) $unit_id = $class->VratOdborZSpisUzlu($uzel_id);
     $pole = array();
 		 $pole = $class->VratNadrizeneUnity($unit_id);
     $zarizeni_id_ret = array_pop(array_keys($pole));
     return $zarizeni_id_ret;
 }

  function NajdiSuperodborzIDPUVODNI($id_puvodni = 0)  {
    If ($id_puvodni>0) {
      $a = eed_db_object::getInstanceDb();
      $sql='select superodbor from posta where id=' . $id_puvodni;
      $a->query($sql);
      $a->Next_Record();
      $ret = $a->Record['SUPERODBOR'];
   }
   else $ret = 0;
   return $ret;
 }



  function Skartace_Pole($skartaceID) {
    $res="";
    If ($skartaceID>0) {
      $a = eed_db_object::getInstanceDb();
      $sql='select skar_znak, doba, text, kod, nadrazene_id from cis_posta_skartace where id='.$skartaceID;
      $a->query($sql);
      $a->Next_Record();
      $text_skartace=$a->Record['KOD'] . ' ' . str_replace('STARE - ','',$a->Record["TEXT"]);
      //$text=substr($text_skartace,0,strpos($text_skartace,' '));
  //    $res=$text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];

      $res=array('kod'=>$a->Record['KOD'],'znak'=>$a->Record['SKAR_ZNAK'],'doba'=>$a->Record['DOBA'],'text'=>$text_skartace);
      if ($a->Record['NADRAZENE_ID']>0) {
        $sql='select skar_znak, doba, text, kod from cis_posta_skartace where id='.$a->Record['NADRAZENE_ID'];
        $a->query($sql);
        $a->Next_Record();
        $res['plne_urceny'] = $a->Record['KOD'] .'.'.$res['kod'];
        
      }

    }
    return $res;
  }

  function getIDDZ($id) {
    if ($id>0) {
      $a = eed_db_object::getInstanceDb();
      $sql = 'select ds_id from posta_DS where posta_id='.$id;
      $a->query($sql); $a->Next_Record();
      return $a->Record['DS_ID'];
    }
    else return '';
  }


  function czdate2eng($engdatum) {
    $date1 = substr($engdatum,0,strpos($engdatum," "));
  // Odstranime cas...
    $datumkod=explode(".",$date1);
    if (strlen($datumkod[0])<2) $datumkod[0]="0".$datumkod[0];
    if (strlen($datumkod[1])<2) $datumkod[1]="0".$datumkod[1];
    $odeslano=$datumkod[2]."-".$datumkod[1]."-".$datumkod[0];
    return $odeslano;
  }

  function GetArchivacniBoxy($posta_id) {
    $ids = array();
    If ($posta_id>0) {
      $a = eed_db_object::getInstanceDb();
      $sql='select box_id from posta_spisovna_boxy_ids where posta_id=' . $posta_id;
      $a->query($sql);
      while ($a->Next_Record()) {
        $ids[] = $a->Record['BOX_ID'];
      }
    }
    return $ids;
  }

	function MaPristupKDokumentu($IDP, $akce) {
	  include_once(FileUp2('.admin/has_access.inc'));
	  global $USER_INFO;
	  if (MaPristupKDokumentu_old($IDP)) return true;
	  else {
	  	if (!$USER_INFO) $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
	  	$EedUser = LoadClass('EedUser', $USER_INFO['ID']);

	  	$text = 'uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. '), spustil akci ' . $akce .' u dokumentu ' . $IDP . ', na které nemá dostatečná práva';
	  	EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
	  	echo '<h1>CHYBA:</h1><p>Pro tuto operaci nemáte oprávnění.</p>';
	  	require(FileUp2('html_footer.inc'));
	  	Die();


	  }
	}

	function MaPristupKCteniDokumentu($IDP, $akce) {
	  include_once(FileUp2('.admin/has_access.inc'));
	  global $USER_INFO;
	  if (MaPristupKCteniDokumentu($IDP)) return true;
	  else {
	  	if (!$USER_INFO) $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
	  	$EedUser = LoadClass('EedUser', $USER_INFO['ID']);

	  	$text = 'uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. '), spustil akci ' . $akce .' u dokumentu ' . $IDP . ', na které nemá dostatečná práva';
	  	EedTransakce::ZapisLog(0, $text, 'SECURITY', $user_id);
	  	echo '<h1>CHYBA:</h1><p>Pro tuto operaci nemáte oprávnění.</p>';
	  	require(FileUp2('html_footer.inc'));
	  	Die();


	  }
	}

	function GetLokace($id = 0) {
		if (!$id) return '';
		$db = eed_db_object::getInstanceDb();
		$sql = "SELECT plna_cesta FROM posta_spisovna_cis_lokace WHERE id=" . $id ;
		$db->query($sql);
		$db->Next_Record();
		return $db->Record['PLNA_CESTA'] ;
	}

  function ZalozSbernyArch($id) {
		global $USER_INFO;
		if (!$USER_INFO) $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
    $id_user = $USER_INFO['ID'];
    $cj_obj = new EedCj($id);
    $cj_zaklad = $cj_obj->cislo_jednaci_zaklad;
    $q = new DB_POSTA;

    $sql = "select id from cis_posta_spisy where spis_id=" . $id;
    $q->query($sql);
    $pocet = $q->Num_Rows();

    if ($pocet == 0) {
      $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,ARCH) VALUES ".
            "('$cj_zaklad', '$cj_zaklad', ".$id.", 0,'".Date('Y-m-d')."','".Date('H:i:s')."',$id_user,$id_user,1)";
      $q->query($sql);

      $text = 'Byl založen sběrný arch <b>' . $cj_zaklad . '</b>';
      EedTransakce::ZapisLog($id, $text, 'DOC', $id_user);
      EedTransakce::ZapisLog($id, $text, 'SPIS', $id_user);
    }

  }

	function PriradPodcislo($lastid) {
		global $USER_INFO;
		if (!$USER_INFO) $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
		if ($GLOBALS['POUZIVAT_SBERNE_ARCHY'] ) return false; //pokud nepouzivame sberne archy, tak vyskocime :-)
		$db = new DB_POSTA;
        $cj = LoadClass('EedCj', $lastid);		
    $sql = 'select * from posta where id=' . $lastid;
		$db->query($sql); $db->Next_Record();
//		$GLOBALS["CISLO_SPISU1"] = $cj->cj1 ? $cj->cj1 : 0;
//		$GLOBALS["CISLO_SPISU2"] = $cj->cj2 ? $cj->cj2 : 0;
		$GLOBALS["CISLO_SPISU1"] = $db->Record["CISLO_SPISU1"] ? $db->Record["CISLO_SPISU1"]:0;
		$GLOBALS["CISLO_SPISU2"] = $db->Record["CISLO_SPISU2"] ? $db->Record["CISLO_SPISU2"]:0;
//echo '<hr/>';
		$sql = "select id,podcislo_spisu,cislo_spisu1,cislo_spisu2,superodbor from posta where (CISLO_SPISU1 = ".$GLOBALS["CISLO_SPISU1"].") and (CISLO_SPISU2 = ".$GLOBALS["CISLO_SPISU2"].") and id<>$lastid order by id asc limit 1";
		$db->query($sql);
		$db->Next_Record();
		$id_puvodni = $db->Record['ID'];
    if (!$id_puvodni) {$id_puvodni = $lastid; $db->Record['PODCISLO_SPISU'] = 0;} //jde o prvni dokument

    //if ($id_puvodni>$lastid) {$id_puvodni = $lastid; $db->Record['PODCISLO_SPISU'] = 0;} //jde o prvni dokument

//echo "onma $id_puvodni <br/>";
    if (($db->Record['PODCISLO_SPISU'] < $GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'])|| ($id_puvodni<$lastid)) {
			$sql = "UPDATE posta SET podcislo_spisu = ".$GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'].",last_user_id = $USER_INFO[ID] where id = " . $id_puvodni;
//echo $sql.'<br/>';
			$db->query($sql);
      EedTools::ZalozSbernyArch($id_puvodni);
      $cj_puv = new EedCj($id_puvodni);
// 		  $text = 'U dokumentu <b>('.$id_puvodni.')</b> byl založen sběrný arch <b>' . $cj_puv->cislo_jednaci_zaklad .'</b>';
      $text = 'dokument (<b>'.$id_puvodni.'</b>) '.$cj_puv->cislo_jednaci.' byl vložen do <b>' . $cj_puv->cislo_jednaci_zaklad . '</b>';
		  EedTransakce::ZapisLog($id_puvodni, $text, 'DOC', $USER_INFO[ID]);
		}
		$GLOBALS["CISLO_SPISU1"] = $db->Record["CISLO_SPISU1"] ? $db->Record["CISLO_SPISU1"]:0;
		$GLOBALS["CISLO_SPISU2"] = $db->Record["CISLO_SPISU2"] ? $db->Record["CISLO_SPISU2"]:0;
			
    if ($lastid<>$id_puvodni) {
  		$sql2 = "SELECT MAX(podcislo_spisu) as podcislo_spisu_max FROM POSTA where (CISLO_SPISU1 = ".$GLOBALS["CISLO_SPISU1"].") and (CISLO_SPISU2 = ".$GLOBALS["CISLO_SPISU2"].")";
//echo $sql.'<br/>';
  		$db->query ($sql2);
  		$db->next_record();
  		$PODCISLO2 = 0;
  		$PODCISLO2 = $db->Record["PODCISLO_SPISU_MAX"] ? $db->Record["PODCISLO_SPISU_MAX"] : $GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'];
  		$PODCISLO = $PODCISLO2+1;

      $sql2 = "select * from posta WHERE id =" . $lastid;
  		$db->query ($sql2); $db->Next_Record();
      $so = $db->Record['SUPERODBOR'] ? $db->Record['SUPERODBOR'] : 0;


      $cj_vysl = new EedCj($lastid);
  		$sql2 = "SELECT id FROM POSTA where (CISLO_SPISU1 = ".$GLOBALS["CISLO_SPISU1"].") and (CISLO_SPISU2 = ".$GLOBALS["CISLO_SPISU2"]." and superodbor=$so)";
  		$db->query ($sql2);
      $pocet = $db->Num_Rows();
      if ($pocet == 1) {
        //jde o novy arch na nove soucasti, musime zalozit spis a nastavit main_doc
        EedTools::ZalozSbernyArch($lastid);
        $append = ',main_doc = 1 ';
      }

      $sql = "UPDATE posta SET podcislo_spisu = ".$PODCISLO . $append .",last_user_id = $USER_INFO[ID] where id = $lastid";
  		$db->query ($sql);
  		NastavStatus($lastid);
  		$text = 'dokument <b>('.$lastid.')</b> byl přidán do sběrného archu ' . $cj_vysl->cislo_jednaci_zaklad;
 	    EedTransakce::ZapisLog($lastid, $text, 'DOC', $USER_INFO[ID]);
    }

	}
	
	function GetExemplar($id, $cs1, $cs2, $podcislo) {
		$db = eed_db_object::getInstanceDb();
		$sql = "SELECT max(exemplar) as max_exm FROM posta WHERE cislo_spisu1=$cs1 and cislo_spisu2=$cs2 and podcislo_spisu=$podcislo" ;
		$db->query($sql);
		$db->Next_Record();
		$exemplar = $db->Record['MAX_EXM'] ? $db->Record['MAX_EXM']+1 : 1; 
		return $exemplar;
	}

	function PriradExemplar($id) {
		global $USER_INFO;
		if (!$USER_INFO) $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
		$db = eed_db_object::getInstanceDb();
		$db = new DB_POSTA;
		$cj = LoadClass('EedCj', $id);
		$GLOBALS["CISLO_SPISU1"] = $cj->cj1 ? $cj->cj1 : 0;
		$GLOBALS["CISLO_SPISU2"] = $cj->cj2 ? $cj->cj2 : 0;
		$GLOBALS["PODCISLO_SPISU"] = $cj->podlomeni ? $cj->podlomeni : 0;
    if ($GLOBALS["PODCISLO_SPISU"]== 0 ) {
  		$sql = "select id,exemplar,podcislo_spisu,cislo_spisu1,cislo_spisu2,superodbor from posta where (CISLO_SPISU1 = ".$GLOBALS["CISLO_SPISU1"].") and (CISLO_SPISU2 = ".$GLOBALS["CISLO_SPISU2"].") order by id asc limit 1";
//echo $sql.'<br/>';
  		$db->query($sql);
  		$db->Next_Record();
  		$id_puvodni = $db->Record['ID'];
      EedTools::PriradPodcislo($id_puvodni);
  		$sql = "select id,exemplar,podcislo_spisu,cislo_spisu1,cislo_spisu2,superodbor from posta where id=" . $id_puvodni;
//echo $sql.'<br/>';
  		$db->query($sql);
  		$db->Next_Record();
      $GLOBALS["PODCISLO_SPISU"] = $db->Record['PODCISLO_SPISU'];;

    }

		$sql = "select id,exemplar,podcislo_spisu,cislo_spisu1,cislo_spisu2,superodbor from posta where (CISLO_SPISU1 = ".$GLOBALS["CISLO_SPISU1"].") and (CISLO_SPISU2 = ".$GLOBALS["CISLO_SPISU2"].") and (PODCISLO_SPISU = ".$GLOBALS["PODCISLO_SPISU"].") order by id asc limit 1";
//echo $sql.'<br/>';
		$db->query($sql);
		$db->Next_Record();
		$id_puvodni = $db->Record['ID'];
		if ($db->Record['EXEMPLAR'] <> $GLOBALS['CONFIG']['PRVOTNI_PODLOMENI']) {
      $cj_vysl_puv = new EedCj($id_puvodni);
			$sql = "UPDATE posta SET exemplar = ".$GLOBALS['CONFIG']['PRVOTNI_PODLOMENI'].",last_user_id = $USER_INFO[ID] where id = " . $id_puvodni;
//echo $sql.'<br/>';
			$db->query($sql);
      $cj_vysl = new EedCj($id_puvodni);
  		$text = 'K dokumentu <b>('.$id_puvodni.')</b> '.$cj_vysl_puv->cislo_jednaci.' byl přidán exemplář, toto je exemplář <b>1</b>, nově je uvedeno čj. <b> ' . $cj_vysl->cislo_jednaci.'</b>';
 	    EedTransakce::ZapisLog($id_puvodni, $text, 'DOC', $USER_INFO[ID]);
		}
		$cs1 = $db->Record["CISLO_SPISU1"] ? $db->Record["CISLO_SPISU1"]:0;
		$cs2 = $db->Record["CISLO_SPISU2"] ? $db->Record["CISLO_SPISU2"]:0;
		$podcislo = $db->Record["PODCISLO_SPISU"] ? $db->Record["PODCISLO_SPISU"]:0;
		
		
		$exemplar = EedTools::GetExemplar($id, $cs1, $cs2, $GLOBALS["PODCISLO_SPISU"]);
		$sql = "UPDATE posta SET podcislo_spisu=$podcislo,exemplar = ".$exemplar.",last_user_id = $USER_INFO[ID] where id = $id";
//echo $sql.'<br/>';
		$db->query ($sql);
    $cj_vysl = new EedCj($id);
		$text = 'Dokument <b>('.$id.')</b> '.$cj_vysl->cislo_jednaci.' byl označen jako exemplář <b>'.$exemplar.'</b>';
    EedTransakce::ZapisLog($id, $text, 'DOC', $USER_INFO[ID]);
    }

	  function GetSoucastiTypovehoSpisu($spis_id) {
	    $ids = array();
	    If ($spis_id>0) {
	      $a = eed_db_object::getInstanceDb();
	      $sql='select * from cis_posta_spisy where typovy_spis_id=' . $spis_id .' and typovy_spis>0 and dalsi_spis_id=-1 and dil=1 order by soucast asc';
	      $a->query($sql);
	      while ($a->Next_Record()) {
          $id = $a->Record['ID'];
	        $ids[$a->Record['ID']] = $a->Record;
	        $ids[$a->Record['ID']]['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'TSS' . $a->Record['ID'];
          $ids[$a->Record['ID']]['SKARTACE_ID'] = $a->Record['SKARTACE_ID'];
          $ids[$a->Record['ID']]['REZIM_ID'] = $a->Record['REZIM_ID'];

	      }
        $temp = array();
        foreach ($ids as $key => $val) {
           $skartace = EedTools::getSkartacniRezimSpisu($val['SKARTACE_ID'], $val['REZIM_ID']);
           $temp[$key] = $val;
           $temp[$key]['ZNAK'] = $skartace['znak'];
           $temp[$key]['DOBA'] = $skartace['doba'];
           $temp[$key]['KOD'] = $skartace['kod'];
        }
        $ids = $temp;
	    }
	    return $ids;
	  }

    function getSkartacniRezimSpisu($skartace, $rezim_id = 0) {
      $ret = array();
      if ($rezim_id>0) {
	      $q = eed_db_object::getInstanceDb();
        $sql = 'select * from posta_cis_skartacni_rezimy where id=' . $rezim_id;
        $q->query($sql);
        $q->Next_Record();
        if ($q->Record['SKAR_ZNAK']<>'') $ret = array('jid' => $q->Record['JID'], 'znak' => $q->Record['SKAR_ZNAK'], 'doba' => $q->Record['SKAR_LHUTA']);
      }
      else {
        $temp = EedTools::Skartace_Pole($skartace);
        $ret=array('kod'=>$temp['kod'],'znak'=>$temp['znak'],'doba'=>$temp['doba']);

      }
      return $ret;
    }


	  function GetSoucastiSablonyTypovehoSpisu($spis_id) {
	    $ids = array();
	    If ($spis_id>0) {
	      $a = eed_db_object::getInstanceDb();
	      $sql='select * from posta_cis_typ_spis_soucasti where spis_id=' . $spis_id .' order by id asc';
	      $a->query($sql);
        $pocet = 0;
	      while ($a->Next_Record()) {
          $pocet++;
	        $ids[$pocet]['NAZEV'] = $a->Record['NAZEV'];
	        $ids[$pocet]['SKARTACE_ID'] = $a->Record['SKARTACE_ID'];
	        $ids[$pocet]['REZIM_ID'] = $a->Record['REZIM_ID'];
	      }
	    }
	    return $ids;
	  }

	  function VratOtevrenyDil($spis_id, $soucast) {
	      $a = eed_db_object::getInstanceDb();
	      $sql='select * from cis_posta_spisy where typovy_spis_id=' . $spis_id .' and typovy_spis>0 and soucast=' . $soucast . ' and dalsi_spis_id=-1 and datum_uzavreni is NULL order by dil desc';
	      $a->query($sql);
	      $a->Next_Record();
	      $dil = $a->Record['DIL'];
	      return $dil;
	  }

	  function VratTypovySpisColumn($spis_id) {
	      $a = eed_db_object::getInstanceDb();
	      $sql='select * from cis_posta_spisy where typovy_spis_id=' . $spis_id .' and typovy_spis>0 AND dalsi_spis_id=-1 and datum_uzavreni is NULL order by dil desc';
	      $a->query($sql);
	      $a->Next_Record();
	      $dil = $a->Record['TYPOVY_SPIS'];
	      return $dil;
	  }

    function VratTypovySpisZNazvu($nazev) {
      $q = new DB_POSTA;
      $res = array();
      $sql = "select * from cis_posta_spisy where nazev_spisu like '".$nazev."'";
      $q->query($sql);
      if ($q->Num_Rows() == 0) return false;
      while ($q->Next_Record())
        $res[] = $q->Record['TYPOVY_SPIS_ID'];

      return $res;
    }

    function VratSoucastDleSkartaceTypovehoSpisu($typovy_spis_id, $pismeno) {
      $soucasti = EedTools::GetSoucastiTypovehoSpisu($typovy_spis_id);
      foreach ($soucasti as $key => $soucast) {
        $skartacni_rezim = EedTools::getSkartacniRezimSpisu($soucast['SKARTACE_ID'], $soucast['REZIM_ID']);
        if ($skartacni_rezim['znak'] == $pismeno) $vhodna_soucast[] = $soucast;
      }
      return $vhodna_soucast;
    }

	  function VratPuvodniSUperodbor($dokument_id) {
	      $a = eed_db_object::getInstanceDb();
	      $sql='select * from posta_h where id=' . $dokument_id . ' AND superodbor is not null and superodbor>0 order by id_h asc limit 1';
	      $a->query($sql);
	      $a->Next_Record();
	      $so = $a->Record['SUPERODBOR'];
	      return $so;
	  }

	  function JeDilPrazdny($spis_id, $soucast, $dil) {
	      $a = eed_db_object::getInstanceDb();
	  	//a testneme, jestli nejde o prazdny dil (pokud je prazdny, musime tam prvni zaznam pridat
	      $sql='select * from cis_posta_spisy where typovy_spis_id=' . $spis_id .' and typovy_spis>0
	      		and soucast=' . $soucast . ' and dil=' . $dil . ' and dalsi_spis_id=0 and (datum_uzavreni is null) order by dil desc';
	      $a->query($sql);
	      if ($a->Num_Rows() == 0) return 0;
	      else {
	      	$a->Next_Record();
	      	return $a->Record['SPIS_ID'];
	      }
	  }
	   
    function JeNastaveniKonfigurace($so, $parametr) {
	      $a = eed_db_object::getInstanceDb();
	  	//a testneme, jestli nejde o prazdny dil (pokud je prazdny, musime tam prvni zaznam pridat
	      $sql='select * from posta_konfigurace where superodbor in (' . $so . ') and parametr like \'' . $parametr . '\'';
	      $a->query($sql);
	      if ($a->Num_Rows() == 0) return false;
        else {
          $a->Next_Record();
          return $a->Record['ID'];
        }

    }
	       
    function MuzemePoslatEmail($user_id) {
      $ret = true;
      $sett = new SETTING_OBJ;
      $a = $sett->get($user_id, 'POSTA');
      if ($a['POSTA']['USER_CONFIG']['NEZASILAT_EMAILY'] == 1) $ret = false;
      return $ret;
    }

}
