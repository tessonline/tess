<?php
include_once(FileUp2('.admin/oth_funkce.inc'));
require_once(FileUp2('sip/sip_fce.inc'));
require_once(FileUp2('sip/sip_fceTS.inc'));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once(FileUp2('interface/.admin/soap_funkce.inc'));
include_once(FileUp2('.admin/status.inc'));

include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['status'] = getSelectDataEed(new of_select_status(array()));
$GLOBALS['jine'] = getSelectDataEed(new of_select_jine(array()));
$GLOBALS['typ_posty'] = getSelectDataEed(new of_select_typ_posty(array('selectfull'=>true)));

function generateSIP($id) {
  $q = new DB_POSTA;
  $sql = 'select * from posta where id='.$id;
  $q->query($sql); $q->Next_Record();
  $data = $q->Record;


$xmlstr = <<<XML
<?xml version='1.0'?>
<Spis ID="ESS_SPSPISIDENTIFIKATOR" xmlns="nsesss">
</Spis>
XML;

$xmlstr2 = <<<XML
<?xml version='1.0'?>
<root></root>
XML;

$files = <<<XML
<mets:fileSec></mets:fileSec>
XML;

  $cj = LoadClass('EedCj', $id);
  $cj_info = $cj->GetCjInfo($id);
//   if (!$cj_info['JE_TYPOVY_SPIS']) {
    $spis = @new SimpleXMLElement($xmlstr, 0, false);
    getSpisInfo($spis, $data);
//   }
//   else {
//     $spis = @new SimpleXMLElement($xmlstr2, 0, false);
//     $typovy_spis_id = $cj_info['TYPOVY_SPIS_MAINID'];
//     $sql = 'select * from posta where id='.$typovy_spis_id;
//     $q->query($sql); $q->Next_Record();
//     $data = $q->Record;
//     getTypSpisInfo($spis, $typovy_spis_id);
//     $vysledek = $spis->asXML();
// //     print_r($vysledek);
// //   Die('konec');
//   }


  //asi historie, zejmena import z jine spis sluzby
  //ve verzi 2 asi neni
  //$ZaznamOHistorii = $doc->addChild('ZaznamOHistorii');

  $file = 'sip/sip_header.xml';
  $fp = fopen($file, 'r');
  $header = fread($fp, filesize($file));
  fclose($fp);

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $user = LoadClass('EedUser',$USER_INFO['ID']);

  $header = str_replace('JMENO_PREDAVAJICIHO' , $user->cele_jmeno, $header);
  $header = str_replace('DATUM_VZNIKU' , ConvertDatumToXML(Date('Y-m-d H:i'),true), $header);
//  $header = str_replace('' , '', );
//  $header = str_replace('' , '', );
//  $header = str_replace('' , '', );

  $file = 'sip/sip_footer.xml';
  $fp = fopen($file, 'r');
  $footer = fread($fp, filesize($file));
  fclose($fp);

  $vysledek = $spis->asXML();
  $vysledek = str_replace('<?xml version="1.0"?>','',$vysledek);

  $vysledek = str_replace('DOCIDENTIFIKATOR', $data['ID'], $vysledek);
  $vysledek = str_replace('SPISIDENTIFIKATOR', $data['ID'], $vysledek);

  $vysledek = str_replace('<', '<nsesss:', $vysledek);
  $vysledek = str_replace('<nsesss:/', '</nsesss:', $vysledek);

  $xml = $header.$vysledek.$footer;

  $cj = LoadClass('EedCj',$data['ID']);
  $docs = $cj->getDocsInCJ($data['ID']);
  $db = new DB_POSTA;
  $docs_add = '';

  $filesXML = @new SimpleXMLElement($files, 0, false);
  $is_file = false;

  foreach($docs as $doc_id) {
    $return = array();
    $cj_temp = LoadClass('EedCj',$doc_id);
    if ($cj_temp->typ_dokumentu == 'D' && $_POST['vcetne_priloh']) $return = getFiles($filesXML, $doc_id);
//    if ($cj_temp->typ_dokumentu == 'D') $return = getFiles($filesXML, $doc_id);
    $docs_add .= '<mets:div TYPE="dokument" DMDID="ESS_'.$doc_id.'">';
    if (count($return)>0) {
      $is_file = true;
//      $docs_add .= '<mets:div TYPE="komponenta">';
      foreach ($return as $ret) {
         $docs_add .= '<mets:fptr FILEID="' . $ret . '"/>';
      }
//    $docs_add .= '</mets:div>
//';
    }
    $docs_add .= '</mets:div>
';
  }
//                  <mets:div TYPE="doručený dokument">
//                    <mets:fptr FILEID="file_001"/>
//                    <mets:fptr FILEID="file_002"/>
//                  </mets:div>
//                 <mets:div TYPE="vyřízení prvopisem">
//          <mets:fptr FILEID="file_004"/>


//  	$docs_add .= '<mets:div TYPE="dokument" DMDID="ESS_'.$data['ID'].'"></mets:div>
//';
  $filesOUT = $filesXML->asXml();
  $filesOUT = str_replace('<?xml version="1.0"?>', '', $filesOUT);

//  $filesOUT = str_replace('fileSec', 'mets:fileSec', $filesOUT);
  $filesOUT = str_replace('<fileGrp', '<mets:fileGrp', $filesOUT);
  $filesOUT = str_replace('<file', '<mets:file', $filesOUT);
  $filesOUT = str_replace('<FContent', '<mets:FContent', $filesOUT);
  $filesOUT = str_replace('<binData', '<mets:binData', $filesOUT);
  $filesOUT = str_replace('</fileGrp', '</mets:fileGrp', $filesOUT);
  $filesOUT = str_replace('</file', '</mets:file', $filesOUT);
  $filesOUT = str_replace('</FContent', '</mets:FContent', $filesOUT);
  $filesOUT = str_replace('</binData', '</mets:binData', $filesOUT);

  $xml = str_replace('EEDDOCS', $docs_add, $xml);
  $xml = str_replace('DMDIDSPISID', 'ESS_SP' . $data['ID'], $xml);
//  $xml = str_replace('DMDIDVS', 'ESS_VS' . $data['ID'], $xml);
  $xml = str_replace('DMDIDVS', $GLOBALS['JID_VS_SKARTACE'], $xml);

  $xml = str_replace('DMDIDSP', $GLOBALS['JID_SP_SKARTACE'], $xml);

  if ($is_file) $xml = str_replace('ADD_FILES', $filesOUT, $xml);
  else
    $xml = str_replace('ADD_FILES', '', $xml);

  $xml = html_entity_decode($xml, 0, 'UTF-8');
  return $xml;
}