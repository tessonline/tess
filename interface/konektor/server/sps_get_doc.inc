<?php
 
Function get_doc($session_id,$dokument_id,$odbor_id,$zpracovatel_id)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'get_doc','Neprovedena identifikace');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]+1; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  $sql = "SELECT * FROM posta WHERE 1=1";
  if ($odbor_id>0) $sql.=" AND odbor = '".$odbor_id."'";
  if ($zpracovatel_id>0) $sql.=" AND referent = '".$zpracovatel_id."'";
  $sql.=" AND odeslana_posta='f'";
  $sql.=" AND (stav=".$stav.") ";
  
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
//echo $sql;
  $q->query($sql);
  $counter=0;
  $counter2=0;

  
  while ($q->Next_Record())
  {
    $dokument[$counter]=VratDokumentInfo($q->Record[ID]);
    //vrátí pole se seznamem příloh na základě hodnoty AGENDA_ID
//    print_r($seznam_souboru);
  //  $dokument[$counter][SOUBORY] = array('files'=>new soapval('files', 'tns:files',$file));
/*    $dokument[$counter][SOUBORY] = array(
      new soapval('file','tns:file',array(FILE_ID=>'TEST', FILE_NAME=>'test2')),
      new soapval('file','tns:file',array(FILE_ID=>'TEST', FILE_NAME=>'test2')),
    );
*/    $counter++;
  }
  $text='Operace proběhla v pořádku';
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
    'dokumenty'=>new soapval('dokumenty', 'tns:dokumenty',$dokument),
  );
  return VratVysledek($vysledek);
}


