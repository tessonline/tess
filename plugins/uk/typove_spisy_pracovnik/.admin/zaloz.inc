<?php
include_once(FileUp2('.admin/status.inc'));
include_once(FileUp2('.admin/config.inc'));


function ZalozTypovySpis($znacka, $nazev, $so, $referent, $typ) {
//  global $USER_INFO;
  static $q;

  UNSET($GLOBALS['EDIT_ID']);
  if (!$q) $q = new DB_POSTA;
//  $puv_ref = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
//  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo($referent, 0, 0, 1);
  $GLOBALS['DIL'] = 0;
  $GLOBALS['PUVODNI_SPIS'] = '0';
  $GLOBALS['NOVY_SPIS'] = '0';

  $GLOBALS['DALSI_SPIS_ID'] = -1; //prvotni spis typovy ma minus 1, 0 ma dil.

  $sqlObj = LoadClass('EedSql', 0);
  $append = '';
  $doc = $sqlObj->createDocBezCJ($referent, $znacka);
  $nazev = $znacka . ' - ' . $nazev;
  $sql = "update posta set main_doc=1,vec='typový spis " . $nazev . "',datum_podatelna_prijeti='".Date('Y-m-d H:i:s')."', datum_referent_prijeti='".Date('Y-m-d H:i:s')."',superodbor=".$so." where id=" . $doc;
  $q->query($sql);
  NastavStatus($doc);
  $cj_obj = LoadClass('EedCj', $doc);
  $cj_info = $cj_obj->GetCjInfo($doc);

  $text = 'založen typový spis '.$znacka;

//   $puvodni_doc = $GLOBALS['SPIS_ID']; // zazalohujeme puvodni spis_id
//   $puvodni_nazev = $GLOBALS['NAZEV_SPISU'];
  $GLOBALS['SPIS_ID'] = $doc;

  $GLOBALS['TYPOVY_SPIS'] = $typ;
  $GLOBALS['TYPOVY_SPIS_ID'] = $doc;
  EedTransakce::ZapisLog($doc, $text, 'DOC');


	$typove_spisy = EedTools::GetSoucastiSablonyTypovehoSpisu($typ);
  
	foreach($typove_spisy as $key => $val) {
		UNSET($GLOBALS['ID']);
		$GLOBALS['DALSI_SPIS_ID'] = -1;
		$GLOBALS['SOUCAST'] = $key;
    $GLOBALS['SPIS_ID'] = $doc;
		$GLOBALS['NAZEV_SPISU'] = $val['NAZEV'];
		$GLOBALS['SKARTACE_ID'] = $val['SKARTACE_ID'];
		$GLOBALS['REZIM_ID'] = $val['REZIM_ID'];
		$GLOBALS['DIL'] = 1;
    $GLOBALS['TYPOVY_SPIS_ID'] = $doc;
    $GLOBALS['PUVODNI_SPIS'] = 0;
    $GLOBALS['NOVY_SPIS'] = 0;
		$sql = Run_(array("agenda"=>"POSTA_TYP_SPIS_SOUCASTIADILY", "noaccesscondition"=>true,"noaccessrefresh"=>true,"outputtype"=>1,"no_unsetvars"=>true));
		$text = 'založen díl ' . $val . ' v typovém spisu ' . $znacka;
		EedTransakce::ZapisLog($doc, $text, 'SPIS');
	}
  // a pridame saamotny dokument
	UNSET($GLOBALS['ID']);
	$GLOBALS['DALSI_SPIS_ID'] = 0;
	$GLOBALS['SOUCAST'] = 0;
	$GLOBALS['NAZEV_SPISU'] = $nazev;
	$GLOBALS['DIL'] = 0; //je to prvotni zaznam, mame v nem nazev spisu
	$GLOBALS['SPIS_ID'] = $doc;
  $GLOBALS['TYPOVY_SPIS_ID'] = $doc;
	Run_(array("agenda"=>"POSTA_TYP_SPIS_SOUCASTIADILY", "noaccesscondition"=>true,"noaccessrefresh"=>true,"outputtype"=>1,"no_unsetvars"=>true));

  return $doc;
}