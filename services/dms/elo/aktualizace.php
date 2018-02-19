<?php



function AktualizujElo($id)
{
  include_once(FileUp2('.admin/upload_.inc'));
  include_once( $GLOBALS["TMAPY_LIB"].'/upload/main.inc'); 
  $config=$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table'];
  $GLOBALS['RECORD_ID']=$id;
  $GLOBALS['FILE_ID']=$id;
  if (!$GLOBALS['EDIT_ID']) $GLOBALS['EDIT_ID']=$id;
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $elo_con = new Upload_Storage_Obj_Elo($config,'elo');
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id); 

  //jsou v uploadu soubory? pokud ano, posleme metadata
  If (count($upload_records)>0)
  {
    include(FileUp2('services/dms/elo/metadata.php'));
    $token=$elo_con->connect2Elo();
    while (list($key,$val)=each($upload_records))
    {
       $elo_con->Service->setMetaData($val['DIRECTORY'],$data, $token);
       $elo_con->Service->showSOAPDebug();     
    }
    if (!$elo_con->Service->logout($token)) Die('Nepovedl se logout pro token '.$token);
  }
}
