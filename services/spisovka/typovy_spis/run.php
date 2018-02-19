<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(Fileup2("html_header_title.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();


$temp1 = explode(',',$GLOBALS['DALSI_SPIS_ID']);
$temp2 = explode(',',$GLOBALS['NOVY_SPIS']);

$q = new DB_POSTA;

if ($GLOBALS['DELETE_ID']) {
  $q->query('select * from '.$PROPERTIES['AGENDA_TABLE'].' where '.$PROPERTIES['AGENDA_ID'].'='.$GLOBALS['DELETE_ID']);
  $q->Next_Record();
  $data = $q->Record;
}

//$GLOBALS['VYBRANA_SOUCAST'] = 1; //onma, predelat, do ktere soucasti se musi vybrat
$GLOBALS['DIL'] = 0;

$GLOBALS['DALSI_SPIS_ID'] = -1; //prvotni spis typovy ma minus 1, 0 ma dil.

//  $GLOBALS['NOVY_SPIS'] = $temp2[$key];

  if ($GLOBALS['DELETE_ID']) {
    Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));

    $cj_obj = LoadClass('EedCj', $data['SPIS_ID']);
    $cj_info = $cj_obj->GetCjInfo($data['SPIS_ID']);
    $text = 'dokument (<b>'.$data['DALSI_SPIS_ID'].'</b>) byl vyjmut ze spisu '.$cj_info['CELY_NAZEV'];
    EedTransakce::ZapisLog($data['DALSI_SPIS_ID'], $text, 'DOC');
    EedTransakce::ZapisLog($data['SPIS_ID'], $text, 'SPIS');
  }

  else {
    $sqlObj = LoadClass('EedSql', 0);
    $append = '';
    if ($GLOBALS['ZNACKA_SPISU']) {
      // v pripade, ze mame znacku, tak nevytvorime CJ, ale zapiseme primo nazev spisu
      $doc = $sqlObj->createDocBezCJ($USER_INFO['ID'], $GLOBALS['ZNACKA_SPISU']);
    }
    else
      $doc = $sqlObj->createCJ($USER_INFO['ID']);
    if (!$GLOBALS['NAZEV_SPISU']) $GLOBALS['NAZEV_SPISU'] = $GLOBALS['ZNACKA_SPISU'];
    $sql = "update posta set main_doc=1,vec='typový spis " . addslashes ($GLOBALS['NAZEV_SPISU']) . "',datum_podatelna_prijeti='".Date('Y-m-d H:i:s')."', datum_referent_prijeti='".Date('Y-m-d H:i:s')."' where id=" . $doc;
    $q->query($sql);
    NastavStatus($doc);
    $cj_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
    $cj_info = $cj_obj->GetCjInfo($GLOBALS['SPIS_ID']);

    $text = 'založen '.$cj_info['CELY_NAZEV'];

    $puvodni_doc = $GLOBALS['SPIS_ID']; // zazalohujeme puvodni spis_id
    $puvodni_nazev = $GLOBALS['NAZEV_SPISU'];
    $GLOBALS['SPIS_ID'] = $doc;

    $GLOBALS['TYPOVY_SPIS_ID'] = $doc;
    EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS');
    EedTransakce::ZapisLog($doc, $text, 'DOC');

  	$typove_spisy = EedTools::GetSoucastiSablonyTypovehoSpisu($GLOBALS['TYPOVY_SPIS']);
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

  		Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
  		$text = 'založen díl pro '.$cj_info['CELY_NAZEV'];
  		EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS');
  		
  		//zalozime dokument do dilu spisu
  		if ($key == $GLOBALS['VYBRANA_SOUCAST']) {
  			UNSET($GLOBALS['ID']);
        $GLOBALS['SPIS_ID'] = $puvodni_doc;
  			$GLOBALS['DALSI_SPIS_ID'] = 0;
  			$GLOBALS['SOUCAST'] = $GLOBALS['VYBRANA_SOUCAST'];
  			$GLOBALS['NAZEV_SPISU'] = $GLOBALS['NAZEV_DILU'];
  			$GLOBALS['DIL'] = 1;
        $GLOBALS['TYPOVY_SPIS_ID'] = $doc;

  			Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
  			$text = 'čj vloženo do dílu pro '.$cj_info['CELY_NAZEV'];
  			EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS');
  				
  		}
  	}
    // a pridame saamotny dokument
		UNSET($GLOBALS['ID']);
		$GLOBALS['DALSI_SPIS_ID'] = 0;
		$GLOBALS['SOUCAST'] = 0;
		$GLOBALS['NAZEV_SPISU'] = $puvodni_nazev;
 		$GLOBALS['DIL'] = 0; //je to prvotni zaznam, mame v nem nazev spisu
		$GLOBALS['SPIS_ID'] = $doc;
    $GLOBALS['TYPOVY_SPIS_ID'] = $doc;
		Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));


  }

  UNSET($GLOBALS['ID']);

require_once(Fileup2("html_footer.inc"));  
?>
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>

