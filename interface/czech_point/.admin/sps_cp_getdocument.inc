<?php
//Login czechpointu do serveru 
require_once(FileUp2('.admin/upload_.inc'));
Function GetDocument($LogToken, $ReferenceNumber, $DocumentID, $DocumentTyp) {

  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true));

  $file = $uplobj['table']->getRecordTable($DocumentID);
  $doc_id = $file['RECORD_ID'];

  $doc = LoadClass('EedDokument', $doc_id);

  $upl_obj = LoadClass('EedUpload', $doc_id);
  foreach($upl_obj->uplobj_records as $file_temp) {
    if ($file_temp['ID'] == $DocumentID) $file = $file_temp;
  }

  $file_data = $uplobj['table']->GetUploadFiles($file);

    $return='<GetDocumentResponse xmlns="http://www.software602.cz/webservices/602xml">
      <GetDocumentResult>1</GetDocumentResult>
      <XmlDoc>
        <dokument>
          <identifikace>
            <cislo_jednaci>'.TxtEncoding4Soap($doc->cislo_jednaci).'</cislo_jednaci>
            <dokument_id>'.TxtEncoding4Soap($doc_id).'</dokument_id>
          </identifikace>
          <metadata>
            <cislo_jednaci>'.TxtEncoding4Soap($doc->cislo_jednaci).'</cislo_jednaci>
            <spisova_znacka>'.TxtEncoding4Soap($doc->cislo_jednaci).'</spisova_znacka>
            <vec>'.TxtEncoding4Soap($doc->vec).'</vec>
          </metadata>
          <prilohy>
            <priloha>
              <nazev>'.TxtEncoding4Soap($file['NAME']).'</nazev>
              <format>pdf</format>
              <filename>'.TxtEncoding4Soap($file['NAME']).'</filename>
              <obsah xmlns:dt="urn:schemas-microsoft-com:datatypes" dt:dt="bin.base64">'.base64_encode($file_data).'</obsah>
              <priloha_id>'.$DocumentID.'</priloha_id>
            </priloha>
          </prilohy>
        </dokument>
      </XmlDoc>
    </GetDocumentResponse>
    ';
/*
    $return='<LoginResponse>
        <LoginResult>1</LoginResult>
        <LogToken>'.$session.'</LogToken>
      </LoginResponse>
    ';
*/
    return $return;
/*
  }
  else
  {
    $text='(LOGIN) - zadané uživ. jméno a heslo není správné';
    WriteLog($software_id,$text,$session_id,1);

    $return='
     <ns1:LoginResponse ret="Exception" code="-2" xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:LoginResult>-2</ns1:LoginResult> 
        <ns1:Exception>InvalidUserName</ns1:Exception> 
     </ns1:LoginResponse>
  ';
    return $return;
  }
*/
}
?>
